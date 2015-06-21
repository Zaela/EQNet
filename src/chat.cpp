
#include "stdafx.h"

void EQNet_SendChatMessage(EQNet* net, const char* message, EQNet_ChatChannel channel, uint32_t language,
	const char* tellRecipient)
{
	uint32_t msglen = strlen(message) + 1;

	switch (net->clientVersion)
	{
	case EQNET_CLIENT_Titanium:
	case EQNET_CLIENT_SecretsOfFaydwer: // will need to be different if there are embedded item links
	case EQNET_CLIENT_SeedsOfDestruction:
	{
		Packet* p = new Packet(net, sizeof(Titanium::ChannelMessage_Struct) + msglen, EQNET_OP_ChatMessage);
		Titanium::ChannelMessage_Struct* cm = (Titanium::ChannelMessage_Struct*)p->getDataBuffer();

		// server doesn't care about sender name (why even put it there?)
		if (tellRecipient)
			Util::strcpy(cm->targetname, tellRecipient, 64);
		cm->chan_num = channel;
		cm->language = language;

		char* msg = ((char*)cm) + sizeof(Titanium::ChannelMessage_Struct);
		memcpy(msg, message, msglen);
		p->queue(net);
		break;
	}
	case EQNET_CLIENT_Underfoot:
	case EQNET_CLIENT_ReignOfFear:
	case EQNET_CLIENT_ReignOfFear2:
	{
		uint32_t len = 36 + msglen + 2; // 2 null terminators for sender name and tell recipient
		uint32_t tellLen = 0;
		if (tellRecipient)
		{
			tellLen = strlen(tellRecipient);
			len += tellLen;
		}

		Packet* p = new Packet(net, len, EQNET_OP_ChatMessage);
		byte* data = p->getDataBuffer();
		if (tellRecipient)
		{
			memcpy(data + 1, tellRecipient, tellLen);
		}
		uint32_t pos = 2 + tellLen + 4;
		*(uint32_t*)(data + pos) = language;
		pos += 4;
		*(uint32_t*)(data + pos) = channel;
		pos += 4 + 9;

		memcpy(data + pos, message, msglen);
		p->queue(net);
		break;
	}
	} // switch
}
