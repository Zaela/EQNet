
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
	static const uint32_t SEQUENCE_MAX = 65536;
	static const uint16_t WINDOW_SIZE = 2048;

	uint32_t mCRCKey;
	uint32_t mSessionID;

	std::chrono::system_clock::time_point mAutoAckTimestamp;
	bool mAutoAckEnabled;

	//these overflow by design
	uint16_t mNextSeq;
	uint16_t mExpectedSeq;
	uint16_t mLastReceivedAck;

	//fragment-related
	bool mBuildingFrag;
	bool mFragEndReceived;
	uint16_t mFragStart;
	uint16_t mFragEnd;
	uint16_t mFragMilestone;

	ReadPacket* mFuturePackets[SEQUENCE_MAX];
	Packet* mSentPackets[SEQUENCE_MAX];

protected:
	std::queue<ReadPacket*> mReadPacketQueue;

protected:
	void setAutoAckEnabled(bool to) { mAutoAckEnabled = to; }

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

public:
	AckManager(EQNet* net);

	void checkAutoAck();

	uint16_t getNextSequence() { return ++mNextSeq; }

	void setCRCKey(uint32_t crc) { mCRCKey = crc; }
	uint32_t getCRCKey() { return mCRCKey; }
	uint32_t getSessionID() { return mSessionID; }

	void receiveAck(uint16_t seq);
	void sendAck(uint16_t seq);
	void sendKeepAliveAck();
	void checkInboundPacket(byte* packet, uint32_t len, uint32_t off = 2);
	void checkInboundFragment(byte* packet, uint32_t len);
	void checkFragmentComplete();
	void checkAfterPacket();
	void recordSentPacket(const Packet& packet, uint16_t seq);
	void queueRawPacket(byte* data, uint32_t len);
	bool resendUnackedPackets();
	void startFragSequence(byte* data, uint16_t seq);

	void sendSessionRequest();
	void sendSessionDisconnect();
	void sendMaxTimeoutLengthRequest();

	void resetAcks();

	bool hasQueuedPackets() { return !mReadPacketQueue.empty(); }
};

#endif//_EQNET_ACKMGR_H_
