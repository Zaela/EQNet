
#include "stdafx.h"

Decoder::Decoder(byte* data) : mData(data), mPos(0)
{

}

uint8_t Decoder::u8()
{
	uint32_t pos = mPos++;
	return *(uint8_t*)(mData + pos);
}

uint16_t Decoder::u16()
{
	uint32_t pos = mPos;
	mPos += sizeof(uint16_t);
	return *(uint16_t*)(mData + pos);
}

uint32_t Decoder::u32()
{
	uint32_t pos = mPos;
	mPos += sizeof(uint32_t);
	return *(uint32_t*)(mData + pos);
}

float Decoder::f32()
{
	uint32_t pos = mPos;
	mPos += sizeof(float);
	return *(float*)(mData + pos);
}

double Decoder::f64()
{
	uint32_t pos = mPos;
	mPos += sizeof(double);
	return *(double*)(mData + pos);
}

void Decoder::strVarLen(char* writePtr, uint32_t writeBound)
{
	const char* read = (char*)(mData + mPos);
	uint32_t len = strlen(read) + 1;
	mPos += len;
	if (len > 1)
		Util::strcpy(writePtr, read, writeBound);
}

void Decoder::strBounded(char* writePtr, uint32_t bound)
{
	const char* read = (char*)(mData + mPos);
	mPos += bound;
	Util::strcpy(writePtr, read, bound);
}

void Decoder::skip(uint32_t bytes)
{
	mPos += bytes;
}

void* Decoder::ptr()
{
	return mData + mPos;
}

void* Decoder::cast(uint32_t len)
{
	void* ret = ptr();
	skip(len);
	return ret;
}

Encoder::Encoder() :
	mData(nullptr),
	mPos(0),
	mCap(0)
{

}

Encoder::Encoder(uint32_t len) :
	mPos(0),
	mCap(len)
{
	alloc();
}

Encoder::~Encoder()
{
	if (mData)
		delete[] mData;
}

void Encoder::alloc()
{
	if (mData) this->~Encoder();
	mData = new byte[mCap];
	memset(mData, 0, mCap);
}

void Encoder::addLen(uint32_t n)
{
	if (!mData)
		mCap += n;
}

void Encoder::copy(byte* to)
{
	memcpy(to, mData, mCap);
}

void Encoder::u8(uint8_t v)
{
	*(uint8_t*)(mData + mPos) = v;
	mPos++;
}

void Encoder::u16(uint16_t v)
{
	*(uint16_t*)(mData + mPos) = v;
	mPos += sizeof(uint16_t);
}

void Encoder::u32(uint32_t v)
{
	*(uint32_t*)(mData + mPos) = v;
	mPos += sizeof(uint32_t);
}

void Encoder::u64(uint64_t v)
{
	*(uint64_t*)(mData + mPos) = v;
	mPos += sizeof(uint64_t);
}

void Encoder::f32(float v)
{
	*(float*)(mData + mPos) = v;
	mPos += sizeof(float);
}

void Encoder::f64(double v)
{
	*(double*)(mData + mPos) = v;
	mPos += sizeof(double);
}

void Encoder::strFixed(const char* str, uint32_t bound)
{
	Util::strcpy((char*)(mData + mPos), str, bound);
	mPos += bound;
}

void Encoder::strVarLen(const char* str)
{
	uint32_t len = strlen(str) + 1;
	memcpy(mData + mPos, str, len);
	mPos += len;
}

void Encoder::skip(uint32_t n)
{
	mPos += n;
}

void* Encoder::ptr()
{
	return mData + mPos;
}

void* Encoder::cast(uint32_t size)
{
	void* ret = mData + mPos;
	mPos += size;
	return ret;
}
