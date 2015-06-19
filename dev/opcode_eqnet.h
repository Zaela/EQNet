
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
	/* World and char select */
	EQNET_OP_SendLoginInfo = EQNET_OP_MAX_COUNT,
	EQNET_OP_GuildsList,
	EQNET_OP_LogServer,
	EQNET_OP_ApproveWorld,
	EQNET_OP_SendCharInfo,
	EQNET_OP_EnterWorld,
	EQNET_OP_PostEnterWorld,
	EQNET_OP_ExpansionInfo,
	EQNET_OP_AckPacket,
	EQNET_OP_SetChatServer,
	EQNET_OP_SetChatServer2,
	EQNET_OP_ZoneUnavailable,
	EQNET_OP_ZoneServerInfo,
	/* Zone-in */
	EQNET_OP_ZoneSpawns,
	EQNET_OP_ReqNewZone,
	EQNET_OP_ReqClientSpawn,
	EQNET_OP_ClientReady,
	/* Toggles */
	EQNET_OP_AutoAttack,
	EQNET_OP_AutoFire,
	/* Targetting */
	EQNET_OP_TargetCommand,
	/* Skills */
	EQNET_OP_CombatAbility,
	EQNET_OP_Hide,
	EQNET_OP_Sneak,
	EQNET_OP_Forage,
	EQNET_OP_Begging,
	EQNET_OP_Taunt,
	EQNET_OP_SenseHeading,
	EQNET_OP_SenseTraps,
	EQNET_OP_DisarmTraps,
	EQNET_OP_Fishing,
	EQNET_OP_INTERNAL_MAX_COUNT
};

uint16_t translateOpcodeFromServer(EQNet*, uint16_t opcode);
uint16_t translateOpcodeToServer(EQNet*, uint16_t opcode);
void initNoDeleteOpcodes();
void setNoDeleteOpcode(uint16_t opcode);
uint32_t isNoDeleteOpcode(uint16_t opcode);
void checkSpecialDestructor(EQNet_Packet& packet);

#endif//_EQNET_OPCODE_EQNET_H_
