
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

#include "main.h"
#include "address.h"

#define toNetworkLong htonl
#define toNetworkShort htons
#define toHostLong ntohl
#define toHostShort ntohs

class Socket
{
private:
	static const uint32_t RECV_BUF_SIZE = 8192;

#ifdef _WIN32
	SOCKET mSocket;
#else
	int mSocket;
#endif
	byte mRecvBuf[RECV_BUF_SIZE];

	std::string mIPAddress;
	std::string mPort;

protected:
	EQNet* mEQNet;

public:
	static bool loadLibrary();
	static void closeLibrary();

public:
	Socket(EQNet* net);
	virtual ~Socket();

	void setAddress(Address& addr);
	bool connect();
	void disconnect();
	byte* getBuffer() { return mRecvBuf; }
	int recvPacket();
	int recvWithTimeout(uint32_t milliseconds);
	void sendPacket(void* data, int len);
};

#endif//_EQNET_SOCKET_H_