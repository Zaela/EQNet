
#ifndef _EQNET_ZONE_H_
#define _EQNET_ZONE_H_

#include <unordered_map>
#include "main.h"

void initZonePacketHandlers();
void deinitZonePacketHandlers();
void handleZonePacket(EQNet* net, uint16_t opcode, uint16_t nativeOpcode, byte* data, uint32_t len);

#endif//_EQNET_ZONE_H_
