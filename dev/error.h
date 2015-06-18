
#ifndef _EQNET_EVENT_Error_H_
#define _EQNET_EVENT_Error_H_

#include "eqnet.h"

void setFatalErrorMessage(EQNet*, const char* msg);
void setFatalErrorMessageFormat(EQNet*, const char* fmt, ...);
void setErrorMessage(EQNet*, const char* msg);
void setErrorMessageFormat(EQNet*, const char* fmt, ...);

#endif//_EQNET_EVENT_Error_H_
