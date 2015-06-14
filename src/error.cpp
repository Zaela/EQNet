
#include "stdafx.h"

const char* EQNet_GetErrorMessage(EQNet* net)
{
	return net->errMsg;
}

static void setErrMsg(EQNet* net, const char* msg)
{
	snprintf(net->errMsg, EQNET_MAX_ERR_LEN, "%s", msg);
}

static void setErrFmt(EQNet* net, const char* fmt, va_list args)
{
	vsnprintf(net->errMsg, EQNET_MAX_ERR_LEN, fmt, args);
}

void setFatalErrorMessage(EQNet* net, const char* msg)
{
	setErrMsg(net, msg);
	queueEvent(net, EQNET_FATAL_ERROR);
}

void setFatalErrorMessageFormat(EQNet* net, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	setErrFmt(net, fmt, args);
	va_end(args);
	queueEvent(net, EQNET_FATAL_ERROR);
}

void setInvalidOpMessage(EQNet* net, const char* msg)
{
	setErrMsg(net, msg);
	queueEvent(net, EQNET_INVALID_OPERATION);
}

void setInvalidOpMessageFormat(EQNet* net, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	setErrFmt(net, fmt, args);
	va_end(args);
	queueEvent(net, EQNET_INVALID_OPERATION);
}
