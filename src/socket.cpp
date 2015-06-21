
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
		if (err != WSAEWOULDBLOCK)
#else
		err = errno;
		if (err != EWOULDBLOCK)
#endif
		{
			setFatalErrorMessageFormat(mEQNet, "recvPacket: error %i", err);
		}
	}

	return -1;
}

void Socket::sendRaw(const void* in_data, int len)
{
	const char* data = (const char*)in_data;

	do
	{
		int sent = send(mSocket, data, len, 0);

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
			if (err != WSAEWOULDBLOCK)
#else
			err = errno;
			if (err != EWOULDBLOCK)
#endif
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
	// first chunk - proto op, seq, 32-bit length, 504 bytes of data
	// subsequent - proto op, seq, 508 bytes of data

	byte* data = p->getRawBuffer();
	uint32_t len = p->lengthWithOverhead();

	byte buf[SEND_PACKET_MAX_SIZE];
	
	uint16_t* ptr = (uint16_t*)buf;
	*ptr = toNetworkShort(OP_Fragment);

	// first chunk
	ptr[1] = toNetworkShort(getNextSequence());

	// stated len is minus all overhead except app opcode
	uint32_t minus;
	if (p->hasSequence()) // would we ever fragment a non-sequenced packet? gonna get sequenced anyway
		minus = 4; // protocol opcode + seq
	else
		minus = 2; // protocol opcode

	uint32_t* lenPtr = (uint32_t*)(buf + 4);
	*lenPtr = toNetworkLong(len - minus); 

	// copy first 504 bytes
	memcpy(buf + 8, data + minus, 502);
	uint32_t pos = minus + 502;

	// send
	sendPacket(buf, SEND_PACKET_MAX_SIZE_BEFORE_CRC);

	// subsequent chunks
	byte* bufWrite = buf + 4;

	while (pos < len)
	{
		ptr[1] = toNetworkShort(getNextSequence());

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

	if (mEQNet->mode >= MODE_WORLD_TO_ZONE)
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
			if (len > 2)
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

void Socket::processSinglePacketQueue()
{
	Packet* p = mSendQueue[0];

	if (p->lengthWithOverhead() > SEND_PACKET_MAX_SIZE_BEFORE_CRC)
	{
		sendPacketFragmented(p);
	}
	else
	{
		if (p->hasSequence())
		{
			p->setSequence(getNextSequence());
			recordSentPacket(*p);
		}
		sendPacket(p);
	}

	if (!p->isNoDelete())
		delete p;
	mSendQueue.clear();
}

void Socket::processSendQueue()
{
	uint32_t numPackets = mSendQueue.size();

	if (numPackets == 0)
		return;

	if (numPackets == 1)
	{
		processSinglePacketQueue();
		return;
	}

	CombinedPacket comb;

	for (uint32_t i = 0; i < numPackets; ++i)
	{
		Packet* p = mSendQueue[i];
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
	return diff.count() > SOCKET_TIMEOUT_SECONDS;
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
