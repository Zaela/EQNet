
#ifndef _EQNET_DECODER_H_
#define _EQNET_DECODER_H_

#include <cstdint>

class Decoder
{
private:
	uint8_t* mData;
	uint32_t mPos;

public:
	Decoder(uint8_t* data);

	uint8_t u8();
	uint16_t u16();
	uint32_t u32();
	uint64_t u64();
	float f32();
	double f64();
	void* ptr();
	void* cast(uint32_t len);

	void strVarLen(char* writePtr, uint32_t writeBound);
	void strBounded(char* writePtr, uint32_t bound);

	void skip(uint32_t bytes);
};

class Encoder
{
private:
	uint8_t* mData;
	uint32_t mPos;
	uint32_t mCap;

public:
	Encoder();
	Encoder(uint32_t len);
	~Encoder();

	void alloc();
	void addLen(uint32_t n);
	void copy(uint8_t* to);

	void u8(uint8_t v);
	void u16(uint16_t v);
	void u32(uint32_t v);
	void u64(uint64_t v);
	void f32(float v);
	void f64(double v);

	void strFixed(const char* str, uint32_t bound);
	void strVarLen(const char* str);

	void skip(uint32_t n);

	void* ptr();
	void* cast(uint32_t size);
};

#endif//_EQNET_DECODER_H_
