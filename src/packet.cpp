
#include "stdafx.h"

Packet::Packet(int data_len, uint16_t opcode, AckManager* ackMgr, int protocol_opcode, bool no_crc, bool compressed)
	:
	mBuffer(nullptr)
{
	uint16_t len = data_len + 8;
	uint8_t dataPos = 6;
	bool hasCRC = true;
	if (ackMgr == nullptr)
	{
		len -= 2;
		dataPos = 4;
	}
	if (no_crc)
	{
		len -= 2;
		hasCRC = false;
	}

	byte* buf = new byte[len];
	memset(buf, 0, len);

	mLen = len;
	mDataLen = data_len;
	mDataPos = dataPos;
	mHasCRC = hasCRC;
	mCompress = compressed;
	mBuffer = buf;

	uint16_t* ptr = (uint16_t*)buf;
	*ptr = toNetworkShort(protocol_opcode);

	if (opcode != OP_NONE)
	{
		ptr[ackMgr ? 2 : 1] = opcode;
	}
	else
	{
		mLen -= 2;
		mDataPos -= 2;
	}

	if (ackMgr)
	{
		uint16_t seq = toNetworkShort(ackMgr->getNextSequence());
		ptr[1] = seq;
		ackMgr->recordSentPacket(*this, seq);
	}
}

Packet::Packet() :
mLen(0),
mDataLen(0),
mDataPos(0),
mHasCRC(false),
mBuffer(nullptr)
{

}

Packet::Packet(const Packet& toCopy) :
mLen(toCopy.mLen),
mDataLen(toCopy.mDataLen),
mDataPos(toCopy.mDataPos),
mHasCRC(toCopy.mHasCRC)
{
	mBuffer = new byte[mLen];
	memcpy(mBuffer, toCopy.mBuffer, mLen);
}

Packet::~Packet()
{
	if (mBuffer)
		delete[] mBuffer;
}

void Packet::writeCRC(uint32_t crcKey)
{
	if (mBuffer == nullptr)
		return;
	uint16_t len = mLen - 2;
	uint16_t* ptr = (uint16_t*)(mBuffer + len);
	*ptr = CRC::calcOutbound(mBuffer, len, crcKey);
}

void Packet::send(EQNet* net)
{
	if (mCompress)
		compress(net);
	if (mHasCRC)
		writeCRC(net->connection->getCRCKey());
	net->connection->sendPacket(mBuffer, mLen);
}

void Packet::compress(EQNet* net)
{
	// compress everything except the protocol opcode and crc space
	// I think every compressed packet also has a crc...
	byte* data = mBuffer + 2;
	uint32_t len = mLen - 4;

	Compression::compressBlock(net, data, len);

	//check results - we add 1 byte for the compression flag
	if (len > (uint32_t)(mLen - 5))
	{
		//compression increased our size, need to realloc buffer
		uint16_t opcode = *(uint16_t*)mBuffer;
		delete[] mBuffer;
		mBuffer = new byte[len + 5];
		*(uint16_t*)mBuffer = opcode;
	}

	mBuffer[2] = 'Z';
	memcpy(&mBuffer[3], data, len);
	mLen = len + 5;
}
