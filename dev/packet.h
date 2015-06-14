
#ifndef _EQNET_PACKET_H_
#define _EQNET_PACKET_H_

#include <cstdint>
#include "main.h"
#include "socket.h"
#include "network_protocol.h"

class AckManager;

class Packet
{
private:
	uint16_t mLen;
	uint16_t mDataLen;
	uint8_t mDataPos;
	bool mHasCRC;
	bool mCompress;
	byte* mBuffer;

private:
	void writeCRC(uint32_t crcKey);
	void compress(EQNet* net);

public:
	Packet(int data_len, uint16_t opcode, AckManager* ackMgr, int protocol_opcode = OP_Packet,
		bool no_crc = false, bool compressed = true);
	Packet();
	Packet(const Packet& toCopy);
	~Packet();

	uint16_t length() { return mDataLen; }
	uint16_t lengthWithOverhead() { return mLen; }
	byte* getDataBuffer() { return mBuffer + mDataPos; }
	void send(EQNet* net);
	void setSequence(uint16_t seq) { *(uint16_t*)(mBuffer + 2) = toNetworkShort(seq); }
};

struct ReadPacket
{
	ReadPacket() : data(nullptr), len(0) { }

	ReadPacket(byte* in_data, uint32_t in_len) : len(in_len)
	{
		data = new byte[in_len];
		if (in_data)
			memcpy(data, in_data, in_len);
	}

	~ReadPacket()
	{
		if (data)
			delete[] data;
	}

	byte* data;
	uint32_t len;
	uint32_t max_seq;
};

#endif//_EQNET_PACKET_H_
