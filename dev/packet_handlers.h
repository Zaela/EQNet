
#ifndef _EQNET_PACKET_HANDLERS_H_
#define _EQNET_PACKET_HANDLERS_H_

#include <unordered_map>
#include "main.h"

void initPacketHandlers();
void handlePacket(EQNet* net, uint16_t opcode, uint16_t nativeOpcode, byte* data, uint32_t len);

#endif//_EQNET_PACKET_HANDLERS_H_
