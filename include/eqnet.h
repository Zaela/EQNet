
/*
** User include file for EQNet
*/

#ifndef _EQNET_H_
#define _EQNET_H_

#include <stdint.h>

#ifdef _WIN32
#define EQNET_EXPORT extern "C" __declspec(dllexport)
#else
#define EQNET_EXPORT extern "C"
#endif

/*
** Typedefs
*/

typedef struct EQNet EQNet;

/*
** Initialization and deinitialization
*/

EQNET_EXPORT int	EQNet_Init();
EQNET_EXPORT void	EQNet_Close();
EQNET_EXPORT EQNet*	EQNet_Create();
EQNET_EXPORT void	EQNet_Destroy(EQNet*);

/*
** Fatal Errors
*/

#define EQNET_MAX_ERR_LEN 1024

EQNET_EXPORT const char*	EQNet_GetErrorMessage(EQNet*);

/*
** Login
*/

typedef struct EQNet_Server {
	const char* ip;
	uint32_t listID;
	uint32_t runtimeID;
	const char* name;
	const char* language;
	const char* region;
	int status;
	uint32_t playerCount;
} EQNet_Server;

EQNET_EXPORT void			EQNet_SetLoginServer(EQNet*, const char* ip, uint16_t port);
EQNET_EXPORT int			EQNet_LoginToServerSelect(EQNet*, const char* username, const char* password);
EQNET_EXPORT int			EQNet_LoginToWorld(EQNet*, EQNet_Server* server);

EQNET_EXPORT EQNet_Server*	EQNet_GetServerList(EQNet*, int* count);
EQNET_EXPORT int			EQNet_ServerIsUp(EQNet*, EQNet_Server* server);
EQNET_EXPORT int			EQNet_ServerIsLocked(EQNet*, EQNet_Server* server);

/*
** Events
*/

typedef struct EQNet_Event {
	int type;
} EQNet_Event;

EQNET_EXPORT EQNet_Event*	EQNet_Poll(EQNet*);

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
	EQNET_WORLD_CONNECT_FAILED
};

#endif/*_EQNET_H_*/
