
#include "stdafx.h"

int EQNet_Init()
{
#ifdef _WIN32
	return Socket::loadLibrary();
#else
	return true;
#endif
}

void EQNet_Close()
{
#ifdef _WIN32
	Socket::closeLibrary();
#endif
}

EQNet* EQNet_Create()
{
	EQNet* net = new EQNet;
	memset(net, 0, sizeof(EQNet));

	net->mode = MODE_LOGIN;
	
	net->eventQueue = new EQNet_Event[EQNET_EVENT_QUEUE_DEFAULT_LEN];
	net->eventQueueCap = EQNET_EVENT_QUEUE_DEFAULT_LEN;

	net->ackPacket = new Packet(2, OP_NONE, nullptr, OP_Ack, false, false);
	net->connection = new Connection(net);

	EQNet_SetLoginServer(net, "login.eqemulator.net", 5998);

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
	if (net->addressLogin.ip)
		delete[] net->addressLogin.ip;

	if (net->selectedServer)
	{
		freeServer(net->selectedServer);
		delete net->selectedServer;
	}

	freeServerList(net);

	delete net;
}
