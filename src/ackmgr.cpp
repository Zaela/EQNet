
#include "stdafx.h"

AckManager::AckManager(EQNet* net) :
	Socket(net),
	mAutoAckEnabled(false),
	mExpectedSeq(0),
	mLastReceivedAck(65535),
	mBuildingFrag(false),
	mReadQueuePos(0)
{
	memset(mFuturePackets, 0, sizeof(ReadPacket*) * SEQUENCE_MAX);
	memset(mSentPackets, 0, sizeof(Packet*) * SEQUENCE_MAX);
}

void AckManager::resetAcks()
{
	resetSequence();
	mExpectedSeq = 0;
	mLastReceivedAck = 65535;
	mBuildingFrag = false;

	for (uint32_t i = 0; i < SEQUENCE_MAX; ++i)
	{
		if (mFuturePackets[i]) delete mFuturePackets[i];
	}

	for (uint32_t i = 0; i < SEQUENCE_MAX; ++i)
	{
		if (mSentPackets[i]) delete mSentPackets[i];
	}

	memset(mFuturePackets, 0, sizeof(ReadPacket*) * SEQUENCE_MAX);
	memset(mSentPackets, 0, sizeof(Packet*) * SEQUENCE_MAX);
}

AckManager::PacketSequence AckManager::compareSequence(uint16_t got, uint16_t expected)
{
	if (got == expected)
		return SEQUENCE_PRESENT;

	if ((got > expected && got < expected + WINDOW_SIZE) || got < (expected - WINDOW_SIZE))
		return SEQUENCE_FUTURE;

	return SEQUENCE_PAST;
}

void AckManager::receiveAck(uint16_t seq)
{
	mLastReceivedAck = seq;

	for (uint16_t count = 0; count < WINDOW_SIZE; ++count)
	{
		if (mSentPackets[seq])
		{
			delete mSentPackets[seq];
			mSentPackets[seq] = nullptr;
		}
		else
			break;
		--seq;
	}
}

void AckManager::sendAck(uint16_t seq)
{
	mEQNet->ackPacket->setSequence(seq);
	mEQNet->ackPacket->queue(mEQNet);
	mAutoAckTimestamp = std::chrono::system_clock::now();
}

void AckManager::sendAckNoQueue(uint16_t seq)
{
	Packet* p = mEQNet->ackPacket;
	p->setSequence(seq);
	sendRaw(p->getRawBuffer(), p->lengthWithOverhead());
}

void AckManager::checkAutoAck()
{
	if (!mAutoAckEnabled)
		return;

	std::chrono::duration<double> diff = std::chrono::system_clock::now() - mAutoAckTimestamp;
	if (diff.count() > 4.0)
		sendKeepAliveAck();
}

void AckManager::sendKeepAliveAck()
{
	sendAck(mExpectedSeq - 1);
}

void AckManager::sendKeepAliveAckNoQueue()
{
	sendAckNoQueue(mExpectedSeq - 1);
}

void AckManager::checkInboundPacket(byte* packet, uint32_t len, uint32_t off)
{
	uint16_t seq = toHostShort(*(uint16_t*)(packet + off));

	switch (compareSequence(seq, mExpectedSeq))
	{
	case SEQUENCE_PRESENT:
	{
		// this is our next expected packet, queue it
		mReadPacketQueue.push_back(new ReadPacket(packet + 2 + off, len - 2 - off));
		++mExpectedSeq;
		// check if we have any packets ahead of this one ready to be processed
		checkAfterPacket();

		sendAck(mExpectedSeq - 1);
		break;
	}
	case SEQUENCE_FUTURE:
	{
		// future packet: remember it for later
		if (mFuturePackets[seq])
			delete mFuturePackets[seq];
		mFuturePackets[seq] = new ReadPacket(packet + 2 + off, len - 2 - off);
		break;
	}
	} // switch
}

void AckManager::checkInboundFragment(byte* packet, uint32_t len, uint32_t off)
{
	uint16_t seq = toHostShort(*(uint16_t*)(packet + off));

	switch (compareSequence(seq, mExpectedSeq))
	{
	case SEQUENCE_PRESENT:
	{
		// this is the starting packet of a fragment sequence
		startFragSequence(packet + off + 2, seq);
		mFuturePackets[seq] = new ReadPacket(packet + off + 2 + 4, len - off - 2 - 4);

		checkFragmentComplete();
		break;
	}
	case SEQUENCE_FUTURE:
	{
		// future packet: remember it for later
		mFuturePackets[seq] = new ReadPacket(packet + off + 2, len - off - 2);

		if (mBuildingFrag)
		{
			checkFragmentComplete();
			// if we didn't finish a packet...
			if (mBuildingFrag && (seq - mFragMilestone) >= 10)
			{
				mFragMilestone = seq;
				sendAck(seq);
			}
		}
		break;
	}
	} // switch
}

