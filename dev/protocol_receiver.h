
#ifndef _EQNET_PROTOCOL_RECEIVER_H_
#define _EQNET_PROTOCOL_RECEIVER_H_

#include <cstdint>
#include "main.h"
#include "ackmgr.h"

class ProtocolReceiver : public AckManager
{
private:
	uint32_t mAccountID;
	std::string mSessionKey;

private:
	bool validatePacket(byte*& packet, uint32_t& len, uint32_t& offset, bool fromCombined = false);
	void readPacket(byte* data, uint32_t len, bool fromCombined = false);

protected:
	ProtocolReceiver(EQNet* net);

	bool handleProtocol(uint32_t len);
	void setAccountID(uint32_t id) { mAccountID = id; }
	void setSessionKey(std::string key) { mSessionKey = key; }
	uint32_t getAccountID() const { return mAccountID; }
	std::string getSessionKey() const { return mSessionKey; }
};

#endif//_EQNET_PROTOCOL_RECEIVER_H_
