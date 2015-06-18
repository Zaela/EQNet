
#include "stdafx.h"

static bool pump(EQNet* net)
{
	net->connection->pump();

	// no new events after pumping?
	if (net->eventQueueWritePos == 0)
	{
		net->connection->checkAutoAck();
		return false;
	}

	return true;
}

int EQNet_Poll(EQNet* net, EQNet_Event* ev)
{
	if (net->eventQueueReadPos == 0)
	{
		if (!pump(net))
			return false;
	}

	net->connection->checkAutoAck();

	if (net->eventQueueReadPos < net->eventQueueWritePos)
	{
		*ev = net->eventQueue[net->eventQueueReadPos++];
		return true;
	}

	// reached end of queue
	for (int i = 0; i < net->eventQueueWritePos; ++i)
	{
		EQNet_Event& ev = net->eventQueue[i];
		if (ev.type != EQNET_EVENT_Packet)
			continue;

		if (ev.Packet.packet.data)
		{
			if (!isNoDeleteOpcode(ev.Packet.packet.opcode))
			{
				checkSpecialDestructor(ev.Packet.packet);
				delete[] ev.Packet.packet.data;
			}
		}
	}

	memset(net->eventQueue, 0, sizeof(EQNet_Event) * net->eventQueueWritePos);

	net->eventQueueReadPos = 0;
	net->eventQueueWritePos = 0;
	return false;
}

static void reallocEvents(EQNet* net)
{
	net->eventQueueCap <<= 1;
	EQNet_Event* ev = new EQNet_Event[net->eventQueueCap];

	memset(ev, 0, sizeof(EQNet_Event) * net->eventQueueCap);

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

void queueZonePacketEvent(EQNet* net, uint16_t opcode, uint16_t nativeOpcode, byte* nativeData, uint32_t nativeLen, int count)
{
	EQNet_Event* ev = nextEvent(net);
	ev->type = EQNET_EVENT_Packet;
	ev->Packet.count = count;

	ev->Packet.packet.opcode = opcode;

	ev->Packet.nativePacket.opcode = nativeOpcode;
	ev->Packet.nativePacket.data = nativeData;
	ev->Packet.nativePacket.len = nativeLen;
}

void queueZonePacketEvent(EQNet* net, uint16_t opcode, void* data, uint32_t len,
		uint16_t nativeOpcode, byte* nativeData, uint32_t nativeLen, int count)
{
	EQNet_Event* ev = nextEvent(net);
	ev->type = EQNET_EVENT_Packet;
	ev->Packet.count = count;

	ev->Packet.packet.opcode = opcode;
	ev->Packet.packet.data = (byte*)data;
	ev->Packet.packet.len = len;

	ev->Packet.nativePacket.opcode = nativeOpcode;
	ev->Packet.nativePacket.data = nativeData;
	ev->Packet.nativePacket.len = nativeLen;
}
