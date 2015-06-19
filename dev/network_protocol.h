
#ifndef _EQNET_NETWORK_PROTOCOL_H_
#define _EQNET_NETWORK_PROTOCOL_H_

#include <cstdint>

#pragma pack(1)

struct SessionRequest
{
	uint16_t opcode;
	uint32_t unknown;
	uint32_t sessionID;
	uint32_t maxLength;
};

struct SessionResponse
{
	uint32_t session;
	uint32_t key;
	uint8_t unknownA;
	uint8_t format;
	uint8_t unknownB;
	uint32_t maxLength;
	uint32_t unknownC;
};

struct SessionStat
{
	uint16_t opcode;
	uint16_t requestID;
	uint32_t last_local_delta;
	uint32_t average_delta;
	uint32_t low_delta;
	uint32_t high_delta;
	uint32_t last_remote_delta;
	uint64_t packets_sent;
	uint64_t packets_received;
};

struct SessionDisconnect
{
	uint16_t opcode;
	uint32_t sessionID;
	uint16_t crc;
};

#pragma pack()

#define OP_NONE					0x00
#define OP_SessionRequest		0x01
#define OP_SessionReady			0x01
#define OP_SessionResponse		0x02
#define OP_Combined				0x03
#define OP_SessionDisconnect	0x05
#define OP_KeepAlive			0x06
#define OP_SessionStatRequest	0x07
#define OP_SessionStatResponse	0x08
#define OP_Packet				0x09
#define OP_Fragment				0x0D
#define OP_OutOfOrder			0x11
#define OP_Ack					0x15

#endif//_EQNET_NETWORK_PROTOCOL_H_
