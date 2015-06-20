
#include "stdafx.h"

void EQNet_EnablePacketTranslation(EQNet* net, int setting)
{
	net->translatePackets = setting ? 1 : 0;
}

////////////////////////////////////////////////////////////////
// Packet handlers
////////////////////////////////////////////////////////////////

using namespace Titanium; // default struct namespace

typedef void(*PacketHandler)(EQNet*, uint16_t, uint16_t, byte*, uint32_t len);

#define HANDLER(name) static void ph##name(EQNet* net, uint16_t eqnetOpcode, uint16_t opcode, byte* data, uint32_t len)

static PacketHandler gPacketHandlers[EQNET_OP_INTERNAL_MAX_COUNT];

void handlePacket(EQNet* net, uint16_t opcode, uint16_t nativeOpcode, byte* data, uint32_t len)
{
#ifdef EQNET_DEBUG
	printf("opcode 0x%0.4X-> 0x%0.4X\n", nativeOpcode, opcode);
#endif

	PacketHandler func = gPacketHandlers[opcode];
	if (func)
		func(net, opcode, nativeOpcode, data, len);
	else
		queuePacketEvent(net, opcode, nativeOpcode, data, len);
}

HANDLER(ReuseNative)
{
	queuePacketEvent(net, eqnetOpcode, data, len, opcode, data, len);
}

// mainly for packets that use 32bits to pass entity ids, which are 16bits otherwise
HANDLER(ReuseFourByteToTwo)
{
	queuePacketEvent(net, eqnetOpcode, data + 2, len - 2, opcode, data, len);
}

#define PREAMBLE do { \
    if (!net->translatePackets) \
    { \
        queuePacketEvent(net, eqnetOpcode, opcode, data, len); \
		return; \
    } } while(0)

#define CAST(var, to) to* var = (to*)data
#define PACKET(sname) EQNetPacket_##sname
#define PACKET_SIZE(sname) sizeof(PACKET(sname))
#define ALLOC_STRUCT(var, sname) PACKET(sname)* var = (PACKET(sname)*)(new byte[PACKET_SIZE(sname)])
#define ALLOC_VARSIZE_STRUCT(var, sname, size) PACKET(sname)* var = (PACKET(sname)*)(new byte[size])
#define ALLOC_STRUCT_ARRAY(var, sname, c) PACKET(sname)* var = (PACKET(sname)*)(new byte[PACKET_SIZE(sname) * c])
#define QUEUE_STRUCT(var, sname) queuePacketEvent(net, eqnetOpcode, var, PACKET_SIZE(sname), opcode, data, len)
#define QUEUE_STRUCT_OP(var, sname, op) queuePacketEvent(net, op, var, PACKET_SIZE(sname), opcode, data, len)
#define QUEUE_VARSIZE(var, size) queuePacketEvent(net, eqnetOpcode, var, size, opcode, data, len)
#define QUEUE_VARSIZE_OP(var, size, op) queuePacketEvent(net, op, var, size, opcode, data, len)
#define QUEUE_STRUCT_ARRAY(var, sname, c) queuePacketEvent(net, eqnetOpcode, var, PACKET_SIZE(sname) * c, opcode, data, len, c)
#define QUEUE_STRUCT_OP_ARRAY(var, sname, op, c) queuePacketEvent(net, op, var, PACKET_SIZE(sname) * c, opcode, data, len, c)
#define QUEUE_VARSIZE_WITH_COUNT(var, size, c) queuePacketEvent(net, eqnetOpcode, var, size, opcode, data, len, c)
#define QUEUE_VARSIZE_OP_WITH_COUNT(var, size, op, c) queuePacketEvent(net, op, var, size, opcode, data, len, c)
#define QUEUE_STRUCT_WITH_COUNT(var, sname, c) queuePacketEvent(net, eqnetOpcode, var, PACKET_SIZE(sname), opcode, data, len, c)
#define QUEUE_STRUCT_OP_WITH_COUNT(var, sname, op, c) queuePacketEvent(net, op, var, PACKET_SIZE(sname), opcode, data, len, c)
#define QUEUE_DEFAULT queuePacketEvent(net, eqnetOpcode, opcode, data, len)

#define HANDLE_AS(name) ph##name(net, EQNET_OP_##name, opcode, data, len)
#define FORWARD_DECLARE(name) void ph##name(EQNet*, uint16_t, uint16_t, byte*, uint32_t)

/////////////////////////////////////////////
// Packets received on the way to char select
/////////////////////////////////////////////
HANDLER(GuildsList)
{
	readGuilds(net, data, len);
}

