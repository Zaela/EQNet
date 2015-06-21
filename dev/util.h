
#ifndef _EQNET_UTIL_H_
#define _EQNET_UTIL_H_

#include <cstdint>

namespace Util
{
	void strcpy(char* dst, const char* src, uint32_t boundLen);
	char* copyString(const char* src, uint32_t len);
	char* copyString(const char* src);
}

#endif//_EQNET_UTIL_H_
