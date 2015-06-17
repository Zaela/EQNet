
#ifndef _EQNET_EVENT_H_
#define _EQNET_EVENT_H_

#include "eqnet.h"

#define EQNET_EVENT_QUEUE_DEFAULT_LEN 128

void queueEvent(EQNet* net, int type);
void queueZonePacketEvent(EQNet* net, uint16_t opcode, uint16_t nativeOpcode, byte* nativeData,
		uint32_t nativeLen, int count = 1);
void queueZonePacketEvent(EQNet* net, uint16_t opcode, void* data, uint32_t len,
		uint16_t nativeOpcode, byte* nativeData, uint32_t nativeLen, int count = 1);

#endif//_EQNET_EVENT_H_
