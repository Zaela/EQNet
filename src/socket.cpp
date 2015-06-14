
#include "stdafx.h"

Socket::Socket(EQNet* net) :
	mSocket(INVALID_SOCKET),
	mEQNet(net)
{

}

Socket::~Socket()
{
	disconnect();
}

void Socket::setAddress(Address& addr)
{
	mIPAddress = addr.ip;

	char portBuf[32];
	itoa(addr.port, portBuf, 10);
	mPort = portBuf;
}

bool Socket::connect()
{
	addrinfo addr;
	memset(&addr, 0, sizeof(addrinfo));
	addr.ai_family = AF_INET;
	addr.ai_socktype = SOCK_DGRAM;

	addrinfo* list;

	int err = getaddrinfo(mIPAddress.c_str(), mPort.c_str(), &addr, &list);
	if (err != 0)
	{
		setFatalErrorMessageFormat(mEQNet, "Socket getaddrinfo failed: %i %s", err, gai_strerror(err));
		return false;
	}

	SOCKET sock = INVALID_SOCKET;
	for (addrinfo* res = list; res != nullptr; res = res->ai_next)
	{
		//get a socket
		sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sock == INVALID_SOCKET)
			continue;
		//set reuseaddr
		char reuse[1] = { 1 };
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, reuse, 1) != 0)
			continue;
		//connect
		if (::connect(sock, res->ai_addr, res->ai_addrlen) != 0)
			continue;
		//set non-blocking
#ifdef _WIN32
		unsigned long nonblock = 1;
		if (ioctlsocket(sock, FIONBIO, &nonblock) == 0)
#else
		if (fcntl(sock, F_SETFL, O_NONBLOCK) == 0)
#endif
			break; //success
		//if we're still here, we're connected but setting non-blocking failed, need to disconnect
#ifdef _WIN32
		closesocket(sock);
#else
		close(sock);
#endif
		sock = INVALID_SOCKET; //in case this is the last round
	}

	freeaddrinfo(list);

	if (sock == INVALID_SOCKET)
	{
		setFatalErrorMessage(mEQNet, "Could not create socket");
		return false;
	}

	mSocket = sock;
	return true;
}

void Socket::disconnect()
{
	if (mSocket != INVALID_SOCKET)
#ifdef _WIN32
		closesocket(mSocket);
#else
		close(mSocket);
#endif
}

int Socket::recvPacket()
{
	int i = recv(mSocket, (char*)mRecvBuf, RECV_BUF_SIZE, 0);

	if (i > 0)
	{
		return i;
	}
	else if (i == -1)
	{
		int err;
#ifdef _WIN32
		err = WSAGetLastError();
		if (err == WSAEWOULDBLOCK)
#else
		err = errno;
		if (err == EWOULDBLOCK)
#endif
		{
			return i;
		}
		else
		{
			setFatalErrorMessageFormat(mEQNet, "recvPacket: error %i", err);
			return -1;
		}
	}

	return -1;
}

int Socket::recvWithTimeout(uint32_t milliseconds)
{
	uint32_t cycles = milliseconds / 20;
	for (uint32_t i = 0; i < cycles; ++i)
	{
		int len = recvPacket();
		if (len > 0)
			return len;

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	return 0;
}

void Socket::sendPacket(void* in_data, int len)
{
	char* data = (char*)in_data;
	int sent;
	do
	{
		sent = send(mSocket, data, len, 0);

		if (sent > 0)
		{
			len -= sent;
			data += sent;
		}
		else if (sent == -1)
		{
			int err;
#ifdef _WIN32
			err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)
#else
			err = errno;
			if (err == EWOULDBLOCK)
#endif
			{
				continue;
			}
			else
			{
				setFatalErrorMessageFormat(mEQNet, "sendPacket: error %i", err);
				return;
			}
		}
	} while (len > 0);
}

bool Socket::loadLibrary()
{
#ifdef _WIN32
	WSAData wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;
#endif
	return true;
}

void Socket::closeLibrary()
{
#ifdef _WIN32
	WSACleanup();
#endif
}
