
#include "stdafx.h"

Connection::Connection(EQNet* net)
	: Receiver(net)
{
	setTimeoutEnabled(true);
}

Connection::~Connection()
{
	sendSessionDisconnect();
}

void Connection::initiateSession()
{
	// send a session request to initiate with the server
	sendSessionRequest();
	// wait for response
	int len = recvWithTimeout(5000);
	handleProtocol(len);
	// increase our timeout window from 1.5 seconds to 5 so we don't have to spam quite so much...
	sendMaxTimeoutLengthRequest();
}

void Connection::pump()
{
	if (isTimedOut())
	{
		queueEvent(mEQNet, EQNET_TIMEOUT);
		resetTimeout();
		return;
	}

	int len = recvPacket();
	if (len <= 0)
		return;

	if (!handleProtocol(len))
		return;

	processPackets();
}

void Connection::processPackets()
{
	while (!mReadPacketQueue.empty())
	{
		ReadPacket* packet = mReadPacketQueue.front();
		mReadPacketQueue.pop();

		uint16_t opcode = *(uint16_t*)packet->data;
		int offset = 2;

		// opcodes with a low-order byte (post-byte order flip) of 0 (e.g. 0x4200 -> 00 42 in memory)
		// are preceded with an extra 0 byte (e.g. 00 42 -> 00 00 42)
		if (opcode == 0)
		{
			opcode = *(uint16_t*)(packet->data + 1);
			offset = 3;
		}

		byte* data = packet->data + offset;
		uint32_t len = packet->len - offset;
		
		switch (mEQNet->mode)
		{
		case MODE_LOGIN:
		case MODE_SERVER_SELECT:
			processPacketLogin(opcode, data, len);
			break;
		case MODE_WORLD:
			processPacketWorld(opcode, data, len);
			break;
		}
		
		delete packet;
	}
}

void Connection::processPacketLogin(uint16_t opcode, byte* data, uint32_t len)
{
	switch (opcode)
	{
	case OP_ChatMessage:
	{
		printf("OP_ChatMessage\n");
		// we receive this to signal that the server's ready to
		// receive login credentials, for whatever reason

		Packet packet(10 + mEQNet->credentialsLen, OP_Login, this, OP_Packet, false, false);
		byte* b = packet.getDataBuffer();
		b[0] = 3;
		b[5] = 2;
		memcpy(&b[10], mEQNet->credentials, mEQNet->credentialsLen);

		packet.send(mEQNet);
		break;
	}

	case OP_LoginAccepted:
	{
		printf("OP_LoginAccepted\n");

		if (len < 80)
		{
			queueEvent(mEQNet, EQNET_LOGIN_BAD_CREDENTIALS);
			return;
		}

		len -= 10;
		byte* decrypted = EQNet_Decrypt(data + 10, &len);

		Login_ReplyBlock* rb = (Login_ReplyBlock*)decrypted;

		setAccountID(rb->login_acct_id);
		setSessionKey(rb->key);

		printf("AccountID: %u, SessionKey: %s\n", getAccountID(), getSessionKey().c_str());

		EQNet_Free(decrypted);

		//send login server list request
		Packet packet(10, OP_ServerListRequest, this, OP_Packet, false, false);
		byte* b = packet.getDataBuffer();
		b[0] = 4;

		packet.send(mEQNet);
		break;
	}

	case OP_ServerListResponse:
	{
		printf("OP_ServerListResponse\n");

		uint32_t count = *(uint32_t*)(data + 16);
		uint32_t offset = 20;

		EQNet_Server* servers = new EQNet_Server[count];
		memset(servers, 0, sizeof(EQNet_Server) * count);

		auto copyStr = [&offset, data]()
		{
			const char* c = (const char*)data + offset;
			size_t len = strlen(c) + 1;
			offset += len;
			char* str = new char[len];
			memcpy(str, c, len);
			return str;
		};

		auto copyInt = [&offset, data]()
		{
			uint32_t* v = (uint32_t*)&data[offset];
			offset += sizeof(uint32_t);
			return *v;
		};

		int i = 0;
		while (offset < len)
		{
			EQNet_Server& server = servers[i++];
		
			server.ip = copyStr();
			server.listID = copyInt();
			server.runtimeID = copyInt();
			server.name = copyStr();
			server.language = copyStr();
			server.region = copyStr();
			server.status = copyInt();
			server.playerCount = copyInt();
		}

		mEQNet->serverListCount = count;
		mEQNet->serverList = servers;
		mEQNet->mode = MODE_SERVER_SELECT;
		queueEvent(mEQNet, EQNET_LOGIN_AT_SERVER_SELECT);
		setTimeoutEnabled(false);
		break;
	}

	case OP_PlayEverquestResponse:
	{
		Login_PlayResponse* pr = (Login_PlayResponse*)data;

		bool success = (pr->allowed > 0);
		if (!success)
		{
			queueEvent(mEQNet, EQNET_WORLD_CONNECT_FAILED);
			return;
		}

		queueEvent(mEQNet, EQNET_LOGIN_TO_WORLD);
		setTimeoutEnabled(true);
		resetTimeout();

		Address addr;
		addr.ip = mEQNet->selectedServer->ip;
		addr.port = 9000;

		setAddress(addr);
		
		freeServerList(mEQNet);
		sendSessionDisconnect();

		mEQNet->mode = MODE_WORLD;
		// disconnect from login
		disconnect();
		// connect to world
		connect();
		// reset ack manager
		resetAcks();
		// init session with world
		initiateSession();

		setAutoAckEnabled(true);

		// say hello to the world server

		// struct seems to be the same for all client versions
		Packet packet(sizeof(Titanium::LoginInfo_Struct),
			translateOpcodeToServer(mEQNet, EQNET_OP_SendLoginInfo), this);
		Titanium::LoginInfo_Struct* li = (Titanium::LoginInfo_Struct*)packet.getDataBuffer();

		// login_info -> accountID as a string, null terminator, session key
		memset(li->login_info, 0, 64);
		itoa(getAccountID(), li->login_info, 10);
		memcpy(&li->login_info[strlen(li->login_info) + 1], getSessionKey().c_str(), getSessionKey().length());

		packet.send(mEQNet);
		break;
	}

	default:
		printf("unhandled login opcode: 0x%0.4X\n", opcode);
		break;
	}
}

