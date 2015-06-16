
#include "stdafx.h"

void recordAddress(Address& addr, const char* ip, uint16_t port)
{
	size_t len = strlen(ip) + 1;
	char* copyIP = new char[len];
	memcpy(copyIP, ip, len);

	if (addr.ip)
		delete[] addr.ip;

	addr.ip = copyIP;
	addr.port = port;
}

void recordAddress(Address& addr, Address& other)
{
	recordAddress(addr, other.ip, other.port);
}
