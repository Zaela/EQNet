
/*
** User include file for EQNet
*/

#ifndef _EQNET_H_
#define _EQNET_H_

#include <stdint.h>
#include "eqnet_enums.h"
#include "eqnet_packets.h"

#ifdef EQNET_STATIC
 #define EQNET_API 
#else
 #ifdef _WIN32
  #ifdef EQNET_BUILD
   #define EQNET_API __declspec(dllexport)
  #else
   #define EQNET_API __declspec(dllimport)
  #endif
 #else
  #define EQNET_API extern
 #endif
#endif

#ifdef __cplusplus
 #define EQNET_DEFAULT(val) = val
 #define NULL 0
extern "C" {
#else
 #define EQNET_DEFAULT(val)
#endif

/*
** Typedefs
*/

typedef struct EQNet EQNet;

typedef struct EQNet_Server     EQNet_Server;
typedef struct EQNet_Guild      EQNet_Guild;
typedef struct EQNet_Character  EQNet_Character;
typedef struct EQNet_Packet     EQNet_Packet;
typedef struct EQNet_Event      EQNet_Event;

typedef int EQNetBOOL;

/*
** Initialization and deinitialization
*/

EQNET_API EQNetBOOL EQNet_Init();
EQNET_API void      EQNet_Close();
EQNET_API EQNet*    EQNet_Create();
EQNET_API void      EQNet_Destroy(EQNet*);

EQNET_API void                EQNet_SetClientVersion(EQNet*, EQNet_ClientVersion version);
EQNET_API EQNet_ClientVersion EQNet_GetClientVersion(EQNet*);
EQNET_API void                EQNet_SetMaxRetries(EQNet*, uint32_t count);
EQNET_API void                EQNet_EnablePacketTranslation(EQNet*, EQNetBOOL setting);

/*
** Errors
*/

#define EQNET_MAX_ERR_LEN 1024

EQNET_API const char* EQNet_GetErrorMessage(EQNet*);

/*
** Login
*/

EQNET_API void                  EQNet_SetLoginServer(EQNet*, const char* ip, uint16_t port EQNET_DEFAULT(5998));
EQNET_API EQNetBOOL             EQNet_LoginToServerSelect(EQNet*, const char* username, const char* password);
EQNET_API EQNetBOOL             EQNet_LoginToWorld(EQNet*, const EQNet_Server* server);

EQNET_API const EQNet_Server*   EQNet_GetServerList(EQNet*, int* count);
EQNET_API EQNetBOOL             EQNet_ServerIsUp(EQNet*, const EQNet_Server* server);
EQNET_API EQNetBOOL             EQNet_ServerIsLocked(EQNet*, const EQNet_Server* server);

/*
** World
*/

EQNET_API EQNetBOOL     EQNet_WorldToZone(EQNet*, const EQNet_Character* character);
EQNET_API const char*   EQNet_GetServerShortName(EQNet*);

EQNET_API const EQNet_Guild*        EQNet_GetGuildList(EQNet*, int* count);
EQNET_API const EQNet_Character*    EQNet_GetCharacterList(EQNet*, int* count);

/*
** Chat
*/

EQNET_API void EQNet_SendChatMessage(EQNet*, const char* message, EQNet_ChatChannel channel EQNET_DEFAULT(EQNET_CHAT_Say),
	uint32_t language EQNET_DEFAULT(0), const char* tellRecipient EQNET_DEFAULT(NULL));

/*
** Combat
*/

EQNET_API void EQNet_SetTarget(EQNet*, EQNet_Id target);
EQNET_API void EQNet_SetAutoAttacking(EQNet*, EQNetBOOL setting);
EQNET_API void EQNet_SetAutoFiring(EQNet*, EQNetBOOL setting);
EQNET_API void EQNet_Assist(EQNet*, EQNet_Id target);
EQNET_API void EQNet_Consider(EQNet*, EQNet_Id target);
EQNET_API void EQNet_UseSkill(EQNet*, EQNet_Skill skill, EQNet_Id target EQNET_DEFAULT(0));

/*
** Inventory
*/

EQNET_API void EQNet_DropCursorItem(EQNet*);

/*
** Raw I/O
*/

EQNET_API void EQNet_KeepAlive(EQNet*);
EQNET_API void EQNet_Flush(EQNet*);
EQNET_API void EQNet_SendRawPacket(EQNet*, uint16_t opcode, const void* data, uint32_t len, EQNetBOOL isNativeOpcode EQNET_DEFAULT(0));
EQNET_API void EQNet_SendRawBytes(EQNet*, const void* data, uint32_t len);

/*
** Events
*/

EQNET_API EQNetBOOL EQNet_Poll(EQNet*, EQNet_Event* ev);

/*
** Structs
*/

struct EQNet_Server
{
	const char* ip;
	uint32_t listId;
	uint32_t runtimeId;
	const char* name;
	const char* language;
	const char* region;
	int status;
	uint32_t playerCount;
};

struct EQNet_Guild
{
	int id;
	char name[64];
};

struct EQNet_Character
{
	char name[64];
	uint8_t level;
	uint8_t charClass;
	uint8_t gender;
	uint32_t race;
	uint32_t deity;
	uint16_t zoneId;
	uint16_t instanceId;
};

struct EQNet_Packet
{
	uint16_t opcode;
	uint32_t len;
	uint8_t* data;
};

struct EQNet_Event
{
	int type;

	int count;
	EQNet_Packet packet;
	EQNet_Packet nativePacket;
};

#ifdef __cplusplus
}
#endif

#endif/*_EQNET_H_*/
