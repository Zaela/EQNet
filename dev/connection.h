
#ifndef _EQNET_CONNECTION_H_
#define _EQNET_CONNECTION_H_

#include "receiver.h"
#include <string>
#include <chrono>

struct EQNet;

class Connection : public Receiver
{
private:
	void processPackets();
	void processPacketLogin(uint16_t opcode, byte* data, uint32_t len);
	void processPacketWorld(uint16_t opcode, byte* data, uint32_t len);

public:
	Connection(EQNet* net);
	~Connection();

	void initiateSession();
	void pump();
};

#endif//_EQNET_CONNECTION_H_
