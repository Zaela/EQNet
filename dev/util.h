
#ifndef _EQNET_UTIL_H_
#define _EQNET_UTIL_H_

#include <cstdint>

namespace Util
{
	void strcpy(char* dst, const char* src, uint32_t boundLen);
	char* copyString(const char* src, uint32_t len);
	char* copyString(const char* src);

	float EQ19toFloat(int val);
	int floatToEQ19(float val);
	float EQ13toFloat(int val);
	int floatToEQ13(float val);
	float EQ13PreciseToFloat(int val);
	int floatToEQ13Precise(float val);

	float unpackHeading(int eq19heading);
}

#endif//_EQNET_UTIL_H_
