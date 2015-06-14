
#ifndef _EQNET_RECEIVER_H_
#define _EQNET_RECEIVER_H_

#include <cstdint>
#include "main.h"
#include "ackmgr.h"

class Receiver : public AckManager
{
private:
	bool validatePacket(byte*& packet, uint32_t& len, uint32_t& offset, bool fromCombined = false);
	void readPacket(byte* data, uint32_t len, bool fromCombined = false);

public:
	Receiver(EQNet* net);

	bool handleProtocol(uint32_t len);
};

#endif//_EQNET_RECEIVER_H_
