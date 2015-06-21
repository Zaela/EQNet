
#include "stdafx.h"

Connection::Connection(EQNet* net)
	: ProtocolReceiver(net)
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
		if (!retry())
			queueEvent(mEQNet, EQNET_EVENT_Timeout);
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

bool Connection::retry()
{
	if (mEQNet->retryCount >= mEQNet->retryMaxAttempts)
		return false;

	mEQNet->retryCount++;

	if (mEQNet->awaitingSession)
	{
		sendSessionRequest();
		return true;
	}

	return true;
}

void Connection::processPackets()
{
	for (; mReadQueuePos < mReadPacketQueue.size(); ++mReadQueuePos)
	{
		ReadPacket* packet = mReadPacketQueue[mReadQueuePos];

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

		if (mEQNet->mode >= MODE_LOGIN_TO_WORLD)
			processPacketWorldZone(opcode, data, len);
		else
			processPacketLogin(opcode, data, len);
	}
}

void Connection::processPacketLogin(uint16_t opcode, byte* data, uint32_t len)
{
	switch (opcode)
	{
	case OP_ChatMessage:
	{
#ifdef EQNET_DEBUG
		printf("OP_ChatMessage\n");
#endif
		// we receive this to signal that the server's ready to
		// receive login credentials, for whatever reason

		Packet* packet = new Packet(nullptr, 10 + mEQNet->credentialsLen, OP_Login);
		byte* b = packet->getDataBuffer();
		b[0] = 3;
		b[5] = 2;
		memcpy(&b[10], mEQNet->credentials, mEQNet->credentialsLen);

		packet->queue(mEQNet);
		break;
	}

	case OP_LoginAccepted:
	{
#ifdef EQNET_DEBUG
		printf("OP_LoginAccepted\n");
#endif

		if (len < 80)
		{
			queueEvent(mEQNet, EQNET_EVENT_BadCredentials);
			return;
		}

		len -= 10;
		byte* decrypted = EQNet_Decrypt(data + 10, &len);

		Login_ReplyBlock* rb = (Login_ReplyBlock*)decrypted;

		setAccountID(rb->login_acct_id);
		setSessionKey(rb->key);

#ifdef EQNET_DEBUG
		printf("AccountID: %u, SessionKey: %s\n", getAccountID(), getSessionKey().c_str());
#endif

		EQNet_Free(decrypted);

		// send login server list request
		Packet* packet = new Packet(nullptr, 10, OP_ServerListRequest);
		byte* b = packet->getDataBuffer();
		b[0] = 4;

		packet->queue(mEQNet);
		break;
	}

	case OP_ServerListResponse:
	{
#ifdef EQNET_DEBUG
		printf("OP_ServerListResponse\n");
#endif

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
		queueEvent(mEQNet, EQNET_EVENT_AtServerSelect);
		setTimeoutEnabled(false);
		break;
	}

	case OP_PlayEverquestResponse:
	{
		Login_PlayResponse* pr = (Login_PlayResponse*)data;

		bool success = (pr->allowed > 0);
		if (!success)
		{
			queueEvent(mEQNet, EQNET_EVENT_WorldConnectFailed);
			return;
		}

		Address addr;
		addr.ip = mEQNet->selectedServer->ip;
		addr.port = EQNET_WORLD_PORT;

		recordAddress(mEQNet->addressWorld, addr);
		
		freeServerList(mEQNet);

		mEQNet->mode = MODE_LOGIN_TO_WORLD;
		sessionHandoff(addr);
		break;
	}

#ifdef EQNET_DEBUG
	default:
		printf("unhandled login opcode: 0x%0.4X\n", opcode);
		break;
#endif
	}
}

void Connection::processPacketWorldZone(uint16_t opcode, byte* data, uint32_t len)
{
	uint16_t eqnetOpcode = translateOpcodeFromServer(mEQNet, opcode);

	if (eqnetOpcode != EQNET_OP_NONE)
		handlePacket(mEQNet, eqnetOpcode, opcode, data, len);
};
