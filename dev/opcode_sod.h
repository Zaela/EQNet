
#ifndef _EQNET_OPCODES_SOD_H_
#define _EQNET_OPCODES_SOD_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace SoD
{
	static const OpCodeTranslation toCanonical[] = {
			/* World packets */
			{ 0x0ff4, EQNET_OP_SendLoginInfo },
			{ 0x5b0b, EQNET_OP_GuildsList },
			{ 0x4762, EQNET_OP_LogServer },
			{ 0x701f, EQNET_OP_ApproveWorld },
			{ 0x0f14, EQNET_OP_SendCharInfo },
			{ 0x1c20, EQNET_OP_EnterWorld },
			{ 0x7c94, EQNET_OP_PostEnterWorld },
			{ 0x7519, EQNET_OP_ExpansionInfo },
			/* Char select packets */
			{ 0x3594, EQNET_OP_AckPacket },
			{ 0x192e, EQNET_OP_MessageOfTheDay },
			{ 0x7f2b, EQNET_OP_SetChatServer },
			{ 0x11f3, EQNET_OP_SetChatServer2 },
			{ 0x7930, EQNET_OP_ZoneUnavailable },
			{ 0x5da4, EQNET_OP_ZoneServerInfo },
			/* Zone packets */
			{ 0x5a6b, EQNET_OP_ZoneEntry }
	};
}

#endif//_EQNET_OPCODES_SOD_H_
