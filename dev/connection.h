
#ifndef _EQNET_CONNECTION_H_
#define _EQNET_CONNECTION_H_

#include "protocol_receiver.h"
#include <string>
#include <chrono>

struct EQNet;

class Connection : public ProtocolReceiver
{
private:
	void processPackets();
	void processPacketLogin(uint16_t opcode, byte* data, uint32_t len);
	void processPacketWorldZone(uint16_t opcode, byte* data, uint32_t len);

	bool retry();

public:
	Connection(EQNet* net);
	~Connection();

	void initiateSession();
	void pump();
	void sessionHandoff(Address& addr);
};

#endif//_EQNET_CONNECTION_H_
