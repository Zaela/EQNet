
#ifndef _EQNET_COMPRESSION_H_
#define _EQNET_COMPRESSION_H_

#include <zlib.h>
#include <cstdint>

#include "main.h"
#include "packet.h"

#define EQNET_COMPRESSION_BUFFER_LEN 16384

namespace Compression
{
	bool decompressBlock(EQNet* net, byte*& data, uint32_t& len, uint32_t buffer_offset = 0);
	bool decompressPacket(EQNet* net, byte*& packet, uint32_t& len);
	void compressBlock(EQNet* net, byte*& data, uint32_t& len);
}

#endif//_EQNET_COMPRESSION_H_