void Connection::processPacketWorld(uint16_t opcode, byte* data, uint32_t len)
{
	printf("opcode 0x%0.4X -> 0x%0.4X\n", opcode, translateOpcodeFromServer(mEQNet, opcode));
	switch (translateOpcodeFromServer(mEQNet, opcode))
	{
	case EQNET_OP_GuildsList:
	{
		// this seems to be the same for all client versions
		Titanium::GuildsListEntry_Struct* guilds = (Titanium::GuildsListEntry_Struct*)data;

		if (mEQNet->guildList)
		{
			delete[] mEQNet->guildList;
			mEQNet->guildListCount = 0;
		}

		// count the number of actual guild names represented
		int numGuilds = 0;
		Titanium::GuildsListEntry_Struct* g = guilds;
		uint32_t pos = 0;
		while (pos < len)
		{
			if (g->name[0] != 0)
				++numGuilds;
			++g;
			pos += sizeof(Titanium::GuildsListEntry_Struct);
		}

		if (numGuilds == 0)
			break;

		// copy only actual guild names
		EQNet_Guild* list = new EQNet_Guild[numGuilds];
		memset(list, 0, sizeof(EQNet_Guild) * numGuilds);

		mEQNet->guildList = list;
		mEQNet->guildListCount = numGuilds;

		pos = 0;
		int id = 0;
		g = guilds;
		while (pos < len)
		{
			if (g->name[0] != 0)
			{
				list->id = id;
				Util::strcpy(list->name, g->name, 64);
				++list;
			}
			++id;
			++g;
			pos += sizeof(Titanium::GuildsListEntry_Struct);
		}

		break;
	}

	case EQNET_OP_SendCharInfo:
	{
		readCharSelectCharacters(mEQNet, data, len);

		setTimeoutEnabled(false);
		mEQNet->mode = MODE_CHAR_SELECT;
		queueEvent(mEQNet, EQNET_WORLD_AT_CHAR_SELECT);
		break;
	}

	case EQNET_OP_LogServer:
	{
		const char* shortname = (char*)(data + 32);
		size_t len = strlen(shortname) + 1;

		char* str = new char[len];
		memcpy(str, shortname, len);

		if (mEQNet->serverShortName)
			delete[] mEQNet->serverShortName;
		mEQNet->serverShortName = str;
		break;
	}

	case EQNET_OP_ApproveWorld:
	case EQNET_OP_EnterWorld:
	case EQNET_OP_PostEnterWorld:
	case EQNET_OP_ExpansionInfo:
		break;

	default:
		printf("unhandled world opcode: 0x%0.4X\n", opcode);
		for (uint32_t i = 0; i < len; ++i)
			printf("%0.2X ", data[i]);
		printf("\n");
		break;
	}
}
