
#include "stdafx.h"

void EQNet_SendRawPacket(EQNet* net, uint16_t opcode, byte* data, uint32_t len)
{
	opcode = translateOpcodeToServer(net, opcode);
	Packet* packet = new Packet(len, opcode);
	memcpy(packet->getDataBuffer(), data, len);
	packet->queue(net);
}

void EQNet_SendRawBytes(EQNet* net, byte* data, uint32_t len)
{
	if (len > 8192)
		len = 8192;
	net->connection->sendRaw(data, len);
}
