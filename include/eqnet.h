
/*
** User include file for EQNet
*/

#ifndef _EQNET_H_
#define _EQNET_H_

#include <stdint.h>

#ifdef _WIN32
 #ifdef EQNET_BUILD
  #define EQNET_API __declspec(dllexport)
 #else
  #define EQNET_API __declspec(dllimport)
 #endif
#else
 #define EQNET_API extern
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

/*
** Initialization and deinitialization
*/

EQNET_API int       EQNet_Init();
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
** Fatal Errors
*/

#define EQNET_MAX_ERR_LEN 1024

EQNET_API const char* EQNet_GetErrorMessage(EQNet*);

/*
** Login
*/

EQNET_API void                  EQNet_SetLoginServer(EQNet*, const char* ip, uint16_t port);
EQNET_API int                   EQNet_LoginToServerSelect(EQNet*, const char* username, const char* password);
EQNET_API int                   EQNet_LoginToWorld(EQNet*, EQNet_Server* server);

EQNET_API const EQNet_Server*   EQNet_GetServerList(EQNet*, int* count);
EQNET_API int                   EQNet_ServerIsUp(EQNet*, EQNet_Server* server);
EQNET_API int                   EQNet_ServerIsLocked(EQNet*, EQNet_Server* server);

/*
** World
*/

EQNET_API const char*   EQNet_GetServerShortName(EQNet*);
EQNET_API int           EQNet_WorldToZone(EQNet*, EQNet_Character* character);

EQNET_API const EQNet_Guild*        EQNet_GetGuildList(EQNet*, int* count);
EQNET_API const EQNet_Character*    EQNet_GetCharacterList(EQNet*, int* count);

/*
** Raw I/O
*/

EQNET_API void EQNet_SendRawPacket(EQNet*, uint16_t opcode, uint8_t* data, uint32_t len);
EQNET_API void EQNet_SendRawBytes(EQNet*, uint8_t* data, uint32_t len);

/*
** Events
*/

EQNET_API EQNet_Event* EQNet_Poll(EQNet*);

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
	EQNET_WORLD_AT_CHAR_SELECT
};

/*
** Structs
*/

struct EQNet_Server
{
	const char* ip;
	uint32_t listID;
	uint32_t runtimeID;
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
	uint32_t race;
	uint8_t gender;
	uint32_t deity;
	uint32_t zone;
};

struct EQNet_Packet
{
	uint8_t* data;
	uint32_t len;
};

struct EQNet_Event
{
	int type;
	union {
		struct {
			uint16_t opcode;
			EQNet_Packet packet;
			EQNet_Packet nativePacket;
		} Packet;
	};
};

/*
** Opcodes
*/

enum EQNet_OpCodes
{
	EQNET_OP_NONE,
	EQNET_OP_MAX_COUNT
};

#ifdef __cplusplus
}
#endif

#endif/*_EQNET_H_*/