int AckManager::copyFragment(ReadPacket* out, int outOffset, uint16_t i)
{
	ReadPacket* sub = mFuturePackets[i];
	mFuturePackets[i] = nullptr;
	uint32_t copy_len = sub->len;
	memcpy(out->data + outOffset, sub->data, copy_len);
	delete sub;
	return copy_len;
}

void AckManager::checkFragmentComplete()
{
	ReadPacket* rp = mFuturePackets[mFragStart];
	if (rp == nullptr)
		return;

	uint32_t len = rp->len;
	uint16_t i = mFragStart + 1;
	while (len < mFragExpectedLen)
	{
		rp = mFuturePackets[i];
		if (rp == nullptr)
			return;
		len += rp->len;
		++i;
	}

	// if we're still here, we had a complete fragment sequence, and we know how long it is
	ReadPacket* out = new ReadPacket(nullptr, len);

	// copy first piece
	uint32_t pos = copyFragment(out, 0, mFragStart);

	// copy subsequence pieces
	i = mFragStart + 1;
	while (pos < mFragExpectedLen)
	{
		pos += copyFragment(out, pos, i);
		++i;
	}

	// add to queue
	mReadPacketQueue.push_back(out);

	// clean up
	mExpectedSeq = i;
	mBuildingFrag = false;
	sendAck(i - 1);

	checkAfterPacket();
	if (mExpectedSeq != i)
		sendAck(mExpectedSeq - 1);
}

void AckManager::checkAfterPacket()
{
	ReadPacket* nextPacket = mFuturePackets[mExpectedSeq];
	if (nextPacket == nullptr)
		return;

	uint16_t i = mExpectedSeq;
	while (nextPacket)
	{
		uint16_t opcode = toHostShort(*(uint16_t*)nextPacket->data);
		if (opcode == OP_Fragment)
		{
			startFragSequence(nextPacket->data, i);
			checkFragmentComplete();
			return;
		}
		else
		{
			mReadPacketQueue.push_back(nextPacket);
			mFuturePackets[i] = nullptr;
			++mExpectedSeq;
		}

		if (i != mExpectedSeq)
		{
			i = mExpectedSeq;
			nextPacket = mFuturePackets[i];
		}
	}
}

void AckManager::sendSessionRequest()
{
	if (!mEQNet->rng)
		mEQNet->rng = new Random();

	mSessionID = (*mEQNet->rng)();
	SessionRequest sr;

	sr.opcode = toNetworkShort(OP_SessionRequest);
	sr.unknown = toNetworkLong(2);
	sr.sessionID = toNetworkLong(mSessionID);
	sr.maxLength = toNetworkLong(512);

	sendRaw(&sr, sizeof(SessionRequest));

	mEQNet->awaitingSession = true;
}

void AckManager::sendSessionDisconnect()
{
	SessionDisconnect sd;

	sd.opcode = toNetworkShort(OP_SessionDisconnect);
	sd.sessionID = toNetworkLong(mSessionID);

	sendPacket((byte*)&sd, 6); // don't count crc
}

void AckManager::sendMaxTimeoutLengthRequest()
{
	SessionStat ss;

	ss.opcode = toNetworkShort(OP_SessionStatRequest);
	// having a high value here maxes out the timeout window to 5 seconds, so we don't have to spam acks quite so much
	ss.last_local_delta = toNetworkLong(5000000);
	// while this one decreases the amount of time the server waits between sending us strings of queued packets
	ss.average_delta = toNetworkLong(25);

	sendRaw(&ss, sizeof(SessionStat));
}

void AckManager::sendOutOfOrderRequest()
{
	Packet* p = new Packet(nullptr, 2, OP_NONE, false, OP_OutOfOrder);
	*(uint16_t*)p->getDataBuffer() = mExpectedSeq;
}

void AckManager::queueRawPacket(byte* packet, uint32_t len)
{
	int offset = 0;
	if (len > 2 && packet[1] == 0xA5) // "not compressed" flag in between the two bytes of the opcode
	{
		packet[1] = packet[0];
		offset = 1;
	}

	mReadPacketQueue.push_back(new ReadPacket(packet + offset, len - offset));
}

bool AckManager::resendUnackedPackets()
{
	int count = 0;
	uint16_t i = mLastReceivedAck + 1;
	for (;;)
	{
		if (mSentPackets[i])
		{
			mSentPackets[i]->queue(mEQNet);
			++count;
		}
		else
		{
			break;
		}
		++i;
	}

	return count > 0;
}

void AckManager::startFragSequence(byte* data, uint16_t seq)
{
	mBuildingFrag = true;
	mFragStart = seq;
	mFragMilestone = seq;

	// some fragmented packets misreport their size by a byte or two,
	// so this may fail in obscure circumstances

	mFragExpectedLen = toHostLong(*(uint32_t*)data);
}

void AckManager::clearReadPacketQueue()
{
	if (mReadPacketQueue.empty())
		return;

	for (ReadPacket* rp : mReadPacketQueue)
		delete rp;

	mReadPacketQueue.clear();
	mReadQueuePos = 0;
}
