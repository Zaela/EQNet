
#include "stdafx.h"

int EQNet_Init()
{
	initNoDeleteOpcodes();
	initPacketHandlers();
#ifdef _WIN32
	return Socket::loadLibrary();
#else
	return true;
#endif
}

void EQNet_Close()
{
	deinitPacketHandlers();
#ifdef _WIN32
	Socket::closeLibrary();
#endif
}

EQNet* EQNet_Create()
{
	EQNet* net = new EQNet;
	memset(net, 0, sizeof(EQNet));

	net->mode = MODE_LOGIN;
	net->clientVersion = EQNET_DEFAULT_CLIENT_VERSION;
	
	net->eventQueue = new EQNet_Event[EQNET_EVENT_QUEUE_DEFAULT_LEN];
	memset(net->eventQueue, 0, sizeof(EQNet_Event) * EQNET_EVENT_QUEUE_DEFAULT_LEN);
	net->eventQueueCap = EQNET_EVENT_QUEUE_DEFAULT_LEN;

	net->retryMaxAttempts = EQNET_DEFAULT_RETRIES;
	net->translateZonePackets = true;

	net->ackPacket = new Packet(nullptr, 2, OP_NONE, false, OP_Ack);
	net->ackPacket->setNoDelete();
	net->connection = new Connection(net);

	EQNet_SetLoginServer(net, EQNET_DEFAULT_LOGIN_IP, EQNET_DEFAULT_LOGIN_PORT);

	return net;
}

void EQNet_Destroy(EQNet* net)
{
	if (net->ackPacket)
		delete net->ackPacket;
	if (net->eventQueue)
		delete[] net->eventQueue;
	if (net->connection)
		delete net->connection;
	if (net->credentials)
		EQNet_Free(net->credentials);

	if (net->addressZone.ip)
		delete[] net->addressZone.ip;
	if (net->addressLogin.ip)
		delete[] net->addressLogin.ip;
	if (net->addressWorld.ip)
		delete[] net->addressWorld.ip;

	if (net->guildList)
		delete[] net->guildList;
	if (net->charList)
		delete[] net->charList;
	if (net->serverShortName)
		delete[] net->serverShortName;

	if (net->selectedServer)
	{
		freeServer(net->selectedServer);
		delete net->selectedServer;
	}

	freeServerList(net);

	if (net->rng)
		delete net->rng;

	delete net;
}

void EQNet_SetClientVersion(EQNet* net, EQNet_ClientVersion version)
{
	if (net->mode >= MODE_LOGIN_TO_WORLD)
		return;
	net->clientVersion = version;
}

EQNet_ClientVersion EQNet_GetClientVersion(EQNet* net)
{
	return (EQNet_ClientVersion)net->clientVersion;
}

void EQNet_SetMaxRetries(EQNet* net, uint32_t count)
{
	net->retryMaxAttempts = count;
}
