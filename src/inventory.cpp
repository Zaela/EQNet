
#include "stdafx.h"

void EQNet_DropCursorItem(EQNet* net)
{
	Packet::queueZeroLength(net, EQNET_OP_GroundSpawn);
}
