
#ifndef _EQNET_OPCODES_ROF_H_
#define _EQNET_OPCODES_ROF_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace RoF
{
	static const OpCodeTranslation toCanonical[] = {
			/* World packets */
			{ 0x11b6, EQNET_OP_SendLoginInfo },
			{ 0x2d38, EQNET_OP_GuildsList },
			{ 0x19ab, EQNET_OP_LogServer },
			{ 0x7e47, EQNET_OP_ApproveWorld },
			{ 0x06a2, EQNET_OP_SendCharInfo },
			{ 0x57c3, EQNET_OP_EnterWorld },
			{ 0x0c3d, EQNET_OP_PostEnterWorld },
			{ 0x711a, EQNET_OP_ExpansionInfo },
			/* Char select packets */
			{ 0x47a6, EQNET_OP_AckPacket },
			{ 0x1ae3, EQNET_OP_MessageOfTheDay },
			{ 0x2a81, EQNET_OP_SetChatServer },
			{ 0x4099, EQNET_OP_SetChatServer2 },
			{ 0x6281, EQNET_OP_ZoneUnavailable },
			{ 0x49d9, EQNET_OP_ZoneServerInfo },
			/* Zone packets */
			{ 0x1665, EQNET_OP_ZoneEntry }
	};
}

#endif//_EQNET_OPCODES_ROF_H_
