
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
