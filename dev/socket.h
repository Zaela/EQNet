
#ifndef _EQNET_SOCKET_H_
#define _EQNET_SOCKET_H_

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#else
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <net/if.h>
#define INVALID_SOCKET -1
#endif

#include <cstdint>
#include <string>
#include <chrono>
#include <vector>

#include "main.h"
#include "address.h"
#include "packet.h"

#define toNetworkLong htonl
#define toNetworkShort htons
#define toHostLong ntohl
#define toHostShort ntohs

class Socket
{
private:
	static const uint32_t RECV_BUF_SIZE = 8192;
	static const uint32_t SEND_PACKET_MAX_SIZE = 512;
	static const uint32_t SEND_PACKET_MAX_SIZE_BEFORE_CRC = 510; // 2 bytes for crc
	static const uint32_t SEND_PACKET_NO_COMPRESSION_THRESHOLD = 40;

protected:
	static const uint32_t SEQUENCE_MAX = 65536;

private:
#ifdef _WIN32
	SOCKET mSocket;
#else
	int mSocket;
#endif
	byte mRecvBuf[RECV_BUF_SIZE];
	std::vector<Packet*> mSendQueue;

	uint16_t mNextSeq;
	uint32_t mCRCKey;
	std::string mIPAddress;
	std::string mPort;

	std::chrono::system_clock::time_point mTimeoutTimestamp;
	bool mTimeOutEnabled;

protected:
	EQNet* mEQNet;

	Packet* mSentPackets[SEQUENCE_MAX];

public:
	static bool loadLibrary();
	static void closeLibrary();

private:
	void sendPacketFragmented(Packet* packet);
	void sendPacket(Packet* packet);
	void sendPacket(CombinedPacket& comb);
	void recordSentPacket(const Packet& packet);
	void processSinglePacketQueue();

	uint16_t getNextSequence() { return ++mNextSeq; }

protected:
	void sendPacket(byte* data, uint32_t len);
	void resetSequence() { mNextSeq = 65535; }

public:
	Socket(EQNet* net);
	virtual ~Socket();

	void setAddress(Address& addr);
	bool connect();
	void disconnect();
	byte* getBuffer() { return mRecvBuf; }
	int recvPacket();
	void sendRaw(const void* data, int len);

	void queuePacket(Packet* packet);
	void processSendQueue();

	void resetTimeout();
	bool isTimedOut();
	void setTimeoutEnabled(bool to) { mTimeOutEnabled = to; }

	void setCRCKey(uint32_t crc) { mCRCKey = crc; }
	uint32_t getCRCKey() { return mCRCKey; }
};

#endif//_EQNET_SOCKET_H_