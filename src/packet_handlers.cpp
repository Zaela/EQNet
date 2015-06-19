
#include "stdafx.h"

void EQNet_EnablePacketTranslation(EQNet* net, int setting)
{
	net->translateZonePackets = setting ? 1 : 0;
}



////////////////////////////////////////////////////////////////
// Packet handlers
////////////////////////////////////////////////////////////////

typedef void(*PacketHandler)(EQNet*, uint16_t, uint16_t, byte*, uint32_t len);

#define HANDLER(name) static void ph##name(EQNet* net, uint16_t eqnetOpcode, uint16_t opcode, byte* data, uint32_t len)

static std::unordered_map<uint16_t, PacketHandler> gPacketHandlers;

void handlePacket(EQNet* net, uint16_t opcode, uint16_t nativeOpcode, byte* data, uint32_t len)
{
#ifdef EQNET_DEBUG
	printf("opcode 0x%0.4X-> 0x%0.4X\n", nativeOpcode, opcode);
#endif

	if (gPacketHandlers.count(opcode))
		gPacketHandlers[opcode](net, opcode, nativeOpcode, data, len);
	else
		queuePacketEvent(net, opcode, nativeOpcode, data, len);
}

HANDLER(ReuseNative)
{
	queuePacketEvent(net, eqnetOpcode, data, len, opcode, data, len);
}

HANDLER(ReuseFourByteToTwo)
{
	queuePacketEvent(net, eqnetOpcode, data + 2, len - 2, opcode, data, len);
}

#define PREAMBLE do { \
    if (!net->translateZonePackets) \
    { \
        queuePacketEvent(net, eqnetOpcode, opcode, data, len); \
		return; \
    } } while(0)

#define CAST(var, to) to* var = (to*)data
#define PACKET(sname) EQNetPacket_##sname
#define PACKET_SIZE(sname) sizeof(PACKET(sname))
#define ALLOC_STRUCT(var, sname) PACKET(sname)* var = new PACKET(sname)
#define ALLOC_STRUCT_ARRAY(var, sname, c) PACKET(sname)* var = new PACKET(sname)[c]
#define QUEUE_STRUCT(var, sname) queuePacketEvent(net, eqnetOpcode, var, PACKET_SIZE(sname), opcode, data, len)
#define QUEUE_STRUCT_ARRAY(var, sname, c) queuePacketEvent(net, eqnetOpcode, var, PACKET_SIZE(sname) * c, opcode, data, len, c)

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
	Titanium::ZoneServerInfo_Struct* zs = (Titanium::ZoneServerInfo_Struct*)data;

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

/////////////////////////////////////////////
// Packets received while in-zone
/////////////////////////////////////////////
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
	CAST(src, Titanium::ExactHPUpdate_Struct);
	ALLOC_STRUCT(hp, HpUpdateExact);
	hp->mobId = src->spawn_id;
	hp->cur = src->cur_hp;
	hp->max = src->max_hp;
	QUEUE_STRUCT(hp, HpUpdateExact);
}

HANDLER(HpUpdatePercent)
{
	PREAMBLE;
	CAST(src, Titanium::HPUpdate_Struct);
	ALLOC_STRUCT(hp, HpUpdatePercent);
	hp->mobId = src->spawn_id;
	hp->percent = src->hp;
	QUEUE_STRUCT(hp, HpUpdatePercent);
}

// handler must have same name as EQNET_OP_
#define SET(handler) gPacketHandlers[EQNET_OP_##handler] = ph##handler
#define REUSE(name) gPacketHandlers[EQNET_OP_##name] = phReuseNative; setNoDeleteOpcode(EQNET_OP_##name)
#define REUSE_4BYTEto2BYTE(name) gPacketHandlers[EQNET_OP_##name] = phReuseFourByteToTwo; setNoDeleteOpcode(EQNET_OP_##name)

void initPacketHandlers()
{
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

	SET(Consider);
	SET(HpUpdateExact);
	SET(HpUpdatePercent);

	REUSE_4BYTEto2BYTE(Assist);
	REUSE_4BYTEto2BYTE(Despawn);
	REUSE_4BYTEto2BYTE(TargetsTarget);

	REUSE(MoneyUpdate);
	REUSE(TimeUpdate);
}

void deinitPacketHandlers()
{
	gPacketHandlers.clear();
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
