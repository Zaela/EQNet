
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
			*dst++ = *src++;
			if (*src == 0)
				return;
		}
		dst[boundLen] = 0;
	}
}