HANDLER(SendCharInfo)
{
	readCharSelectCharacters(net, data, len);

	net->connection->setTimeoutEnabled(false);
	net->mode = MODE_CHAR_SELECT;
	queueEvent(net, EQNET_EVENT_AtCharacterSelect);
}

HANDLER(LogServer)
{
	const char* shortname = (char*)(data + 32);
	size_t slen = strlen(shortname) + 1;

	char* str = new char[slen];
	memcpy(str, shortname, slen);

	if (net->serverShortName)
		delete[] net->serverShortName;
	net->serverShortName = str;
}

/////////////////////////////////////////////
// Packets received before zoning in
/////////////////////////////////////////////
HANDLER(ZoneUnavailable)
{
	queueEvent(net, EQNET_EVENT_ZoneUnavailable);
}

HANDLER(ZoneServerInfo)
{
	// struct seems to be the same for all client versions
	CAST(zs, ZoneServerInfo_Struct);

	Address addr;
	addr.ip = zs->ip;
	addr.port = zs->port;

	recordAddress(net->addressZone, addr);

	net->mode = MODE_WORLD_TO_ZONE;
	net->connection->sessionHandoff(addr);
}

/////////////////////////////////////////////
// Packets received while zoning in
/////////////////////////////////////////////
HANDLER(PlayerProfile)
{
	PREAMBLE;

	// translate

	queuePacketEvent(net, eqnetOpcode, nullptr, 0, opcode, data, len);
}

HANDLER(WeatherUpdate)
{
	// if we are entering a zone, we need to send something right after receiving this
	if (net->mode == MODE_WORLD_TO_ZONE)
	{
		Packet::queueZeroLength(net, EQNET_OP_ReqNewZone);
	}

	PREAMBLE;

	// translate
}

HANDLER(ZoneData)
{
	// send client spawn request
	Packet::queueZeroLength(net, EQNET_OP_ReqClientSpawn);

	PREAMBLE;
}

HANDLER(SetExperience)
{
	if (len == 0)
	{
		// send client ready packet
		Packet::queueZeroLength(net, EQNET_OP_ClientReady);

		// might be a better, later packet to trigger this on
		queueEvent(net, EQNET_EVENT_AtZone);
		net->mode = MODE_ZONE;
		net->connection->setTimeoutEnabled(false); // ? need to decide how/if this should work while in-zone
		return;
	}

	PREAMBLE;
}

FORWARD_DECLARE(Spawn);

HANDLER(PlayerSpawn)
{
	// some clients use this opcode for both player spawn and bulk zone spawns
	// player spawn should be the first one received
	if (net->receivedPlayerSpawn)
	{
		HANDLE_AS(Spawn);
		return;
	}
	
	net->receivedPlayerSpawn = true;
	PREAMBLE;

	QUEUE_DEFAULT;
}

/////////////////////////////////////////////
// Packets received while in-zone
/////////////////////////////////////////////
HANDLER(ChatMessage) // originally ChannelMessage
{
	PREAMBLE;
	CAST(src, ChannelMessage_Struct);
	const char* msg = (char*)(data + sizeof(ChannelMessage_Struct));
	size_t msglen = strlen(msg);

	uint32_t outlen = PACKET_SIZE(ChatMessage) + msglen; // chatmessage has an extra byte for the msg stub
	ALLOC_VARSIZE_STRUCT(cm, ChatMessage, outlen);
	Util::strcpy(cm->senderName, src->sender, 64);
	cm->targetId = 0;
	cm->channel = src->chan_num;
	cm->color = 0;
	cm->language = src->language;
	cm->len = msglen;
	memcpy(cm->msg, msg, msglen + 1);
	QUEUE_VARSIZE(cm, outlen);
}

HANDLER(ChatMessageEQStr) // originally FormattedMessage
{
	PREAMBLE;
	CAST(src, FormattedMessage_Struct);
	const char* strings = src->message;
	uint32_t buflen = len - sizeof(FormattedMessage_Struct) - 1;

	uint32_t outlen = PACKET_SIZE(ChatMessageEQStr) + buflen;
	ALLOC_VARSIZE_STRUCT(cm, ChatMessageEQStr, outlen);
	cm->channel = src->type;
	cm->color = 0;
	cm->strId = src->string_id;
	char* buffer = ((char*)cm) + PACKET_SIZE(ChatMessageEQStr);
	memcpy(buffer, strings, buflen);

	int i = 0;
	uint32_t pos = 0; // just for bounds checking
	while (*buffer && i < 9 && pos < buflen)
	{
		uint32_t slen = strlen(buffer);
		cm->strings[i].len = slen;
		cm->strings[i].str = buffer;
		buffer += slen + 1;
		pos += slen + 1;
		++i;
	}

	QUEUE_VARSIZE_WITH_COUNT(cm, outlen, i);
}

