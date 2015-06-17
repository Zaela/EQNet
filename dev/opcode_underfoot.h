
#ifndef _EQNET_OPCODES_UNDERFOOT_H_
#define _EQNET_OPCODES_UNDERFOOT_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace Underfoot
{
	static const OpCodeTranslation toCanonical[] = {
			/* World packets */
			{ 0x13da, EQNET_OP_SendLoginInfo },
			{ 0x5b0b, EQNET_OP_GuildsList },
			{ 0x6f79, EQNET_OP_LogServer },
			{ 0x86c7, EQNET_OP_ApproveWorld },
			{ 0x4200, EQNET_OP_SendCharInfo },
			{ 0x51b9, EQNET_OP_EnterWorld },
			{ 0x5d32, EQNET_OP_PostEnterWorld },
			{ 0x7e4d, EQNET_OP_ExpansionInfo },
			/* Char select packets */
			{ 0x3594, EQNET_OP_AckPacket },
			{ 0x7629, EQNET_OP_MessageOfTheDay },
			{ 0x7d90, EQNET_OP_SetChatServer },
			{ 0x158f, EQNET_OP_SetChatServer2 },
			{ 0x3288, EQNET_OP_ZoneUnavailable },
			{ 0x1190, EQNET_OP_ZoneServerInfo },
			/* Zone packets */
			{ 0x4b61, EQNET_OP_ZoneEntry }
	};
}

#endif//_EQNET_OPCODES_UNDERFOOT_H_
