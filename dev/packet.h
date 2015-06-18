
#ifndef _EQNET_PACKET_H_
#define _EQNET_PACKET_H_

#include <cstdint>
#include <cstring>
#include "main.h"
#include "network_protocol.h"

typedef uint8_t byte;

class Packet
{
private:
	uint32_t mLen;
	uint32_t mDataLen;
	uint16_t mSeq;
	uint8_t mDataPos;
	bool mNoDelete;
	bool mHasSeq;
	byte* mBuffer;

public:
	Packet(EQNet* net, uint32_t data_len, uint16_t opcode, bool hasSequence = true, int protocol_opcode = OP_Packet);
	Packet();
	Packet(const Packet& toCopy);
	~Packet();

	uint32_t length() { return mDataLen; }
	uint32_t lengthWithOverhead() { return mLen; }
	byte* getDataBuffer() { return mBuffer + mDataPos; }
	byte* getRawBuffer() { return mBuffer; }
	void queue(EQNet* net);
	bool hasSequence() { return mHasSeq; }
	void setSequence(uint16_t seq);
	uint16_t getSequence() const { return mSeq; }

	uint16_t getProtocolOpcode();
	uint16_t getOpcode();

	bool isNoDelete() { return mNoDelete; }
	void setNoDelete() { mNoDelete = true; }

	static void queueZeroLength(EQNet* net, uint16_t opcode);
	static void queueFourByte(EQNet* net, uint16_t opcode, uint32_t value);
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
};

class CombinedPacket
{
private:
	static const uint32_t MAX_SPACE = 510; // 512 minus CRC
	static const uint32_t MAX_SINGLE_PACKET_LEN = 255;

private:
	uint16_t mPacketCount;
	uint16_t mLen;
	byte mBuffer[512];
	Packet* mFirstPacket;

public:
	CombinedPacket();

	bool addPacket(Packet* packet);
	void clear();

	byte* getBuffer() { return mBuffer; }
	uint16_t length() { return mLen; }
	uint16_t getPacketCount() { return mPacketCount; }
	Packet* getFirstPacket() { return mFirstPacket; }
};

#endif//_EQNET_PACKET_H_
