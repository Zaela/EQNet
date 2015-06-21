
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
#define ZERO_STRUCT(var, sname) memset(var, 0, PACKET_SIZE(sname))

#define HANDLE_AS(name) ph##name(net, EQNET_OP_##name, opcode, data, len)
#define HANDLE_AS_BUT_KEEP_OPCODE(name) ph##name(net, eqnetOpcode, opcode, data, len)
#define FORWARD_DECLARE(name) void ph##name(EQNet*, uint16_t, uint16_t, byte*, uint32_t)

#define READ_SETUP uint32_t pos = 0;
#define READ_ADVANCE(t) pos += sizeof(t)
#define READ_ADVANCE_COUNT(t, n) pos += sizeof(t) * (n)
#define READ_ADVANCE_BYTES(n) pos += n
#define VIEW(t) *(t*)(data + pos)
#define READ(t) *(t*)(data + pos); pos += sizeof(t)
#define READ_NEW_STRING readCopyString(pos, data)
#define READ_STRING_BOUND(var, bound) Util::strcpy(var, (char*)(data + pos), bound); pos += bound
#define READ_STRING_VARLEN(var, bound) readVarLenString(var, pos, data, bound)

char* readCopyString(uint32_t& pos, byte* data)
{
	char* src = (char*)(data + pos);
	uint32_t len = strlen(src) + 1;
	pos += len;
	return Util::copyString(src, len);
}

