
#ifndef _EQNET_OPCODES_ROF2_H_
#define _EQNET_OPCODES_ROF2_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace RoF2
{
	static const OpCodeTranslation toCanonical[] = {
			/* World packets */
			{ 0x7a09, EQNET_OP_SendLoginInfo },
			{ 0x507a, EQNET_OP_GuildsList },
			{ 0x7ceb, EQNET_OP_LogServer },
			{ 0x7499, EQNET_OP_ApproveWorld },
			{ 0x00d2, EQNET_OP_SendCharInfo },
			{ 0x578f, EQNET_OP_EnterWorld },
			{ 0x6259, EQNET_OP_PostEnterWorld },
			{ 0x590d, EQNET_OP_ExpansionInfo },
			/* Char select packets */
			{ 0x471d, EQNET_OP_AckPacket },
			{ 0x0c22, EQNET_OP_MOTD },
			{ 0x1bc5, EQNET_OP_SetChatServer },
			{ 0x7eec, EQNET_OP_SetChatServer2 },
			{ 0x4cb4, EQNET_OP_ZoneUnavailable },
			{ 0x4c44, EQNET_OP_ZoneServerInfo }
	};
}

#endif//_EQNET_OPCODES_ROF2_H_
