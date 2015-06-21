
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
	float f32();
	double f64();
	void* ptr();
	void* cast(uint32_t len);

	void strVarLen(char* writePtr, uint32_t writeBound);
	void strBounded(char* writePtr, uint32_t bound);

	void skip(uint32_t bytes);
};

#endif//_EQNET_DECODER_H_
