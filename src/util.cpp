
#include "stdafx.h"

namespace Util
{
	void strcpy(char* dst, const char* src, uint32_t boundLen)
	{
		--boundLen;
		uint32_t count = 0;
		while (count < boundLen)
		{
			++count;
			*dst++ = *src;
			if (*src++ == 0)
				return;
		}
		dst[boundLen] = 0;
	}

	char* copyString(const char* src, uint32_t len)
	{
		char* dst = new char[len];
		memcpy(dst, src, len);
		return dst;
	}

	char* copyString(const char* src)
	{
		size_t len = strlen(src) + 1;
		return copyString(src, len);
	}

	float EQ19toFloat(int val)
	{
		return float(val) / float(1 << 3);
	}

	int floatToEQ19(float val)
	{
		return int(val * float(1 << 3));
	}

	float EQ13toFloat(int val)
	{
		return float(val) / float(1 << 2);
	}

	int floatToEQ13(float val)
	{
		return int(val * float(1 << 2));
	}

	float EQ13PreciseToFloat(int val)
	{
		return float(val) / float(1 << 6);
	}

	int floatToEQ13Precise(float val)
	{
		return int(val * float(1 << 6));
	}

	float unpackHeading(int eq19heading)
	{
		return EQ19toFloat(eq19heading) / 256.0f * 360.0f;
	}
}