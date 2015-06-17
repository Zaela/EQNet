
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
	setTimeoutEnabled(true);
	setAutoAckEnabled(false);
	resetTimeout();
}

void Connection::sessionHandoff(Address& addr)
{
	// send session disconnect to current address
	sendSessionDisconnect();
	// close socket
	disconnect();
	// set new address
	setAddress(addr);
	// open socket to new address
	if (!connect())
		return;
	// reset ack manager
	resetAcks();
	// init session with new address
	initiateSession();
}

void Connection::pump()
{
	if (isTimedOut())
	{
		queueEvent(mEQNet, EQNET_TIMEOUT);
		resetTimeout();
	}

	for (;;)
	{
		int len = recvPacket();
		if (len <= 0)
			break;

		if (!handleProtocol(len))
			continue;

		processPackets();
	}

	processSendQueue();
}

void Connection::processPackets()
{
	while (!mReadPacketQueue.empty())
	{
		ReadPacket* packet = mReadPacketQueue.front();
		mReadPacketQueue.pop();

		uint16_t opcode = *(uint16_t*)packet->data;
		uint32_t offset = 2;

		// opcodes with a low-order byte of 0 (e.g. 0x4200 -> 00 42 in memory)
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
		case MODE_LOGIN_TO_WORLD:
		case MODE_CHAR_SELECT:
			processPacketWorld(opcode, data, len);
			break;
		case MODE_WORLD_TO_ZONE:
			processPacketZone(opcode, data, len);
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

		Packet* packet = new Packet(10 + mEQNet->credentialsLen, OP_Login);
		byte* b = packet->getDataBuffer();
		b[0] = 3;
		b[5] = 2;
		memcpy(&b[10], mEQNet->credentials, mEQNet->credentialsLen);

		packet->queue(mEQNet);
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
		Packet* packet = new Packet(10, OP_ServerListRequest);
		byte* b = packet->getDataBuffer();
		b[0] = 4;

		packet->queue(mEQNet);
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
			server.listId = copyInt();
			server.runtimeId = copyInt();
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

		Address addr;
		addr.ip = mEQNet->selectedServer->ip;
		addr.port = 9000;

		recordAddress(mEQNet->addressWorld, addr);
		
		freeServerList(mEQNet);

		mEQNet->mode = MODE_LOGIN_TO_WORLD;
		sessionHandoff(addr);
		break;
	}

	default:
		printf("unhandled login opcode: 0x%0.4X\n", opcode);
		break;
	}
}

void Connection::processPacketWorld(uint16_t opcode, byte* data, uint32_t len)
{
	uint16_t eqnetOpcode = translateOpcodeFromServer(mEQNet, opcode);
	printf("opcode 0x%0.4X -> 0x%0.4X\n", opcode, eqnetOpcode);
	switch (eqnetOpcode)
	{
	// packets on the way to char select
	case EQNET_OP_GuildsList:
	{
		readGuilds(mEQNet, data, len);
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

	// packets on the way to zone
	case EQNET_OP_ZoneUnavailable:
		queueEvent(mEQNet, EQNET_ZONE_UNAVAILABLE);
		break;

	case EQNET_OP_MessageOfTheDay:
		// plain cstring
		queueZonePacketEvent(mEQNet, eqnetOpcode, data, len,
			opcode, data, len);
		break;

	case EQNET_OP_SetChatServer:
	case EQNET_OP_SetChatServer2:
		break;

	case EQNET_OP_ZoneServerInfo:
	{
		// struct seems to be the same for all client versions
		Titanium::ZoneServerInfo_Struct* zs = (Titanium::ZoneServerInfo_Struct*)data;

		Address addr;
		addr.ip = zs->ip;
		addr.port = zs->port;

		recordAddress(mEQNet->addressZone, addr);

		mEQNet->mode = MODE_WORLD_TO_ZONE;
		sessionHandoff(addr);
		break;
	}

	default:
		printf("unhandled world opcode: 0x%0.4X\n", opcode);
		for (uint32_t i = 0; i < len; ++i)
			printf("%0.2X ", data[i]);
		printf("\n");
		break;
	}
}

void Connection::processPacketZone(uint16_t opcode, byte* data, uint32_t len)
{
	uint16_t eqnetOpcode = translateOpcodeFromServer(mEQNet, opcode);

	handleZonePacket(mEQNet, eqnetOpcode, opcode, data, len);
};
