
#ifndef _EQNET_CRC_H_
#define _EQNET_CRC_H_

#include <cstdint>

namespace CRC
{
	uint16_t calc(void* data, int len, uint32_t key);
	uint16_t calcOutbound(void* data, int len, uint32_t key);
	bool validatePacket(void* packet, uint32_t& len, uint32_t key);
}

#endif//_EQNET_CRC_H_
