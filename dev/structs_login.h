
#ifndef _EQNET_STRUCTS_LOGIN_H_
#define _EQNET_STRUCTS_LOGIN_H_

#include <cstdint>

#pragma pack(1)

struct Login_ReplyBlock
{
	char message; //0x01
	char unknown2[7]; //0x00
	uint32_t login_acct_id;
	char key[11]; //10 char + null term;
	uint32_t failed_attempts;
	char unknown3[4]; //0x00, 0x00, 0x00, 0x03
	char unknown4[4]; //0x00, 0x00, 0x00, 0x02
	char unknown5[4]; //0xe7, 0x03, 0x00, 0x00
	char unknown6[4]; //0xff, 0xff, 0xff, 0xff
	char unknown7[4]; //0xa0, 0x05, 0x00, 0x00
	char unknown8[4]; //0x00, 0x00, 0x00, 0x02
	char unknown9[4]; //0xff, 0x03, 0x00, 0x00
	char unknown10[4]; //0x00, 0x00, 0x00, 0x00
	char unknown11[4]; //0x63, 0x00, 0x00, 0x00
	char unknown12[4]; //0x01, 0x00, 0x00, 0x00
	char unknown13[4]; //0x00, 0x00, 0x00, 0x00
	char unknown14[4]; //0x00, 0x00, 0x00, 0x00
};

struct Login_PlayRequest
{
	uint16_t sequence;
	uint32_t unknown[2];
	uint32_t serverRuntimeID;
};

struct Login_PlayResponse
{
	uint8_t sequence;
	uint8_t unknown1[9];
	uint8_t allowed;
	uint16_t message;
	uint8_t unknown2[3];
	uint32_t playServerID;
};

#pragma pack()

#endif//_EQNET_STRUCTS_LOGIN_H_
