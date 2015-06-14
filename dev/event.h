
#ifndef _EQNET_EVENT_H_
#define _EQNET_EVENT_H_

#include "eqnet.h"

#define EQNET_EVENT_QUEUE_DEFAULT_LEN 128

void queueEvent(EQNet* net, int type);

#endif//_EQNET_EVENT_H_
