
#ifndef _EQNET_OPCODES_UNDERFOOT_H_
#define _EQNET_OPCODES_UNDERFOOT_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace Underfoot
{
	static const OpCodeTranslation toCanonical[] = {
			/* World packets */
			{ 0x13DA, EQNET_OP_SendLoginInfo },
			{ 0x5B0B, EQNET_OP_GuildsList },
			{ 0x6F79, EQNET_OP_LogServer },
			{ 0x86C7, EQNET_OP_ApproveWorld },
			{ 0x4200, EQNET_OP_SendCharInfo },
			{ 0x51B9, EQNET_OP_EnterWorld },
			{ 0x5D32, EQNET_OP_PostEnterWorld },
			{ 0x7E4D, EQNET_OP_ExpansionInfo },
			/* Char select packets */
			{ 0x3594, EQNET_OP_AckPacket },
			{ 0x7629, EQNET_OP_MOTD },
			{ 0x7D90, EQNET_OP_SetChatServer },
			{ 0x158F, EQNET_OP_SetChatServer2 },
			{ 0x3288, EQNET_OP_ZoneUnavailable },
			{ 0x1190, EQNET_OP_ZoneServerInfo }
	};
}

#endif//_EQNET_OPCODES_UNDERFOOT_H_
