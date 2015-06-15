
#ifndef _EQNET_OPCODE_EQNET_H_
#define _EQNET_OPCODE_EQNET_H_

#include <cstdint>
#include "main.h"
#include "eqnet.h"

struct OpCodeTranslation
{
	uint16_t from;
	uint16_t to;
};

enum Unexposed_OpCodes
{
	EQNET_OP_SendLoginInfo = EQNET_OP_MAX_COUNT,
	EQNET_OP_GuildsList,
	EQNET_OP_LogServer,
	EQNET_OP_ApproveWorld,
	EQNET_OP_SendCharInfo,
	EQNET_OP_EnterWorld,
	EQNET_OP_PostEnterWorld,
	EQNET_OP_ExpansionInfo,
	EQNET_OP_AckPacket,
	EQNET_OP_MOTD,
	EQNET_OP_SetChatServer,
	EQNET_OP_SetChatServer2,
	EQNET_OP_ZoneUnavailable,
	EQNET_OP_ZoneServerInfo
};

uint16_t translateOpcodeFromServer(EQNet*, uint16_t opcode);
uint16_t translateOpcodeToServer(EQNet*, uint16_t opcode);

#endif//_EQNET_OPCODE_EQNET_H_
