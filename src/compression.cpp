
#include "stdafx.h"

namespace Compression
{
	bool decompressBlock(EQNet* net, byte*& data, uint32_t& len, uint32_t buffer_offset)
	{
		unsigned long buflen = EQNET_COMPRESSION_BUFFER_LEN - buffer_offset;
		if (uncompress(net->compressBuffer + buffer_offset, &buflen, data, len) != 0)
			return false;

		// note that we are returning the static decompress buffer
		data = net->compressBuffer;
		len = (uint32_t)buflen;
		return true;
	}

	bool decompressPacket(EQNet* net, byte*& data, uint32_t& len)
	{
		// data is Socket.mRecvBuf; if decompressed, net->compressBuffer; no delete in either case
		uint16_t opcode = *(uint16_t*)data;
		// skip the opcode and compression flag
		data += 3;
		len -= 3;
		// decompress, leaving the first 2 bytes of the buffer clear
		if (!decompressBlock(net, data, len, 2))
			return false;
		// write the opcode back to the first 2 bytes
		*(uint16_t*)data = opcode;
		len += 2;
		return true;
	}

	void compressBlock(EQNet* net, byte*& data, uint32_t& len)
	{
		if (compressBound(len) > EQNET_COMPRESSION_BUFFER_LEN)
		{
			setFatalErrorMessage(net, "Compression failed - compressBound too long");
			return;
		}

		unsigned long buflen = EQNET_COMPRESSION_BUFFER_LEN;
		if (compress2(net->compressBuffer, &buflen, data, len, 9) != 0)
		{
			setFatalErrorMessage(net, "Compression failed");
			return;
		}

		data = net->compressBuffer;
		len = (uint32_t)buflen;
	}
}
