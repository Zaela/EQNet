
#include "stdafx.h"

void EQNet_KeepAlive(EQNet* net)
{
	net->connection->sendKeepAliveAckNoQueue();
}

void EQNet_SendRawPacket(EQNet* net, uint16_t opcode, const void* data, uint32_t len, int isNativeOpcode)
{
	if (!isNativeOpcode)
		opcode = translateOpcodeToServer(net, opcode);
	Packet* packet = new Packet(nullptr, len, opcode);
	memcpy(packet->getDataBuffer(), data, len);
	packet->queue(net);
}

void EQNet_SendRawBytes(EQNet* net, const void* data, uint32_t len)
{
	net->connection->sendRaw(data, len);
}
