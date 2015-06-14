
#include "stdafx.h"

EQNet_Event* EQNet_Poll(EQNet* net)
{
	if (net->eventQueueReadPos == 0)
	{
		net->connection->pump();
	}

	if (net->eventQueueReadPos < net->eventQueueWritePos)
	{
		return &net->eventQueue[net->eventQueueReadPos++];
	}

	net->eventQueueReadPos = 0;
	net->eventQueueWritePos = 0;
	return nullptr;
}

static void reallocEvents(EQNet* net)
{
	net->eventQueueCap <<= 1;
	EQNet_Event* ev = new EQNet_Event[net->eventQueueCap];

	memcpy(ev, net->eventQueue, sizeof(EQNet_Event) * net->eventQueueWritePos);
	delete[] net->eventQueue;
	net->eventQueue = ev;
}

static EQNet_Event* nextEvent(EQNet* net)
{
	if (net->eventQueueWritePos == net->eventQueueCap)
	{
		reallocEvents(net);
	}

	return &net->eventQueue[net->eventQueueWritePos++];
}

void queueEvent(EQNet* net, int type)
{
	EQNet_Event* ev = nextEvent(net);
	ev->type = type;
}