void readVarLenString(char* dst, uint32_t& pos, byte* data, uint32_t bound)
{
	char* src = (char*)(data + pos);
	uint32_t len = strlen(src) + 1;
	pos += len;
	Util::strcpy(dst, src, bound);
}

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

	ALLOC_STRUCT(pp, PlayerProfile);
	ZERO_STRUCT(pp, PlayerProfile);
	READ_SETUP;

	switch (net->clientVersion)
	{
	case EQNET_CLIENT_ReignOfFear2:
		READ_ADVANCE_COUNT(uint32_t, 4);
		pp->gender = READ(uint8_t);
		pp->race = READ(uint32_t);
		pp->charClass = READ(uint8_t);
		pp->level = READ(uint8_t);
		READ_ADVANCE_BYTES(5);

		for (int i = 0; i < EQNET_BIND_POINT_COUNT; ++i)
		{
			EQNetPacket_BindPoint& bp = pp->bindPoints[i];
			bp.zoneId = READ(uint32_t);
			bp.x = READ(float);
			bp.y = READ(float);
			bp.z = READ(float);
			bp.heading = READ(float);
		}

		pp->deity = READ(uint32_t);
		pp->intoxication = READ(uint32_t);

		READ_ADVANCE_COUNT(uint32_t, 12);

		for (int i = 0; i < EQNET_EQUIP_MATERIAL_COUNT; ++i)
		{
			pp->equipMaterials[i] = READ(uint32_t);
			READ_ADVANCE_COUNT(uint32_t, 4);
		}

		READ_ADVANCE_COUNT(uint32_t, 5 * 22 + 2);

		for (int i = 0; i < EQNET_EQUIP_TINT_COUNT; ++i)
		{
			pp->equipMaterialTints[i].color = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 3);

		for (int i = 0; i < EQNET_EQUIP_TINT_COUNT; ++i)
		{
			pp->equipMaterialTints[i].color2 = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 2);

		pp->hairColor = READ(uint8_t);
		pp->beardColor = READ(uint8_t);
		READ_ADVANCE(uint32_t);
		pp->eyeColor1 = READ(uint8_t);
		pp->eyeColor2 = READ(uint8_t);
		pp->hairstyle = READ(uint8_t);
		pp->beard = READ(uint8_t);
		pp->face = READ(uint8_t);

		pp->drakkinHeritage = READ(uint32_t);
		pp->drakkinTattoo = READ(uint32_t);
		pp->drakkinDetails = READ(uint32_t);

		READ_ADVANCE_BYTES(5);
		READ_ADVANCE_COUNT(uint32_t, 6);

		pp->trainingPoints = READ(uint32_t);
		pp->currentMana = READ(uint32_t);
		pp->currentHp = READ(uint32_t);
		pp->STR = READ(uint32_t);
		pp->STA = READ(uint32_t);
		pp->CHA = READ(uint32_t);
		pp->DEX = READ(uint32_t);
		pp->INT = READ(uint32_t);
		pp->AGI = READ(uint32_t);
		pp->WIS = READ(uint32_t);

		READ_ADVANCE_COUNT(uint32_t, 8);

		for (int i = 0; i < EQNET_AA_COUNT; ++i)
		{
			EQNetPacket_AA& aa = pp->AAs[i];
			aa.id = READ(uint32_t);
			aa.value = READ(uint32_t);
			aa.charges = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 60 * 3 + 1);

		for (int i = 0; i < EQNET_SKILL_COUNT; ++i)
		{
			pp->skills[i] = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 27);

		for (int i = 0; i < EQNET_DISCIPLINE_COUNT; ++i)
		{
			pp->disciplines[i] = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 222);

		for (int i = 0; i < 20; ++i)
		{
			pp->recastTimes[i] = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 102);

		for (int i = 0; i < EQNET_SPELLBOOK_COUNT; ++i)
		{
			pp->spellbook[i] = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 720 - EQNET_SPELLBOOK_COUNT + 1);

		for (int i = 0; i < EQNET_MEMSPELL_COUNT; ++i)
		{
			pp->memmedSpells[i] = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 16 - EQNET_MEMSPELL_COUNT + 15);
		READ_ADVANCE_BYTES(1);

		for (int i = 0; i < EQNET_BUFF_COUNT; ++i)
		{
			EQNetPacket_Buff& buff = pp->buffs[i];
			READ_ADVANCE_BYTES(1);
			buff.instrumentModifier = READ(float);
			buff.casterId = READ(uint32_t);
			READ_ADVANCE_BYTES(1);
			buff.counters = READ(uint32_t);
			buff.duration = READ(uint32_t);
			buff.casterLevel = READ(uint8_t);
			buff.spellId = READ(uint32_t);
			buff.slot = READ(uint32_t);
			READ_ADVANCE_BYTES(45 + 8);
		}

		READ_ADVANCE_COUNT(uint32_t, (42 - EQNET_BUFF_COUNT) * 20);

		pp->platinum = READ(uint32_t);
		pp->gold = READ(uint32_t);
		pp->silver = READ(uint32_t);
		pp->copper = READ(uint32_t);
		pp->cursorPlatinum = READ(uint32_t);
		pp->cursorGold = READ(uint32_t);
		pp->cursorSilver = READ(uint32_t);
		pp->cursorCopper = READ(uint32_t);

		READ_ADVANCE_COUNT(uint32_t, 3);

		pp->thirst = READ(uint32_t);
		pp->hunger = READ(uint32_t);
		pp->spentAApoints = READ(uint32_t);

		READ_ADVANCE_COUNT(uint32_t, 6);

		pp->availableAApoints = READ(uint32_t);

		READ_ADVANCE_BYTES(6);

		// bandolier
		for (int i = 0; i < EQNET_BANDOLIERS_COUNT; ++i)
		{
			EQNetPacket_Bandolier& b = pp->bandolier[i];
			b.name = READ_NEW_STRING;

			for (int j = 0; j < EQNET_BANDOLIER_ITEMS_COUNT; ++j)
			{
				EQNetPacket_BandolierItem& bi = b.items[j];
				bi.name = READ_NEW_STRING;
				bi.id = READ(uint32_t);
				bi.icon = READ(int32_t);
			}
		}

		// potion belt
		for (int i = 0; i < EQNET_POTION_BELT_ITEM_COUNT; ++i)
		{
			EQNetPacket_BandolierItem pi = pp->potionBelt[i];
			pi.name = READ_NEW_STRING;
			pi.id = READ(uint32_t);
			pi.icon = READ(int32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 21);
		pp->currentEndurance = READ(uint32_t);
		READ_ADVANCE_COUNT(uint32_t, 3);

		READ_STRING_BOUND(pp->name, 64);
		READ_ADVANCE(uint32_t);
		READ_STRING_BOUND(pp->surname, 32);
		READ_ADVANCE(uint32_t);
		pp->creationTime = READ(uint32_t);
		pp->lastLoginTime = READ(uint32_t);
		pp->minutesPlayed = READ(uint32_t);
		pp->entitledTime = READ(uint32_t);

		READ_ADVANCE_COUNT(uint32_t, 2);

		for (int i = 0; i < EQNET_LANGUAGE_COUNT; ++i)
		{
			pp->languages[i] = READ(uint8_t);
		}

		READ_ADVANCE_BYTES(32 - EQNET_LANGUAGE_COUNT);

		pp->zoneId = READ(uint16_t);
		pp->instanceId = READ(uint16_t);
		pp->y = READ(float);
		pp->x = READ(float);
		pp->z = READ(float);
		pp->heading = READ(float);

		READ_ADVANCE_BYTES(1);
		pp->isPvP = READ(uint8_t);
		READ_ADVANCE_BYTES(1);
		pp->isGM = READ(uint8_t);

		pp->guildId = READ(uint32_t);
		pp->guildRank = READ(uint8_t);
		READ_ADVANCE_BYTES(9);

		pp->experience = READ(uint64_t);
		READ_ADVANCE_BYTES(1);
		pp->bankPlatinum = READ(uint32_t);
		pp->bankGold = READ(uint32_t);
		pp->bankSilver = READ(uint32_t);
		pp->bankCopper = READ(uint32_t);
		pp->sharedPlatinum = READ(uint32_t);
		READ_ADVANCE_COUNT(uint32_t, 6);

		pp->totalTributePoints = READ(uint32_t);
		READ_ADVANCE(uint32_t);
		pp->tributePoints = READ(uint32_t);
		READ_ADVANCE_BYTES(10);

		for (int i = 0; i < EQNET_TRIBUTE_COUNT; ++i)
		{
			pp->tributes[i].id = READ(uint32_t);
			pp->tributes[i].tier = READ(uint32_t);
		}

		// skip stuff
		READ_ADVANCE_COUNT(uint32_t, 27);
		READ_ADVANCE_BYTES(125 + 8);

		pp->radiantCrystals = READ(uint32_t);
		pp->totalRadiantCrystals = READ(uint32_t);
		pp->ebonCrystals = READ(uint32_t);
		pp->totalEbonCrystals = READ(uint32_t);

		// skip tons of stuff
		READ_ADVANCE_BYTES((4 * 13) + 64 + 10 + 64 + 64 + 320 + 343);

		pp->leadershipActive = READ(uint8_t);
		READ_ADVANCE_COUNT(uint32_t, 2);
		pp->ldonPointsGuk = READ(uint32_t);
		pp->ldonPointsMir = READ(uint32_t);
		pp->ldonPointsMmc = READ(uint32_t);
		pp->ldonPointsRuj = READ(uint32_t);
		pp->ldonPointsTak = READ(uint32_t);
		pp->ldonPointsAvailable = READ(uint32_t);
		
		pp->groupLeadershipExp = READ(double);
		pp->raidLeadershipExp = READ(double);

		READ_ADVANCE(uint32_t);
		
		for (int i = 0; i < EQNET_TOTAL_LEADERSHIP_COUNT; ++i)
		{
			pp->leadershipAAs[i] = READ(uint32_t);
		}

		READ_ADVANCE_COUNT(uint32_t, 64 - EQNET_TOTAL_LEADERSHIP_COUNT);

		// mostly pvp stuff remaining... finish later
		break;
	}

	QUEUE_STRUCT(pp, PlayerProfile);
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

	ALLOC_STRUCT(zd, ZoneData);
	// translate

	QUEUE_STRUCT(zd, ZoneData);
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

	HANDLE_AS_BUT_KEEP_OPCODE(Spawn);
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

	ALLOC_STRUCT(sp, Spawn);
	ZERO_STRUCT(sp, Spawn);

	READ_SETUP;

	switch (net->clientVersion)
	{
	case EQNET_CLIENT_ReignOfFear2:
	{
		READ_STRING_VARLEN(sp->name, 64);
		sp->mobId = READ(uint32_t);
		sp->level = READ(uint8_t);
		READ_ADVANCE(float);
		uint8_t npc = READ(uint8_t);

		if (npc == 1 || npc == 3)
			sp->isNpc = true;
		if (npc == 2 || npc == 3)
			sp->isCorpse = true;

		RoF::Spawn_Struct_Bitfields bit = READ(RoF::Spawn_Struct_Bitfields);
		sp->gender = bit.gender;
		sp->isPet = bit.ispet;
		sp->isAfk = bit.afk;
		if (bit.anon == 1)
			sp->isAnonymous = true;
		else if (bit.anon == 2)
			sp->isRoleplay = true;
		sp->isGM = bit.gm;
		sp->isSneaking = bit.sneak;
		sp->isLfg = bit.lfg;
		sp->isInvis = bit.invis;
		sp->isLinkdead = bit.linkdead;
		sp->showHelm = bit.showhelm;
		sp->isTrader = bit.trader;
		sp->isTargetable = bit.targetable;
		sp->isTargetableWithHotkey = bit.targetable_with_hotkey;
		sp->showName = bit.showname;

		uint8_t titles = READ(uint8_t);

		READ_ADVANCE_BYTES(9);

		sp->bodyType = READ(uint32_t);
		sp->hpPercent = READ(uint8_t);
		sp->hairColor = READ(uint8_t);
		sp->beardColor = READ(uint8_t);
		sp->eyeColor1 = READ(uint8_t);
		sp->eyeColor2 = READ(uint8_t);
		sp->hairstyle = READ(uint8_t);
		sp->beard = READ(uint8_t);
		
		sp->drakkinHeritage = READ(uint32_t);
		sp->drakkinTattoo = READ(uint32_t);
		sp->drakkinDetails = READ(uint32_t);

		READ_ADVANCE_BYTES(3);
		sp->helm = READ(uint8_t);
		sp->size = READ(float);
		sp->face = READ(uint8_t);
		sp->walkspeed = READ(float);
		sp->runspeed = READ(float);
		sp->race = READ(uint32_t);

		READ_ADVANCE_BYTES(1);
		sp->deity = READ(uint32_t);

		if (npc)
		{
			READ_ADVANCE_COUNT(uint32_t, 2);
		}
		else
		{
			sp->guildId = READ(uint32_t);
			sp->guildRank = READ(uint32_t);
		}

		sp->charClass = READ(uint8_t);
		READ_ADVANCE_BYTES(1);
		sp->standState = READ(uint8_t);
		sp->light = READ(uint8_t);
		sp->flyMode = READ(uint8_t);

		READ_STRING_VARLEN(sp->surname, 32);

		READ_ADVANCE_BYTES(3);
		sp->ownerId = READ(uint32_t);

		READ_ADVANCE_BYTES(1 + 4 * 6);

		if (npc == 0 || (sp->race <= 12) || (sp->race == 128) || (sp->race == 130) || (sp->race == 330) || (sp->race == 522))
		{
			for (int i = 0; i < EQNET_EQUIP_TINT_COUNT; ++i)
			{
				sp->equipMaterialTints[i] = READ(uint32_t);
			}

			READ_ADVANCE_COUNT(uint32_t, 2);

			for (int i = 0; i < EQNET_EQUIP_MATERIAL_COUNT; ++i)
			{
				sp->equipMaterials[i].material = READ(uint32_t);
				READ_ADVANCE(uint32_t);
				sp->equipMaterials[i].eliteMaterial = READ(uint32_t);
				sp->equipMaterials[i].heroForgeModel = READ(uint32_t);
				sp->equipMaterials[i].material2 = READ(uint32_t);
			}
		}
		else
		{
			READ_ADVANCE_COUNT(uint32_t, 5);
			sp->equipMaterials[EQNET_MATERIAL_Primary].material = READ(uint32_t);
			READ_ADVANCE_COUNT(uint32_t, 4);
			sp->equipMaterials[EQNET_MATERIAL_Secondary].material = READ(uint32_t);
			READ_ADVANCE_COUNT(uint32_t, 4);
		}

		RoF2::Spawn_Struct_Position p = READ(RoF2::Spawn_Struct_Position);

		// need to do some translation here
		sp->x = (float)p.x;
		sp->y = (float)p.y;
		sp->z = (float)p.z;
		sp->heading = (float)p.heading;
		sp->deltaX = (float)p.deltaX;
		sp->deltaY = (float)p.deltaY;
		sp->deltaZ = (float)p.deltaZ;
		sp->deltaHeading = (float)p.deltaHeading;
		sp->animation = p.animation;

		if (titles & 16)
			READ_STRING_VARLEN(sp->title, 32);
		if (titles & 32)
			READ_STRING_VARLEN(sp->suffix, 32);

		READ_ADVANCE_BYTES(8);
		sp->isMercenary = VIEW(uint8_t) ? true : false;

		break;
	}
	} // switch

	QUEUE_STRUCT(sp, Spawn);
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
