
#include "stdafx.h"

void EQNet_EnablePacketPayloadTranslation(EQNet* net, int setting)
{
	net->translateZonePackets = (setting != 0);
}

////////////////////////////////////////////////////////////////
// Zone packet handlers
////////////////////////////////////////////////////////////////

typedef void(*ZonePacketHandler)(EQNet*, uint16_t, uint16_t, byte*, uint32_t len);

#define HANDLER(name) static void zph##name(EQNet* net, uint16_t eqnetOpcode, uint16_t opcode, byte* data, uint32_t len)

static std::unordered_map<uint16_t, ZonePacketHandler> gZonePacketHandlers;

void handleZonePacket(EQNet* net, uint16_t opcode, uint16_t nativeOpcode, byte* data, uint32_t len)
{
	printf("opcode 0x%0.4X-> 0x%0.4X\n", nativeOpcode, opcode);
	if (gZonePacketHandlers.count(opcode))
		gZonePacketHandlers[opcode](net, opcode, nativeOpcode, data, len);
	else
		queueZonePacketEvent(net, opcode, nativeOpcode, data, len);
}

HANDLER(ReuseNative)
{
	queueZonePacketEvent(net, eqnetOpcode, data, len, opcode, data, len);
}

#define PREAMBLE do { \
    if (!net->translateZonePackets) \
    { \
        queueZonePacketEvent(net, eqnetOpcode, opcode, data, len); \
		return; \
    } } while(0)

#define CAST(var, to) to* var = (to*)data
#define PACKET(sname) EQNetPacket_##sname
#define PACKET_SIZE(sname) sizeof(PACKET(sname))
#define ALLOC_STRUCT(var, sname) PACKET(sname)* var = new PACKET(sname)
#define ALLOC_STRUCT_ARRAY(var, sname, c) PACKET(sname)* var = new PACKET(sname)[c]
#define QUEUE_STRUCT(var, sname) queueZonePacketEvent(net, eqnetOpcode, var, PACKET_SIZE(sname), opcode, data, len)
#define QUEUE_STRUCT_ARRAY(var, sname, c) queueZonePacketEvent(net, eqnetOpcode, var, PACKET_SIZE(sname) * c, opcode, data, len, c)

/////////////////////////////////////////////
// Packets received while zoning in
/////////////////////////////////////////////
HANDLER(PlayerProfile)
{
	PREAMBLE;

	// translate

	queueZonePacketEvent(net, eqnetOpcode, nullptr, 0, opcode, data, len);
}

/////////////////////////////////////////////
// Packets received while in-zone
/////////////////////////////////////////////
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
#define SET(handler) gZonePacketHandlers[EQNET_OP_##handler] = zph##handler
#define REUSE(name) gZonePacketHandlers[EQNET_OP_##name] = zphReuseNative

void initZonePacketHandlers()
{
	SET(PlayerProfile);
	REUSE(Despawn);
	SET(HpUpdateExact);
	SET(HpUpdatePercent);
	REUSE(TimeUpdate);
}

void deinitZonePacketHandlers()
{
	gZonePacketHandlers.clear();
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
