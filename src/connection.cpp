
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

void Connection::resetTimeout()
{
	mTimeoutTimestamp = std::chrono::system_clock::now();
}

bool Connection::isTimedOut()
{
	if (!mTimeOutEnabled)
		return false;
	std::chrono::duration<double> diff = std::chrono::system_clock::now() - mTimeoutTimestamp;
	return diff.count() > 5.0;
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
		byte* data = packet->data + 2;
		uint32_t len = packet->len - 2;
		
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
		resetTimeout();
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
		resetTimeout();
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

		// say hello to the world server

		Packet packet(sizeof(LoginInfo_Struct), OP_SendLoginInfo, this);
		LoginInfo_Struct* li = (LoginInfo_Struct*)packet.getDataBuffer();

		// login_info -> accountID as a string, null terminator, session key
		memset(li->login_info, 0, 64);
		itoa(getAccountID(), li->login_info, 10);
		memcpy(&li->login_info[strlen(li->login_info) + 1], getSessionKey().c_str(), getSessionKey().length());

		packet.send(mEQNet);
		break;
	}

	default:
		printf("unhandled opcode: 0x%0.4X\n", opcode);
		break;
	}
}

void Connection::processPacketWorld(uint16_t opcode, byte* data, uint32_t len)
{
	switch (opcode)
	{
	default:
		printf("unhandled world opcode: 0x%0.4X\n", opcode);
		break;
	}
}
