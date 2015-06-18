
#ifndef _EQNET_ERROR_H_
#define _EQNET_ERROR_H_

#include "eqnet.h"

void setFatalErrorMessage(EQNet*, const char* msg);
void setFatalErrorMessageFormat(EQNet*, const char* fmt, ...);
void setErrorMessage(EQNet*, const char* msg);
void setErrorMessageFormat(EQNet*, const char* fmt, ...);

#endif//_EQNET_ERROR_H_
