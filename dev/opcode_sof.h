
#ifndef _EQNET_OPCODES_SOF_H_
#define _EQNET_OPCODES_SOF_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace SoF
{
	static const OpCodeTranslation toCanonical[] = {
			/* World packets */
			{ 0x6c3c, EQNET_OP_SendLoginInfo },
			{ 0x04fb, EQNET_OP_GuildsList },
			{ 0x129a, EQNET_OP_LogServer },
			{ 0x7fc0, EQNET_OP_ApproveWorld },
			{ 0x6040, EQNET_OP_SendCharInfo },
			{ 0x1340, EQNET_OP_EnterWorld },
			{ 0x1aee, EQNET_OP_PostEnterWorld },
			{ 0x0a1b, EQNET_OP_ExpansionInfo },
			/* Char select packets */
			{ 0x4d38, EQNET_OP_AckPacket },
			{ 0x5711, EQNET_OP_MOTD },
			{ 0x71b8, EQNET_OP_SetChatServer },
			{ 0x32cc, EQNET_OP_SetChatServer2 },
			{ 0x07a2, EQNET_OP_ZoneUnavailable },
			{ 0x18b1, EQNET_OP_ZoneServerInfo }
	};
}

#endif//_EQNET_OPCODES_SOF_H_
