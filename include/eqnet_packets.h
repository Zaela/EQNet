
#ifndef _EQNET_PACKETS_H_
#define _EQNET_PACKETS_H_

#include <stdint.h>

/*
** Opcodes
*/

enum EQNet_OpCodes
{
	EQNET_OP_NONE,
	EQNET_OP_PositionUpdate,
	EQNET_OP_Spawn,
	EQNET_OP_Despawn,
	EQNET_OP_HpUpdateExact,
	EQNET_OP_HpUpdatePercent,
	EQNET_OP_ManaEnduranceUpdate,
	EQNET_OP_Message,
	EQNET_OP_MessageEQStr,
	EQNET_OP_HungerThirstUpdate,
	EQNET_OP_PlayerProfile,
	EQNET_OP_PlayerSpawn,
	EQNET_OP_MessageOfTheDay,
	EQNET_OP_TimeUpdate,
	EQNET_OP_MAX_COUNT
};

/*
** Packet structs
*/

typedef uint16_t EQNet_Id;

typedef struct EQNetPacket_PlayerProfile {

} EQNetPacket_PlayerProfile;

typedef struct EQNetPacket_Spawn {
	EQNet_Id mobId;
	uint16_t isNpc : 1;
	uint16_t isCorpse : 1;
	uint16_t isPet : 1;
	uint16_t isInvis : 1;
	uint16_t isGM : 1;
	uint16_t isFlyMode : 1;
	uint16_t isAnonymous : 1;
	uint16_t isRoleplay : 1;
	uint16_t isAfk : 1;
	uint16_t isFindable : 1;
	uint16_t isShowHelm : 1;
	uint16_t isGuildOfficer : 1;
	uint16_t isGuildLeader : 1;
} EQNetPacket_Spawn;

typedef struct EQNetPacket_HpUpdateExact {
	EQNet_Id mobId;
	int cur;
	int max;
} EQNetPacket_HpUpdateExact;

typedef struct EQNetPacket_HpUpdatePercent {
	EQNet_Id mobId;
	int8_t percent;
} EQNetPacket_HpUpdatePercent;

typedef struct EQNetPacket_TimeUpdate {
	uint8_t	hour;
	uint8_t	minute;
	uint8_t	day;
	uint8_t	month;
	uint32_t year;
} EQNetPacket_TimeUpdate;

#endif//_EQNET_PACKETS_H_
