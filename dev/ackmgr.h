
#ifndef _EQNET_ACKMGR_H_
#define _EQNET_ACKMGR_H_

#include <queue>
#include <chrono>

#include "main.h"
#include "socket.h"
#include "packet.h"

class AckManager : public Socket
{
private:
	static const uint16_t WINDOW_SIZE = 2048;

	uint32_t mSessionID;

	std::chrono::system_clock::time_point mAutoAckTimestamp;
	bool mAutoAckEnabled;

	// these overflow by design
	uint16_t mExpectedSeq;
	uint16_t mLastReceivedAck;

	// fragment-related
	bool mBuildingFrag;
	uint16_t mFragStart;
	uint32_t mFragExpectedLen;
	uint16_t mFragMilestone;

	ReadPacket* mFuturePackets[SEQUENCE_MAX];

protected:
	std::queue<ReadPacket*> mReadPacketQueue;

private:
	enum PacketSequence
	{
		SEQUENCE_PAST,
		SEQUENCE_PRESENT,
		SEQUENCE_FUTURE
	};

	static PacketSequence compareSequence(uint16_t got, uint16_t expected);

private:
	int copyFragment(ReadPacket* out, int outOffset, uint16_t i, int offset = 4);
	void checkFragmentComplete();
	void checkAfterPacket();
	void startFragSequence(byte* data, uint16_t seq);
	bool resendUnackedPackets();
	void sendOutOfOrderRequest();

protected:
	void receiveAck(uint16_t seq);
	void checkInboundPacket(byte* packet, uint32_t len, uint32_t off = 2);
	void checkInboundFragment(byte* packet, uint32_t len);
	void queueRawPacket(byte* data, uint32_t len);
	void resetAcks();

	bool hasQueuedPackets() { return !mReadPacketQueue.empty(); }

public:
	AckManager(EQNet* net);

	void checkAutoAck();

	uint32_t getSessionID() { return mSessionID; }

	void sendAck(uint16_t seq);
	void sendKeepAliveAck();
	void sendAckNoQueue(uint16_t seq);
	void sendKeepAliveAckNoQueue();
	void setAutoAckEnabled(bool to) { mAutoAckEnabled = to; }

	void sendSessionRequest();
	void sendSessionDisconnect();
	void sendMaxTimeoutLengthRequest();
};

#endif//_EQNET_ACKMGR_H_
