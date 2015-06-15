
#ifndef _EQNET_CONNECTION_H_
#define _EQNET_CONNECTION_H_

#include "receiver.h"
#include <string>
#include <chrono>

struct EQNet;

class Connection : public Receiver
{
private:
	uint32_t mAccountID;
	std::string mSessionKey;

private:
	void processPackets();
	void processPacketLogin(uint16_t opcode, byte* data, uint32_t len);
	void processPacketWorld(uint16_t opcode, byte* data, uint32_t len);

	void setAccountID(uint32_t id) { mAccountID = id; }
	void setSessionKey(std::string key) { mSessionKey = key; }

public:
	Connection(EQNet* net);
	~Connection();

	void initiateSession();
	void pump();

	uint32_t getAccountID() const { return mAccountID; }
	std::string getSessionKey() const { return mSessionKey; }
};

#endif//_EQNET_CONNECTION_H_
