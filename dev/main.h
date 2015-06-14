
#ifndef _EQNET_MAIN_H_
#define _EQNET_MAIN_H_

#include "eqnet.h"
#include "address.h"
#include "packet.h"
#include "compression.h"
#include "connection.h"
#include <cstdint>
#include <vector>

typedef uint8_t byte;

enum EQNet_Mode
{
	MODE_LOGIN,
	MODE_SERVER_SELECT,
	MODE_WORLD,
	MODE_ZONE
};

struct EQNet
{
	int mode;

	/* Event Queue */
	int eventQueueReadPos;
	int eventQueueWritePos;
	int eventQueueCap;
	EQNet_Event* eventQueue;

	/* Network IO */
	Packet* ackPacket;
	Connection* connection;

	/* Compression */
	byte compressBuffer[EQNET_COMPRESSION_BUFFER_LEN];

	/* Login */
	byte* credentials;
	size_t credentialsLen;
	int serverListCount;
	EQNet_Server* serverList;
	EQNet_Server* selectedServer;
	Address addressLogin;

	/* Error */
	char errMsg[EQNET_MAX_ERR_LEN];
};

#ifdef _WIN32
#define itoa _itoa
#define snprintf _snprintf
#endif

#endif//_EQNET_MAIN_H_
