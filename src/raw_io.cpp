
#include "stdafx.h"

void EQNet_KeepAlive(EQNet* net)
{
	net->connection->sendKeepAliveAckNoQueue();
}

void EQNet_SendRawPacket(EQNet* net, uint16_t opcode, const void* data, uint32_t len)
{
	opcode = translateOpcodeToServer(net, opcode);
	EQNet_SendRawPacketNativeOpcode(net, opcode, data, len);
}

void EQNet_SendRawPacketNativeOpcode(EQNet* net, uint16_t opcode, const void* data, uint32_t len)
{
	Packet* packet = new Packet(len, opcode);
	memcpy(packet->getDataBuffer(), data, len);
	packet->queue(net);
}

void EQNet_SendRawBytes(EQNet* net, const void* data, uint32_t len)
{
	if (len > 8192)
		len = 8192;
	net->connection->sendRaw(data, len);
}
