
#include "stdafx.h"

Socket::Socket(EQNet* net) :
	mSocket(INVALID_SOCKET),
	mEQNet(net),
	mNextSeq(65535)
{

}

Socket::~Socket()
{
	disconnect();

	for (Packet* p : mSendQueue)
	{
		if (!p->isNoDelete())
			delete p;
	}
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
		resetTimeout();
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

void Socket::sendRaw(void* in_data, int len)
{
	char* data = (char*)in_data;
	//for (int i = 0; i < len; ++i)
	//	printf("%0.2X ", (byte)data[i]);
	//printf("\n");
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

void Socket::queuePacket(Packet* packet)
{
	mSendQueue.push_back(packet);
}

void Socket::sendPacketFragmented(Packet* p)
{
	// fragment packets:
	// first chunk - proto op, seq, 32-bit length, 502 bytes of data, 2 byte crc
	// subsequent - proto op, seq, 506 bytes of data, 2 byte crc

	byte* data = p->getDataBuffer();
	uint32_t len = p->length();

	byte buf[SEND_PACKET_MAX_SIZE];
	
	uint16_t* ptr = (uint16_t*)buf;
	*ptr = OP_Fragment;

	// first chunk
	ptr[1] = getNextSequence();

	uint32_t* lenPtr = (uint32_t*)(data + 4);
	*lenPtr = len;

	uint32_t pos = 0;
	// copy first 502 bytes
	memcpy(buf + 8, data, 502);
	pos += 502;

	// send
	sendPacket(buf, SEND_PACKET_MAX_SIZE_BEFORE_CRC);

	// subsequent chunks
	byte* bufWrite = buf + 4;

	while (pos < len)
	{
		ptr[1] = getNextSequence();

		uint32_t chunkLen = len - pos;
		if (chunkLen > 506)
			chunkLen = 506;

		memcpy(bufWrite, data + pos, chunkLen);

		sendPacket(buf, chunkLen + 4);
		pos += chunkLen;
	}
}

void Socket::sendPacket(byte* data, uint32_t len)
{
	byte buf[SEND_PACKET_MAX_SIZE];

	if (mEQNet->mode >= MODE_ZONE)
	{
		// protocol opcode
		uint16_t* ptr = (uint16_t*)buf;
		*ptr = *(uint16_t*)data;

		if (len <= SEND_PACKET_NO_COMPRESSION_THRESHOLD)
		{
			// not worth compressing, but we need to add the 'not compressed' flag
			// protocol opcode + 0xa5 + everything else

			// not compressed flag
			buf[2] = 0xa5;

			// everything else
			memcpy(buf + 3, data + 2, len - 2);

			++len; // add compressed flag
		}
		else
		{
			// do compression
			// protocol opcode + 'Z' + compressed everything else

			// compressed flag
			buf[2] = 'Z';

			// everythign else, compressed
			len -= 2;
			data += 2;
			Compression::compressBlock(mEQNet, data, len);
			memcpy(buf + 3, data, len);

			len += 3; // add protocol opcode back, plus compressed flag
		}

		data = buf;
	}

	// write crc
	// all packets are allocated with 2 extra bytes at the end to hold the CRC
	uint16_t* crc = (uint16_t*)(data + len);
	*crc = CRC::calcOutbound(data, len, getCRCKey());

	// send
	sendRaw(data, len + 2);
}

void Socket::sendPacket(Packet* p)
{
	sendPacket(p->getRawBuffer(), p->lengthWithOverhead());
}

void Socket::sendPacket(CombinedPacket& comb)
{
	uint16_t num = comb.getPacketCount();
	if (num == 0)
		return;

	if (num == 1)
		sendPacket(comb.getFirstPacket());
	else
		sendPacket(comb.getBuffer(), comb.length());

	comb.clear();
}

void Socket::processSendQueue()
{
	if (mSendQueue.empty())
		return;

	Packet* p;
	uint32_t numPackets = mSendQueue.size();

	if (numPackets == 1)
	{
		p = mSendQueue[0];
		sendPacket(p);
		if (!p->isNoDelete())
			delete p;
		mSendQueue.clear();
		return;
	}

	CombinedPacket comb;

	for (uint32_t i = 0; i < numPackets; ++i)
	{
		p = mSendQueue[i];
		uint16_t len = p->lengthWithOverhead();

		if (len > SEND_PACKET_MAX_SIZE_BEFORE_CRC)
		{
			sendPacket(comb);
			sendPacketFragmented(p);
			continue;
		}

		if (p->hasSequence())
		{
			p->setSequence(getNextSequence());
			recordSentPacket(*p);
		}

		if (!comb.addPacket(p))
		{
			sendPacket(comb);
			sendPacket(p);
		}
	}

	sendPacket(comb);

	for (Packet* p : mSendQueue)
	{
		if (!p->isNoDelete())
			delete p;
	}

	mSendQueue.clear();
}

void Socket::recordSentPacket(const Packet& packet)
{
	//copy constructor
	mSentPackets[packet.getSequence()] = new Packet(packet);
}

void Socket::resetTimeout()
{
	mTimeoutTimestamp = std::chrono::system_clock::now();
}

bool Socket::isTimedOut()
{
	if (!mTimeOutEnabled)
		return false;
	std::chrono::duration<double> diff = std::chrono::system_clock::now() - mTimeoutTimestamp;
	return diff.count() > 5.0;
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
