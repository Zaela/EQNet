
#include "stdafx.h"

Packet::Packet(EQNet* net, uint32_t data_len, uint16_t opcode, bool hasSequence, int protocol_opcode) :
	mNoDelete(false),
	mHasSeq(hasSequence),
	mBuffer(nullptr)
{
	uint32_t len = data_len + 6;
	uint8_t dataPos = 6;
	uint8_t opOffset = 0;

	if (!mHasSeq)
	{
		len -= 2;
		dataPos = 4;
	}

	// opcodes with a low-order byte of 0 are preceded with an extra 0 byte
	if (opcode != OP_NONE && (opcode & 0x00ff) == 0)
	{
		opOffset = 1;
		++len;
	}

	byte* buf = new byte[len + 2]; // 2 extra unrecorded bytes to potentially hold a crc
	memset(buf, 0, len);

	mLen = len;
	mDataLen = data_len;
	mDataPos = dataPos;
	mBuffer = buf;

	uint16_t* ptr = (uint16_t*)buf;
	*ptr = toNetworkShort(protocol_opcode);

	if (opcode != OP_NONE)
	{
		if (net)
			opcode = translateOpcodeToServer(net, opcode);
		ptr[(mHasSeq ? 2 : 1) + opOffset] = opcode;
	}
	else
	{
		mLen -= 2;
		mDataPos -= 2;
	}
}

Packet::Packet() :
	mLen(0),
	mDataLen(0),
	mSeq(0),
	mDataPos(0),
	mNoDelete(false),
	mBuffer(nullptr)
{

}

Packet::Packet(const Packet& toCopy) :
	mLen(toCopy.mLen),
	mDataLen(toCopy.mDataLen),
	mSeq(toCopy.mSeq),
	mDataPos(toCopy.mDataPos),
	mNoDelete(false)
{
	mBuffer = new byte[mLen + 2];
	memcpy(mBuffer, toCopy.mBuffer, mLen);
}

Packet::~Packet()
{
	if (mBuffer)
		delete[] mBuffer;
}

void Packet::setSequence(uint16_t seq)
{
	mSeq = seq;
	*(uint16_t*)(mBuffer + 2) = toNetworkShort(seq);
}

void Packet::queue(EQNet* net)
{
	net->connection->queuePacket(this);
}

void Packet::queueZeroLength(EQNet* net, uint16_t opcode)
{
	Packet* p = new Packet(net, 0, opcode);
	p->queue(net);
}

void Packet::queueFourByte(EQNet* net, uint16_t opcode, uint32_t value)
{
	Packet* p = new Packet(net, sizeof(uint32_t), opcode);
	*(uint32_t*)p->getDataBuffer() = value;
	p->queue(net);
}

// for debug messages
uint16_t Packet::getProtocolOpcode()
{
	return toHostShort(*(uint16_t*)getRawBuffer());
}

uint16_t Packet::getOpcode()
{
	return *(uint16_t*)(getDataBuffer() - 2);
}

////////////////////////////////////////////////////////////////////

CombinedPacket::CombinedPacket() :
	mPacketCount(0),
	mLen(2),
	mFirstPacket(nullptr)
{
	uint16_t* ptr = (uint16_t*)mBuffer;
	*ptr = toNetworkShort(OP_Combined);
}

bool CombinedPacket::addPacket(Packet* p)
{
	uint32_t len = p->lengthWithOverhead();

	if (len > MAX_SINGLE_PACKET_LEN)
		return false;

	uint32_t addLen = mLen + len + 1;
	if (addLen > MAX_SPACE)
		return false;

	if (mFirstPacket == nullptr)
		mFirstPacket = p;

	mBuffer[mLen] = (uint8_t)len;
	memcpy(&mBuffer[mLen + 1], p->getRawBuffer(), len);

	mLen = (uint16_t)addLen;
	++mPacketCount;
	return true;
}

void CombinedPacket::clear()
{
	mPacketCount = 0;
	mLen = 2;
	mFirstPacket = nullptr;
}