HANDLER(Consider)
{
	PREAMBLE;
	ALLOC_STRUCT(con, Consider);

	switch (net->clientVersion)
	{
	case EQNET_CLIENT_Titanium:
	{
		CAST(src, Titanium::Consider_Struct);
		con->mobId = src->targetid;
		//con-> handle faction and color con translation
		break;
	}
	} // switch

	QUEUE_STRUCT(con, Consider);
}

HANDLER(HpUpdateExact)
{
	PREAMBLE;
	CAST(src, ExactHPUpdate_Struct);
	ALLOC_STRUCT(hp, HpUpdateExact);
	hp->mobId = src->spawn_id;
	hp->cur = src->cur_hp;
	hp->max = src->max_hp;
	QUEUE_STRUCT(hp, HpUpdateExact);
}

HANDLER(HpUpdatePercent)
{
	PREAMBLE;
	CAST(src, HPUpdate_Struct);
	ALLOC_STRUCT(hp, HpUpdatePercent);
	hp->mobId = src->spawn_id;
	hp->percent = src->hp;
	QUEUE_STRUCT(hp, HpUpdatePercent);
}

HANDLER(SimpleMessage)
{
	PREAMBLE;
	CAST(src, SimpleMessage_Struct);
	ALLOC_STRUCT(cm, ChatMessageEQStr);
	cm->color = src->color; // split color and channel values
	cm->channel = 0;
	cm->strId = src->string_id;
	QUEUE_STRUCT_OP_WITH_COUNT(cm, ChatMessageEQStr, EQNET_OP_ChatMessageEQStr, 0);
}

HANDLER(Spawn)
{
	PREAMBLE;

	QUEUE_DEFAULT;
}

HANDLER(SpecialMesg)
{
	PREAMBLE;
	CAST(src, SpecialMesg_Struct);
	const char* sayer = (char*)(data + sizeof(SpecialMesg_Struct));
	const char* msg = (char*)(sayer + strlen(sayer) + 13);
	uint32_t msglen = strlen(msg);

	uint32_t outlen = PACKET_SIZE(ChatMessage) + msglen; // chatmessage has an extra byte for the msg stub
	ALLOC_VARSIZE_STRUCT(cm, ChatMessage, outlen);
	Util::strcpy(cm->senderName, sayer, 64);
	cm->targetId = src->target_spawn_id;
	cm->channel = src->msg_type;
	cm->color = 0;
	cm->language = 0;
	cm->len = msglen;
	memcpy(cm->msg, msg, msglen + 1);
	QUEUE_VARSIZE_OP(cm, outlen, EQNET_OP_ChatMessage);
}

// handler must have same name as EQNET_OP_
#define SET(handler) gPacketHandlers[EQNET_OP_##handler] = ph##handler
#define REUSE(name) gPacketHandlers[EQNET_OP_##name] = phReuseNative; setNoDeleteOpcode(EQNET_OP_##name)
#define REUSE_4BYTEto2BYTE(name) gPacketHandlers[EQNET_OP_##name] = phReuseFourByteToTwo; setNoDeleteOpcode(EQNET_OP_##name)

void initPacketHandlers()
{
	memset(gPacketHandlers, 0, sizeof(gPacketHandlers));

	SET(GuildsList);
	SET(SendCharInfo);
	SET(LogServer);

	SET(ZoneUnavailable);
	REUSE(MessageOfTheDay);
	SET(ZoneServerInfo);

	SET(PlayerProfile);
	SET(WeatherUpdate);
	SET(ZoneData);
	SET(SetExperience);
	SET(PlayerSpawn);

	SET(ChatMessage);
	SET(ChatMessageEQStr);
	SET(Consider);
	SET(HpUpdateExact);
	SET(HpUpdatePercent);
	SET(SimpleMessage);
	SET(Spawn);
	SET(SpecialMesg);

	REUSE_4BYTEto2BYTE(Assist);
	REUSE_4BYTEto2BYTE(Despawn);
	REUSE_4BYTEto2BYTE(TargetsTarget);

	REUSE(MoneyUpdate);
	REUSE(TimeUpdate);
}

#undef ALLOC_STRUCT
#undef ALLOC_STRUCT_ARRAY
#undef PACKET
#undef PACKET_SIZE
#undef QUEUE_STRUCT
#undef QUEUE_STRUCT_ARRAY
#undef PREAMBLE
#undef REUSE
#undef SET
#undef HANDLER
