
#include "stdafx.h"

void EQNet_SendChatMessage(EQNet* net, const char* message, EQNet_ChatChannel channel, uint32_t language,
	const char* tellRecipient)
{
	uint32_t msglen = strlen(message) + 1;
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
}
