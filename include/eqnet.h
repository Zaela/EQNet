
/*
** User include file for EQNet
*/

#ifndef _EQNET_H_
#define _EQNET_H_

#include <stdint.h>
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
extern "C" {
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

enum EQNet_ClientVersion
{
	EQNET_CLIENT_TITANIUM,
	EQNET_CLIENT_SECRETS_OF_FAYDWER,
	EQNET_CLIENT_SEEDS_OF_DESTRUCTION,
	EQNET_CLIENT_UNDERFOOT,
	EQNET_CLIENT_REIGN_OF_FEAR,
	EQNET_CLIENT_REIGN_OF_FEAR2
};

EQNET_API void EQNet_SetClientVersion(EQNet*, EQNet_ClientVersion version);

/*
** Errors
*/

#define EQNET_MAX_ERR_LEN 1024

EQNET_API const char* EQNet_GetErrorMessage(EQNet*);

/*
** Login
*/

EQNET_API void                  EQNet_SetLoginServer(EQNet*, const char* ip, uint16_t port);
EQNET_API EQNetBOOL             EQNet_LoginToServerSelect(EQNet*, const char* username, const char* password);
EQNET_API EQNetBOOL             EQNet_LoginToWorld(EQNet*, EQNet_Server* server);

EQNET_API const EQNet_Server*   EQNet_GetServerList(EQNet*, int* count);
EQNET_API EQNetBOOL             EQNet_ServerIsUp(EQNet*, EQNet_Server* server);
EQNET_API EQNetBOOL             EQNet_ServerIsLocked(EQNet*, EQNet_Server* server);

/*
** World
*/

EQNET_API const char*   EQNet_GetServerShortName(EQNet*);
EQNET_API EQNetBOOL     EQNet_WorldToZone(EQNet*, EQNet_Character* character);

EQNET_API const EQNet_Guild*        EQNet_GetGuildList(EQNet*, int* count);
EQNET_API const EQNet_Character*    EQNet_GetCharacterList(EQNet*, int* count);

/*
** Zone
*/

EQNET_API void EQNet_EnablePacketPayloadTranslation(EQNet*, int setting);

/*
** Raw I/O
*/

EQNET_API void EQNet_KeepAlive(EQNet*);
EQNET_API void EQNet_SendRawPacket(EQNet*, uint16_t opcode, const void* data, uint32_t len);
EQNET_API void EQNet_SendRawPacketNativeOpcode(EQNet*, uint16_t opcode, const void* data, uint32_t len);
EQNET_API void EQNet_SendRawBytes(EQNet*, const void* data, uint32_t len);

/*
** Events
*/

EQNET_API EQNetBOOL EQNet_Poll(EQNet*, EQNet_Event* ev);

enum EQNet_EventType
{
	EQNET_FATAL_ERROR,
	EQNET_INVALID_OPERATION,
	/* Connection */
	EQNET_TIMEOUT,
	EQNET_DISCONNECTED,
	/* Login */
	EQNET_LOGIN_BAD_CREDENTIALS,
	EQNET_LOGIN_AT_SERVER_SELECT,
	EQNET_LOGIN_TO_WORLD,
	/* World */
	EQNET_WORLD_CONNECT_FAILED,
	EQNET_WORLD_AT_CHAR_SELECT,
	EQNET_WORLD_TO_ZONE,
	/* Zone */
	EQNET_ZONE_UNAVAILABLE,
	EQNET_ZONE_PACKET
};

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
	uint32_t zone;
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
	union {
		struct {
			int count;
			EQNet_Packet packet;
			EQNet_Packet nativePacket;
		} Packet;
	};
};

#ifdef __cplusplus
}
#endif

#endif/*_EQNET_H_*/
