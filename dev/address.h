
#ifndef _EQNET_ADDRESS_H_
#define _EQNET_ADDRESS_H_

#include <cstdint>
#include <cstring>

struct Address
{
	const char* ip;
	uint16_t port;
};

void recordAddress(Address& addr, const char* ip, uint16_t port);
void recordAddress(Address& addr, Address& other);

#endif//_EQNET_ADDRESS_H_
