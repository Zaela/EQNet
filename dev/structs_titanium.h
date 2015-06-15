
#ifndef _EQNET_STRUCTS_TITANIUM_H
#define _EQNET_STRUCTS_TITANIUM_H

#include <cstdint>

namespace Titanium
{

static const uint32_t BUFF_COUNT = 25;
static const uint32_t PACKET_SKILL_ARRAY_SIZE = 100;

/*
** Compiler override to ensure
** byte aligned structures
*/
#pragma pack(1)

struct LoginInfo_Struct {
	/*000*/	char	login_info[64];
	/*064*/	uint8_t	unknown064[124];
	/*188*/	uint8_t	zoning;			// 01 if zoning, 00 if not
	/*189*/	uint8_t	unknown189[275];
	/*488*/
};

struct EnterWorld_Struct {
	/*000*/	char	name[64];
	/*064*/	uint32_t	tutorial;		// 01 on "Enter Tutorial", 00 if not
	/*068*/	uint32_t	return_home;		// 01 on "Return Home", 00 if not
};

/* Name Approval Struct */
/* Len: */
/* Opcode: 0x8B20*/
struct NameApproval
{
	char name[64];
	uint32_t race;
	uint32_t class_;
	uint32_t deity;
};

/*
** Entity identification struct
** Size: 4 bytes
** OPCodes: OP_DeleteSpawn, OP_Assist
*/
struct EntityId_Struct
{
	/*00*/	uint32_t	entity_id;
	/*04*/
};

struct Duel_Struct
{
	uint32_t duel_initiator;
	uint32_t duel_target;
};

struct DuelResponse_Struct
{
	uint32_t target_id;
	uint32_t entity_id;
	uint32_t unknown;
};
/*
Cofruben:
Adventure stuff,not a net one,just one for our use
*/
static const uint32_t ADVENTURE_COLLECT = 0;
static const uint32_t ADVENTURE_MASSKILL = 1;
static const uint32_t ADVENTURE_NAMED = 2;
static const uint32_t ADVENTURE_RESCUE = 3;

struct AdventureInfo {
	uint32_t QuestID;
	uint32_t NPCID;
	bool in_use;
	uint32_t status;
	bool ShowCompass;
	uint32_t Objetive;// can be item to collect,mobs to kill,boss to kill and someone to rescue.
	uint32_t ObjetiveValue;// number of items,or number of needed mob kills.
	char text[512];
	uint8_t type;
	uint32_t minutes;
	uint32_t points;
	float x;
	float y;
	uint32_t zoneid;
	uint32_t zonedungeonid;
};
///////////////////////////////////////////////////////////////////////////////


/*
** Color_Struct
** Size: 4 bytes
** Used for convenience
** Merth: Gave struct a name so gcc 2.96 would compile
**
*/
struct Color_Struct
{
	union
	{
		struct
		{
			uint8_t	blue;
			uint8_t	green;
			uint8_t	red;
			uint8_t	use_tint;	// if there's a tint this is FF
		} rgb;
		uint32_t color;
	};
};

/*
** Character Selection Struct
** Length: 1704 Bytes
**
*/
struct CharacterSelect_Struct {
	/*0000*/	uint32_t	race[10];			// Characters Race
	/*0040*/	Color_Struct	cs_colors[10][9];	// Characters Equipment Colors
	/*0400*/	uint8_t	beardcolor[10];			// Characters beard Color
	/*0410*/	uint8_t	hairstyle[10];			// Characters hair style
	/*0420*/	uint32_t	equip[10][9];			// 0=helm, 1=chest, 2=arm, 3=bracer, 4=hand, 5=leg, 6=boot, 7=melee1, 8=melee2  (Might not be)
	/*0780*/	uint32_t	secondary[10];			// Characters secondary IDFile number
	/*0820*/	uint8_t	unknown820[10];			// 10x ff
	/*0830*/	uint8_t	unknown830[2];			// 2x 00
	/*0832*/	uint32_t	deity[10];			// Characters Deity
	/*0872*/	uint8_t	gohome[10];			// 1=Go Home available, 0=not
	/*0882*/	uint8_t	tutorial[10];			// 1=Tutorial available, 0=not
	/*0892*/	uint8_t	beard[10];			// Characters Beard Type
	/*0902*/	uint8_t	unknown902[10];			// 10x ff
	/*0912*/	uint32_t	primary[10];			// Characters primary IDFile number
	/*0952*/	uint8_t	haircolor[10];			// Characters Hair Color
	/*0962*/	uint8_t	unknown0962[2];			// 2x 00
	/*0964*/	uint32_t	zone[10];			// Characters Current Zone
	/*1004*/	uint8_t	class_[10];			// Characters Classes
	/*1014*/	uint8_t	face[10];			// Characters Face Type
	/*1024*/	char	name[10][64];			// Characters Names
	/*1664*/	uint8_t	gender[10];			// Characters Gender
	/*1674*/	uint8_t	eyecolor1[10];			// Characters Eye Color
	/*1684*/	uint8_t	eyecolor2[10];			// Characters Eye 2 Color
	/*1694*/	uint8_t	level[10];			// Characters Levels
	/*1704*/
};

/*
** Generic Spawn Struct
** Length: 257 Bytes
** Fields from old struct not yet found:
**	float	size;
**	float	walkspeed;	// probably one of the ff 33 33 33 3f
**	float	runspeed;	// probably one of the ff 33 33 33 3f
**	uint8_t	traptype;	// 65 is disarmable trap, 66 and 67 are invis triggers/traps
**	uint8_t	npc_armor_graphic;	// 0xFF=Player, 0=none, 1=leather, 2=chain, 3=steelplate
**	uint8_t	npc_helm_graphic;	// 0xFF=Player, 0=none, 1=leather, 2=chain, 3=steelplate
**
*/

/*
** Generic Spawn Struct
** Length: 383 Octets
** Used in:
**   spawnZoneStruct
**   dbSpawnStruct
**   petStruct
**   newSpawnStruct
*/
/*
showeq -> eqemu
sed -e 's/_t//g' -e 's/seto_0xFF/set_to_0xFF/g'
*/
struct Spawn_Struct {
	/*0000*/ uint8_t unknown0000;
	/*0001*/ uint8_t  gm;             // 0=no, 1=gm
	/*0002*/ uint8_t unknown0003;
	/*0003*/ uint8_t   aaitle;       // 0=none, 1=general, 2=archtype, 3=class
	/*0004*/ uint8_t unknown0004;
	/*0005*/ uint8_t  anon;           // 0=normal, 1=anon, 2=roleplay
	/*0006*/ uint8_t  face;	          // Face id for players
	/*0007*/ char     name[64];       // Player's Name
	/*0071*/ uint16_t  deity;          // Player's Deity
	/*0073*/ uint16_t unknown0073;
	/*0075*/ float    size;           // Model size
	/*0079*/ uint32_t unknown0079;
	/*0083*/ uint8_t  NPC;            // 0=player,1=npc,2=pc corpse,3=npc corpse,a
	/*0084*/ uint8_t  invis;          // Invis (0=not, 1=invis)
	/*0085*/ uint8_t  haircolor;      // Hair color
	/*0086*/ uint8_t  curHp;          // Current hp %%% wrong
	/*0087*/ uint8_t  max_hp;         // (name prolly wrong)takes on the value 100 for players, 100 or 110 for NPCs and 120 for PC corpses...
	/*0088*/ uint8_t  findable;       // 0=can't be found, 1=can be found
	/*0089*/ uint8_t unknown0089[5];
	/*0094*/ signed   deltaHeading : 10;// change in heading
	signed   x : 19;           // x coord
	signed   padding0054 : 3;  // ***Placeholder
	/*0098*/ signed   y : 19;           // y coord
	signed   animation : 10;   // animation
	signed   padding0058 : 3;  // ***Placeholder
	/*0102*/ signed   z : 19;           // z coord
	signed   deltaY : 13;      // change in y
	/*0106*/ signed   deltaX : 13;      // change in x
	unsigned heading : 12;     // heading
	signed   padding0066 : 7;  // ***Placeholder
	/*0110*/ signed   deltaZ : 13;      // change in z
	signed   padding0070 : 19; // ***Placeholder
	/*0114*/ uint8_t  eyecolor1;      // Player's left eye color
	/*0115*/ uint8_t unknown0115[24];
	/*0139*/ uint8_t  showhelm;       // 0=no, 1=yes
	/*0140*/ uint8_t unknown0140[4];
	/*0144*/ uint8_t  is_npc;         // 0=no, 1=yes
	/*0145*/ uint8_t  hairstyle;      // Hair style
	/*0146*/ uint8_t  beardcolor;     // Beard color
	/*0147*/ uint8_t unknown0147[4];
	/*0151*/ uint8_t  level;          // Spawn Level
	/*0152*/ uint8_t  unknown0259[4]; // ***Placeholder
	/*0156*/ uint8_t  beard;          // Beard style
	/*0157*/ char     suffix[32];     // Player's suffix (of Veeshan, etc.)
	/*0189*/ uint32_t petOwnerId;     // If this is a pet, the spawn id of owner
	/*0193*/ uint8_t   guildrank;      // 0=normal, 1=officer, 2=leader
	/*0194*/ uint8_t unknown0194[3];
	/*0197*/ union
	{
		struct
		{
			/*0197*/ uint32_t equip_helmet;    // Equipment: Helmet Visual
			/*0201*/ uint32_t equip_chest;     // Equipment: Chest Visual
			/*0205*/ uint32_t equip_arms;      // Equipment: Arms Visual
			/*0209*/ uint32_t equip_bracers;   // Equipment: Bracers Visual
			/*0213*/ uint32_t equip_hands;     // Equipment: Hands Visual
			/*0217*/ uint32_t equip_legs;      // Equipment: Legs Visual
			/*0221*/ uint32_t equip_feet;      // Equipment: Feet Visual
			/*0225*/ uint32_t equip_primary;   // Equipment: Primary Visual
			/*0229*/ uint32_t equip_secondary; // Equipment: Secondary Visual
		} equip;
		/*0197*/ uint32_t equipment[9];  // Array elements correspond to struct equipment above
	};
	/*0233*/ float    runspeed;       // Speed when running
	/*0036*/ uint8_t  afk;            // 0=no, 1=afk
	/*0238*/ uint32_t guildID;        // Current guild
	/*0242*/ char     title[32];      // Title
	/*0274*/ uint8_t unknown0274;
	/*0275*/ uint8_t  helm;           // Helm texture
	/*0276*/ uint8_t  set_to_0xFF[8]; // ***Placeholder (all ff)
	/*0284*/ uint32_t race;           // Spawn race
	/*0288*/ uint32_t unknown0288;
	/*0292*/ char     lastName[32];   // Player's Lastname
	/*0324*/ float    walkspeed;      // Speed when walking
	/*0328*/ uint8_t unknown0328;
	/*0329*/ uint8_t  is_pet;         // 0=no, 1=yes
	/*0330*/ uint8_t  light;          // Spawn's lightsource %%% wrong
	/*0331*/ uint8_t  class_;         // Player's class
	/*0332*/ uint8_t  eyecolor2;      // Left eye color
	/*0333*/ uint8_t flymode;
	/*0334*/ uint8_t  gender;         // Gender (0=male, 1=female)
	/*0335*/ uint8_t  bodytype;       // Bodytype
	/*0336*/ uint8_t unknown0336[3];
	union
	{
		/*0339*/ uint8_t equip_chest2;     // Second place in packet for chest texture (usually 0xFF in live packets)
		// Not sure why there are 2 of them, but it effects chest texture!
		/*0339*/ uint8_t mount_color;      // drogmor: 0=white, 1=black, 2=green, 3=red
		// horse: 0=brown, 1=white, 2=black, 3=tan
	};
	/*0340*/ uint32_t spawnId;        // Spawn Id
	/*0344*/ uint8_t unknown0344[4];
	/*0348*/ union
	{
		struct
		{
			/*0348*/ Color_Struct color_helmet;    // Color of helmet item
			/*0352*/ Color_Struct color_chest;     // Color of chest item
			/*0356*/ Color_Struct color_arms;      // Color of arms item
			/*0360*/ Color_Struct color_bracers;   // Color of bracers item
			/*0364*/ Color_Struct color_hands;     // Color of hands item
			/*0368*/ Color_Struct color_legs;      // Color of legs item
			/*0372*/ Color_Struct color_feet;      // Color of feet item
			/*0376*/ Color_Struct color_primary;   // Color of primary item
			/*0380*/ Color_Struct color_secondary; // Color of secondary item
		} equipment_colors;
		/*0348*/ Color_Struct colors[9]; // Array elements correspond to struct equipment_colors above
	};
	/*0384*/ uint8_t  lfg;            // 0=off, 1=lfg on
	/*0385*/

};

/*
** New Spawn
** Length: 176 Bytes
** OpCode: 4921
*/
struct NewSpawn_Struct
{
	struct Spawn_Struct spawn;	// Spawn Information
};

struct ClientZoneEntry_Struct {
	/*0000*/	uint32_t	unknown00;
	/*0004*/	char	char_name[64];			// Character Name
};

/*
** Server Zone Entry Struct
** Length: 452 Bytes
** OPCodes: OP_ServerZoneEntry
**
*/
struct ServerZoneEntry_Struct
{
	struct NewSpawn_Struct player;
};

struct NewZone_Struct {
	/*0000*/	char	char_name[64];			// Character Name
	/*0064*/	char	zone_short_name[32];	// Zone Short Name
	/*0096*/	char	zone_long_name[278];	// Zone Long Name
	/*0374*/	uint8_t	ztype;					// Zone type (usually FF)
	/*0375*/	uint8_t	fog_red[4];				// Zone fog (red)
	/*0379*/	uint8_t	fog_green[4];			// Zone fog (green)
	/*0383*/	uint8_t	fog_blue[4];			// Zone fog (blue)
	/*0387*/	uint8_t	unknown323;
	/*0388*/	float	fog_minclip[4];
	/*0404*/	float	fog_maxclip[4];
	/*0420*/	float	gravity;
	/*0424*/	uint8_t	time_type;
	/*0425*/    uint8_t   rain_chance[4];
	/*0429*/    uint8_t   rain_duration[4];
	/*0433*/    uint8_t   snow_chance[4];
	/*0437*/    uint8_t   snow_duration[4];
	/*0441*/	uint8_t	unknown360[33];
	/*0474*/	uint8_t	sky;					// Sky Type
	/*0475*/	uint8_t	unknown331[13];			// ***Placeholder
	/*0488*/	float	zone_exp_multiplier;	// Experience Multiplier
	/*0492*/	float	safe_y;					// Zone Safe Y
	/*0496*/	float	safe_x;					// Zone Safe X
	/*0500*/	float	safe_z;					// Zone Safe Z
	/*0504*/	float	max_z;					// Guessed
	/*0508*/	float	underworld;				// Underworld, min z (Not Sure?)
	/*0512*/	float	minclip;				// Minimum View Distance
	/*0516*/	float	maxclip;				// Maximum View DIstance
	/*0520*/	uint8_t	unknown_end[84];		// ***Placeholder
	/*0604*/	char	zone_short_name2[68];
	/*0672*/	char	unknown672[12];
	/*0684*/	uint16_t	zone_id;
	/*0686*/	uint16_t	zone_instance;
	/*0688*/	uint32_t	unknown688;
	/*0692*/	uint8_t	unknown692[8];
	/*0700*/
};

/*
** Memorize Spell Struct
** Length: 12 Bytes
**
*/
struct MemorizeSpell_Struct {
	uint32_t slot;     // Spot in the spell book/memorized slot
	uint32_t spell_id; // Spell id (200 or c8 is minor healing, etc)
	uint32_t scribing; // 1 if memorizing a spell, set to 0 if scribing to book, 2 if un-memming
	uint32_t unknown12;
};

/*
** Make Charmed Pet
** Length: 12 Bytes
**
*/
struct Charm_Struct {
	/*00*/	uint32_t	owner_id;
	/*04*/	uint32_t	pet_id;
	/*08*/	uint32_t	command;    // 1: make pet, 0: release pet
	/*12*/
};

struct InterruptCast_Struct
{
	uint32_t spawnid;
	uint32_t messageid;
	char	message[1];
};

struct DeleteSpell_Struct
{
	/*000*/int16_t	spell_slot;
	/*002*/uint8_t	unknowndss002[2];
	/*004*/uint8_t	success;
	/*005*/uint8_t	unknowndss006[3];
	/*008*/
};

struct ManaChange_Struct
{
	uint32_t	new_mana;                  // New Mana AMount
	uint32_t	stamina;
	uint32_t	spell_id;
	uint32_t	unknown12;
};

struct SwapSpell_Struct
{
	uint32_t from_slot;
	uint32_t to_slot;


};

struct BeginCast_Struct
{
	// len = 8
	/*000*/	uint16_t	caster_id;
	/*002*/	uint16_t	spell_id;
	/*004*/	uint32_t	cast_time;		// in miliseconds
};

struct CastSpell_Struct
{
	uint32_t	slot;
	uint32_t	spell_id;
	uint32_t	inventoryslot;  // slot for clicky item, 0xFFFF = normal cast
	uint32_t	target_id;
	uint8_t	cs_unknown[4];
};

/*
** SpawnAppearance_Struct
** Changes client appearance for all other clients in zone
** Size: 8 bytes
** Used in: OP_SpawnAppearance
**
*/
struct SpawnAppearance_Struct
{
	/*0000*/ uint16_t spawn_id;          // ID of the spawn
	/*0002*/ uint16_t type;              // Values associated with the type
	/*0004*/ uint32_t parameter;         // Type of data sent
	/*0008*/
};


// solar: this is used inside profile
struct SpellBuff_Struct
{
	/*000*/	uint8_t	slotid;		//badly named... seems to be 2 for a real buff, 0 otherwise
	/*001*/ uint8_t	level;
	/*002*/	uint8_t	bard_modifier;
	/*003*/	uint8_t	effect;			//not real
	/*004*/	uint32_t	spellid;
	/*008*/ uint32_t	duration;
	/*012*/	uint32_t	counters;
	/*016*/	uint32_t	player_id;	//'global' ID of the caster, for wearoff messages
};

struct SpellBuffFade_Struct {
	/*000*/	uint32_t entityid;
	/*004*/	uint8_t slot;
	/*005*/	uint8_t level;
	/*006*/	uint8_t effect;
	/*007*/	uint8_t unknown7;
	/*008*/	uint32_t spellid;
	/*012*/	uint32_t duration;
	/*016*/	uint32_t unknown016;
	/*020*/	uint32_t unknown020;	//prolly global player ID
	/*024*/	uint32_t slotid;
	/*028*/	uint32_t bufffade;
	/*032*/
};

struct ItemNamePacket_Struct {
	/*000*/	uint32_t item_id;
	/*004*/	uint32_t unkown004;
	/*008*/ char name[64];
	/*072*/
};

// Length: 10
struct ItemProperties_Struct {

	uint8_t	unknown01[2];
	uint8_t	charges;
	uint8_t	unknown02[13];
};

struct GMTrainee_Struct
{
	/*000*/ uint32_t npcid;
	/*004*/ uint32_t playerid;
	/*008*/ uint32_t skills[PACKET_SKILL_ARRAY_SIZE];
	/*408*/ uint8_t unknown408[40];
	/*448*/
};

struct GMTrainEnd_Struct
{
	/*000*/ uint32_t npcid;
	/*004*/ uint32_t playerid;
	/*008*/
};

struct GMSkillChange_Struct {
	/*000*/	uint16_t		npcid;
	/*002*/ uint8_t		unknown1[2];    // something like PC_ID, but not really. stays the same thru the session though
	/*002*/ uint16_t       skillbank;      // 0 if normal skills, 1 if languages
	/*002*/ uint8_t		unknown2[2];
	/*008*/ uint16_t		skill_id;
	/*010*/ uint8_t		unknown3[2];
};
struct ConsentResponse_Struct {
	char grantname[64];
	char ownername[64];
	uint8_t permission;
	char zonename[32];
};

/*
** Name Generator Struct
** Length: 72 bytes
** OpCode: 0x0290
*/
struct NameGeneration_Struct
{
	/*0000*/	uint32_t	race;
	/*0004*/	uint32_t	gender;
	/*0008*/	char	name[64];
	/*0072*/
};

/*
** Character Creation struct
** Length: 140 Bytes
** OpCode: 0x0113
*/
struct CharCreate_Struct
{
	/*0000*/	uint32_t	class_;
	/*0004*/	uint32_t	haircolor;	// Might be hairstyle
	/*0008*/	uint32_t	beardcolor;	// Might be beard
	/*0012*/	uint32_t	beard;		// Might be beardcolor
	/*0016*/	uint32_t	gender;
	/*0020*/	uint32_t	race;
	/*0024*/	uint32_t	start_zone;
	// 0 = odus
	// 1 = qeynos
	// 2 = halas
	// 3 = rivervale
	// 4 = freeport
	// 5 = neriak
	// 6 = gukta/grobb
	// 7 = ogguk
	// 8 = kaladim
	// 9 = gfay
	// 10 = felwithe
	// 11 = akanon
	// 12 = cabalis
	// 13 = shar vahl
	/*0028*/	uint32_t	hairstyle;	// Might be haircolor
	/*0032*/	uint32_t	deity;
	/*0036*/	uint32_t	STR;
	/*0040*/	uint32_t	STA;
	/*0044*/	uint32_t	AGI;
	/*0048*/	uint32_t	DEX;
	/*0052*/	uint32_t	WIS;
	/*0056*/	uint32_t	INT;
	/*0060*/	uint32_t	CHA;
	/*0064*/	uint32_t	face;		// Could be unknown0076
	/*0068*/	uint32_t	eyecolor1;	//its possiable we could have these switched
	/*0073*/	uint32_t	eyecolor2;	//since setting one sets the other we really can't check
	/*0076*/	uint32_t	tutorial;
	/*0080*/
};

/*
*Used in PlayerProfile
*/
struct AA_Array
{
	uint32_t AA;
	uint32_t value;
};


static const uint32_t MAX_PP_DISCIPLINES = 100;

struct Disciplines_Struct {
	uint32_t values[MAX_PP_DISCIPLINES];
};

static const uint32_t MAX_PLAYER_TRIBUTES = 5;
static const uint32_t MAX_PLAYER_BANDOLIER = 4;
static const uint32_t MAX_PLAYER_BANDOLIER_ITEMS = 4;
static const uint32_t TRIBUTE_NONE = 0xFFFFFFFF;
struct Tribute_Struct {
	uint32_t tribute;
	uint32_t tier;
};

//len = 72
struct BandolierItem_Struct {
	uint32_t item_id;
	uint32_t icon;
	char item_name[64];
};

//len = 320
enum { //bandolier item positions
	bandolierMainHand = 0,
	bandolierOffHand,
	bandolierRange,
	bandolierAmmo
};
struct Bandolier_Struct {
	char name[32];
	BandolierItem_Struct items[MAX_PLAYER_BANDOLIER_ITEMS];
};
struct PotionBelt_Struct {
	BandolierItem_Struct items[MAX_PLAYER_BANDOLIER_ITEMS];
};

static const uint32_t MAX_GROUP_LEADERSHIP_AA_ARRAY = 16;
static const uint32_t MAX_RAID_LEADERSHIP_AA_ARRAY = 16;
static const uint32_t MAX_LEADERSHIP_AA_ARRAY = (MAX_GROUP_LEADERSHIP_AA_ARRAY + MAX_RAID_LEADERSHIP_AA_ARRAY);
struct GroupLeadershipAA_Struct {
	union {
		struct {
			uint32_t groupAAMarkNPC;
			uint32_t groupAANPCHealth;
			uint32_t groupAADelegateMainAssist;
			uint32_t groupAADelegateMarkNPC;
			uint32_t groupAA4;
			uint32_t groupAA5;
			uint32_t groupAAInspectBuffs;
			uint32_t groupAA7;
			uint32_t groupAASpellAwareness;
			uint32_t groupAAOffenseEnhancement;
			uint32_t groupAAManaEnhancement;
			uint32_t groupAAHealthEnhancement;
			uint32_t groupAAHealthRegeneration;
			uint32_t groupAAFindPathToPC;
			uint32_t groupAAHealthOfTargetsTarget;
			uint32_t groupAA15;
		};
		uint32_t ranks[MAX_GROUP_LEADERSHIP_AA_ARRAY];
	};
};

struct RaidLeadershipAA_Struct {
	union {
		struct {
			uint32_t raidAAMarkNPC;
			uint32_t raidAANPCHealth;
			uint32_t raidAADelegateMainAssist;
			uint32_t raidAADelegateMarkNPC;
			uint32_t raidAA4;
			uint32_t raidAA5;
			uint32_t raidAA6;
			uint32_t raidAASpellAwareness;
			uint32_t raidAAOffenseEnhancement;
			uint32_t raidAAManaEnhancement;
			uint32_t raidAAHealthEnhancement;
			uint32_t raidAAHealthRegeneration;
			uint32_t raidAAFindPathToPC;
			uint32_t raidAAHealthOfTargetsTarget;
			uint32_t raidAA14;
			uint32_t raidAA15;
		};
		uint32_t ranks[MAX_RAID_LEADERSHIP_AA_ARRAY];
	};
};

struct LeadershipAA_Struct {
	union {
		struct {
			GroupLeadershipAA_Struct group;
			RaidLeadershipAA_Struct raid;
		};
		uint32_t ranks[MAX_LEADERSHIP_AA_ARRAY];
	};
};

/**
* A bind point.
* Size: 20 Octets
*/
struct BindStruct {
	/*000*/ uint32_t zoneId;
	/*004*/ float x;
	/*008*/ float y;
	/*012*/ float z;
	/*016*/ float heading;
	/*020*/
};

struct PVPStatsEntry_Struct
{
	/*00*/ char Name[64];
	/*64*/ uint32_t Level;
	/*68*/ uint32_t Race;
	/*72*/ uint32_t Class;
	/*76*/ uint32_t Zone;
	/*80*/ uint32_t Time;
	/*84*/ uint32_t Points;
	/*88*/
};


/*
** Player Profile
**
** Length: 4308 bytes
** OpCode: 0x006a
*/
static const uint32_t MAX_PP_LANGUAGE = 28;
static const uint32_t MAX_PP_SPELLBOOK = 400;
static const uint32_t MAX_PP_MEMSPELL = 9;
static const uint32_t MAX_PP_SKILL = PACKET_SKILL_ARRAY_SIZE;	// 100 - actual skills buffer size
static const uint32_t MAX_PP_AA_ARRAY = 240;
static const uint32_t MAX_GROUP_MEMBERS = 6;
static const uint32_t MAX_RECAST_TYPES = 20;
/*
showeq -> eqemu
sed -e 's/_t//g' -e 's/MAX_AA/MAX_PP_AA_ARRAY/g' \
-e 's/MAX_SPELL_SLOTS/MAX_PP_MEMSPELL/g' \
-e 's/MAX_KNOWN_SKILLS/MAX_PP_SKILL/g' \
-e 's/MAXRIBUTES/MAX_PLAYER_TRIBUTES/g' \
-e 's/MAX_BUFFS/BUFF_COUNT/g' \
-e 's/MAX_KNOWN_LANGS/MAX_PP_LANGUAGE/g' \
-e 's/MAX_RECASTYPES/MAX_RECAST_TYPES/g' \
-e 's/spellBuff/SpellBuff_Struct/g' \
-e 's/lastName/last_name/g' \
-e 's/guildID/guild_id/g' \
-e 's/itemint/item_tint/g' \
-e 's/MANA/mana/g' \
-e 's/curHp/cur_hp/g' \
-e 's/sSpellBook/spell_book/g' \
-e 's/sMemSpells/mem_spells/g' \
-e 's/uint32_t[ \t]*disciplines\[MAX_DISCIPLINES\]/Disciplines_Struct  disciplines/g' \
-e 's/aa_unspent/aapoints/g' \
-e 's/aa_spent/aapoints_spent/g' \
-e 's/InlineItem[ \t]*potionBelt\[MAX_POTIONS_IN_BELT\]/PotionBelt_Struct  potionbelt/g' \
-e 's/ldon_guk_points/ldon_points_guk/g' \
-e 's/ldon_mir_points/ldon_points_mir/g' \
-e 's/ldon_mmc_points/ldon_points_mmc/g' \
-e 's/ldon_ruj_points/ldon_points_ruj/g' \
-e 's/ldonak_points/ldon_points_tak/g' \
-e 's/ldon_avail_points/ldon_points_available/g' \
-e 's/tributeTime/tribute_time_remaining/g' \
-e 's/careerTribute/career_tribute_points/g' \
-e 's/currentTribute/tribute_points/g' \
-e 's/tributeActive/tribute_active/g' \
-e 's/TributeStruct/Tribute_Struct/g' \
-e 's/expGroupLeadAA/group_leadership_exp/g' \
-e 's/expRaidLeadAA/raid_leadership_exp/g' \
-e 's/groupLeadAAUnspent/group_leadership_points/g' \
-e 's/raidLeadAAUnspent/raid_leadership_points/g' \
-e 's/uint32_t[ \t]*leadershipAAs\[MAX_LEAD_AA\]/LeadershipAA_Struct leader_abilities/g' \
-e 's/BandolierStruct/Bandolier_Struct/g' \
-e 's/MAX_BANDOLIERS/MAX_PLAYER_BANDOLIER/g' \
-e 's/birthdayTime/birthday/g' \
-e 's/lastSaveTime/lastlogin/g' \
-e 's/zoneId/zone_id/g' \
-e 's/hunger/hunger_level/g' \
-e 's/thirst/thirst_level/g' \
-e 's/guildstatus/guildrank/g' \
-e 's/airRemaining/air_remaining/g' \



*/
struct PlayerProfile_Struct
{
	/*00000*/ uint32_t  checksum;           //
	/*00004*/ uint32_t  gender;             // Player Gender - 0 Male, 1 Female
	/*00008*/ uint32_t  race;               // Player race
	/*00012*/ uint32_t  class_;             // Player class
	/*00016*/ uint32_t  unknown00016;       // ***Placeholder
	/*00020*/ uint8_t   level;              // Level of player
	/*00021*/ uint8_t   level1;             // Level of player (again?)
	/*00022*/ uint8_t   unknown00022[2];    // ***Placeholder
	/*00024*/ BindStruct binds[5];          // Bind points (primary is first)
	/*00124*/ uint32_t  deity;              // deity
	/*00128*/ uint32_t  intoxication;       // Alcohol level (in ticks till sober?)
	/*00132*/ uint32_t  spellSlotRefresh[MAX_PP_MEMSPELL]; // Refresh time (millis)
	/*00168*/ uint32_t  abilitySlotRefresh;
	/*00172*/ uint8_t   haircolor;          // Player hair color
	/*00173*/ uint8_t   beardcolor;         // Player beard color
	/*00174*/ uint8_t   eyecolor1;          // Player left eye color
	/*00175*/ uint8_t   eyecolor2;          // Player right eye color
	/*00176*/ uint8_t   hairstyle;          // Player hair style
	/*00177*/ uint8_t   beard;              // Player beard type
	/*00178*/ uint8_t unknown00178[10];
	/*00188*/ uint32_t  item_material[9];   // Item texture/material of worn items
	/*00224*/ uint8_t unknown00224[44];
	/*00268*/ Color_Struct item_tint[9];    // RR GG BB 00
	/*00304*/ AA_Array  aa_array[MAX_PP_AA_ARRAY];   // AAs
	/*02224*/ uint32_t  points;             // Unspent Practice points
	/*02228*/ uint32_t  mana;               // Current mana
	/*02232*/ uint32_t  cur_hp;              // Current HP without +HP equipment
	/*02236*/ uint32_t  STR;                // Strength
	/*02240*/ uint32_t  STA;                // Stamina
	/*02244*/ uint32_t  CHA;                // Charisma
	/*02248*/ uint32_t  DEX;                // Dexterity
	/*02252*/ uint32_t  INT;                // Intelligence
	/*02256*/ uint32_t  AGI;                // Agility
	/*02260*/ uint32_t  WIS;                // Wisdom
	/*02264*/ uint8_t   face;               // Player face
	/*02265*/ uint8_t unknown02264[47];
	/*02312*/ uint32_t   spell_book[MAX_PP_SPELLBOOK];    // List of the Spells in spellbook
	/*03912*/ uint8_t   unknown4184[448];   // all 0xff after last spell
	/*04360*/ uint32_t   mem_spells[MAX_PP_MEMSPELL]; // List of spells memorized
	/*04396*/ uint8_t unknown04396[32];
	/*04428*/ uint32_t  platinum;           // Platinum Pieces on player
	/*04432*/ uint32_t  gold;               // Gold Pieces on player
	/*04436*/ uint32_t  silver;             // Silver Pieces on player
	/*04440*/ uint32_t  copper;             // Copper Pieces on player
	/*04444*/ uint32_t  platinum_cursor;    // Platinum Pieces on cursor
	/*04448*/ uint32_t  gold_cursor;        // Gold Pieces on cursor
	/*04452*/ uint32_t  silver_cursor;      // Silver Pieces on cursor
	/*04456*/ uint32_t  copper_cursor;      // Copper Pieces on cursor
	/*04460*/ uint32_t  skills[MAX_PP_SKILL]; // [400] List of skills	// 100 dword buffer
	/*04860*/ uint8_t unknown04760[136];
	/*04996*/ uint32_t  toxicity;           // Potion Toxicity (15=too toxic, each potion adds 3)
	/*05000*/ uint32_t  thirst_level;             // Drink (ticks till next drink)
	/*05004*/ uint32_t  hunger_level;             // Food (ticks till next eat)
	/*05008*/ SpellBuff_Struct buffs[BUFF_COUNT];   // Buffs currently on the player
	/*05508*/ Disciplines_Struct  disciplines; // Known disciplines
	/*05908*/ uint32_t recastTimers[MAX_RECAST_TYPES]; // Timers (GMT of last use)
	/*05988*/ uint8_t unknown05008[160];
	/*06148*/ uint32_t  endurance;          // Current endurance
	/*06152*/ uint32_t  aapoints_spent;           // Number of spent AA points
	/*06156*/ uint32_t  aapoints;         // Unspent AA points
	/*06160*/ uint8_t unknown06160[4];
	/*06164*/ Bandolier_Struct bandoliers[MAX_PLAYER_BANDOLIER]; // bandolier contents
	/*07444*/ uint8_t unknown07444[5120];
	/*12564*/ PotionBelt_Struct  potionbelt; // potion belt
	/*12852*/ uint8_t unknown12852[8];
	/*12860*/ uint32_t available_slots;
	/*12864*/ uint8_t unknown12864[76];
	/*12940*/ char      name[64];           // Name of player
	/*13004*/ char      last_name[32];       // Last name of player
	/*13036*/ uint32_t   guild_id;            // guildid
	/*13040*/ uint32_t  birthday;       // character birthday
	/*13044*/ uint32_t  lastlogin;       // character last save time
	/*13048*/ uint32_t  timePlayedMin;      // time character played
	/*13052*/ uint8_t   pvp;                // 1=pvp, 0=not pvp
	/*13053*/ uint8_t   anon;               // 2=roleplay, 1=anon, 0=not anon
	/*13054*/ uint8_t   gm;                 // 0=no, 1=yes (guessing!)
	/*13055*/ uint8_t    guildrank;        // 0=member, 1=officer, 2=guildleader
	/*13056*/ uint32_t  guildbanker;
	/*13060*/ uint8_t unknown13054[8];
	/*13068*/ uint32_t  exp;                // Current Experience
	/*13072*/ uint8_t unknown13072[8];
	/*13080*/ uint32_t timeentitledonaccount; // In days, displayed in /played
	/*13084*/ uint8_t   languages[MAX_PP_LANGUAGE]; // List of languages
	/*13109*/ uint8_t   unknown13109[4];    // All 0x00 (language buffer?)
	/*13116*/ float     x;                  // Players x position
	/*13120*/ float     y;                  // Players y position
	/*13124*/ float     z;                  // Players z position
	/*13128*/ float     heading;            // Players heading
	/*13132*/ uint8_t   unknown13132[4];    // ***Placeholder
	/*13136*/ uint32_t  platinum_bank;      // Platinum Pieces in Bank
	/*13140*/ uint32_t  gold_bank;          // Gold Pieces in Bank
	/*13144*/ uint32_t  silver_bank;        // Silver Pieces in Bank
	/*13148*/ uint32_t  copper_bank;        // Copper Pieces in Bank
	/*13152*/ uint32_t  platinum_shared;    // Shared platinum pieces
	/*13156*/ uint8_t unknown13156[84];
	/*13240*/ uint32_t  expansions;         // Bitmask for expansions
	/*13244*/ uint8_t unknown13244[12];
	/*13256*/ uint32_t  autosplit;          // 0 = off, 1 = on
	/*13260*/ uint8_t unknown13260[16];
	/*13276*/ uint16_t  zone_id;             // see zones.h
	/*13278*/ uint16_t  zoneInstance;       // Instance id
	/*13280*/ char      groupMembers[MAX_GROUP_MEMBERS][64];// all the members in group, including self
	/*13664*/ char      groupLeader[64];    // Leader of the group ?
	/*13728*/ uint8_t unknown13728[656];
	/*14384*/ uint32_t  entityid;
	/*14388*/ uint32_t  leadAAActive;       // 0 = leader AA off, 1 = leader AA on
	/*14392*/ uint8_t unknown14392[4];
	/*14396*/ int32_t  ldon_points_guk;    // Earned GUK points
	/*14400*/ int32_t  ldon_points_mir;    // Earned MIR points
	/*14404*/ int32_t  ldon_points_mmc;    // Earned MMC points
	/*14408*/ int32_t  ldon_points_ruj;    // Earned RUJ points
	/*14412*/ int32_t  ldon_points_tak;    // Earned TAK points
	/*14416*/ int32_t  ldon_points_available;  // Available LDON points
	/*14420*/ uint8_t unknown14420[132];
	/*14552*/ uint32_t  tribute_time_remaining;        // Time remaining on tribute (millisecs)
	/*14556*/ uint32_t  career_tribute_points;      // Total favor points for this char
	/*14560*/ uint32_t  unknown7208;        // *** Placeholder
	/*14564*/ uint32_t  tribute_points;     // Current tribute points
	/*14568*/ uint32_t  unknown7216;        // *** Placeholder
	/*14572*/ uint32_t  tribute_active;      // 0 = off, 1=on
	/*14576*/ Tribute_Struct tributes[MAX_PLAYER_TRIBUTES]; // Current tribute loadout
	/*14616*/ uint32_t  unknown14616;
	/*14620*/ double  group_leadership_exp;
	/*14628*/ double  raid_leadership_exp;
	/*14640*/ uint32_t  group_leadership_points; // Unspent group lead AA points
	/*14644*/ uint32_t  raid_leadership_points;  // Unspent raid lead AA points
	/*14644*/ LeadershipAA_Struct leader_abilities; // Leader AA ranks
	/*14772*/ uint8_t unknown14772[128];
	/*14900*/ uint32_t  air_remaining;       // Air supply (seconds)
	/*14904*/ uint32_t  PVPKills;
	/*14908*/ uint32_t  PVPDeaths;
	/*14912*/ uint32_t  PVPCurrentPoints;
	/*14916*/ uint32_t  PVPCareerPoints;
	/*14920*/ uint32_t  PVPBestKillStreak;
	/*14924*/ uint32_t  PVPWorstDeathStreak;
	/*14928*/ uint32_t  PVPCurrentKillStreak;
	/*14932*/ PVPStatsEntry_Struct PVPLastKill;
	/*15020*/ PVPStatsEntry_Struct PVPLastDeath;
	/*15108*/ uint32_t  PVPNumberOfKillsInLast24Hours;
	/*15112*/ PVPStatsEntry_Struct PVPRecentKills[50];
	/*19512*/ uint32_t expAA;               // Exp earned in current AA point
	/*19516*/ uint8_t unknown19516[40];
	/*19556*/ uint32_t currentRadCrystals;  // Current count of radiant crystals
	/*19560*/ uint32_t careerRadCrystals;   // Total count of radiant crystals ever
	/*19564*/ uint32_t currentEbonCrystals; // Current count of ebon crystals
	/*19568*/ uint32_t careerEbonCrystals;  // Total count of ebon crystals ever
	/*19572*/ uint8_t  groupAutoconsent;    // 0=off, 1=on
	/*19573*/ uint8_t  raidAutoconsent;     // 0=off, 1=on
	/*19574*/ uint8_t  guildAutoconsent;    // 0=off, 1=on
	/*19575*/ uint8_t  unknown19575;     // ***Placeholder (6/29/2005)
	/*19576*/ uint32_t level3;              // Titanium looks here to determine the max leadership points you can bank.
	/*19580*/ uint32_t showhelm;            // 0=no, 1=yes
	/*19584*/ uint8_t  unknown19584[4];     // ***Placeholder (10/27/2005)
	/*19588*/ uint32_t unknown19588;        // *** Placeholder
	/*19584*/
};





/*
** Client Target Struct
** Length: 2 Bytes
** OpCode: 6221
*/
struct ClientTarget_Struct {
	/*000*/	uint32_t	new_target;			// Target ID
};

/*
** Target Rejection Struct
** Length: 12 Bytes
** OpCode: OP_TargetReject
*/
struct TargetReject_Struct {
	/*00*/	uint8_t	unknown00[12];
};

struct PetCommand_Struct {
	/*000*/ uint32_t	command;
	/*004*/ uint32_t	unknown;
};

/*
** Delete Spawn
** Length: 4 Bytes
** OpCode: OP_DeleteSpawn
*/
struct DeleteSpawn_Struct
{
	/*00*/ uint32_t spawn_id;             // Spawn ID to delete
	/*04*/
};

/*
** Channel Message received or sent
** Length: 144 Bytes + Variable Length + 1
** OpCode: OP_ChannelMessage
**
*/
struct ChannelMessage_Struct
{
	/*000*/	char	targetname[64];		// Tell recipient
	/*064*/	char	sender[64];			// The senders name (len might be wrong)
	/*128*/	uint32_t	language;			// Language
	/*132*/	uint32_t	chan_num;			// Channel
	/*136*/	uint32_t	cm_unknown4[2];		// ***Placeholder
	/*144*/	uint32_t	skill_in_language;	// The players skill in this language? might be wrong
	/*148*/	char	message[1];			// Variable length message
};

/*
** Special Message
** Length: 4 Bytes + Variable Text Length + 1
** OpCode: OP_SpecialMesg
**
*/
/*
Theres something wrong with this... example live packet:
Server->Client: [ Opcode: OP_SpecialMesg (0x0fab) Size: 244 ]
0: 01 02 00 0A 00 00 00 09 - 05 00 00 42 61 72 73 74  | ...........Barst
16: 72 65 20 53 6F 6E 67 77 - 65 61 76 65 72 00 7C F9  | re Songweaver.|.
32: FF FF 84 FF FF FF 03 00 - 00 00 47 72 65 65 74 69  | ..........Greeti

*/
struct SpecialMesg_Struct
{
	/*00*/	char	header[3];				// 04 04 00 <-- for #emote style msg
	/*03*/	uint32_t	msg_type;				// Color of text (see MT_*** below)
	/*07*/	uint32_t	target_spawn_id;		// Who is it being said to?
	/*11*/	char	sayer[1];				// Who is the source of the info
	/*12*/	uint8_t	unknown12[12];
	/*24*/	char	message[1];				// What is being said?
};

/*
** When somebody changes what they're wearing
**      or give a pet a weapon (model changes)
** Length: 16 Bytes
** Opcode: 9220
*/
struct WearChange_Struct{
	/*000*/ uint16_t spawn_id;
	/*002*/ uint16_t material;
	/*004*/ Color_Struct color;
	/*009*/ uint8_t wear_slot_id;
};

/*
** Type:   Bind Wound Structure
** Length: 8 Bytes
*/
//Fixed for 7-14-04 patch
struct BindWound_Struct
{
	/*002*/	uint16_t	to;			// TargetID
	/*004*/	uint16_t	unknown2;		// ***Placeholder
	/*006*/	uint16_t	type;
	/*008*/	uint16_t	unknown6;
};


/*
** Type:   Zone Change Request (before hand)
** Length: 88 bytes
** OpCode: a320
*/

struct ZoneChange_Struct {
	/*000*/	char	char_name[64];     // Character Name
	/*064*/	uint16_t	zoneID;
	/*066*/	uint16_t	instanceID;
	/*068*/	float	y;
	/*072*/	float	x;
	/*076*/	float	z;
	/*080*/	uint32_t	zone_reason;	//0x0A == death, I think
	/*084*/	int32_t	success;		// =0 client->server, =1 server->client, -X=specific error
	/*088*/
};

struct RequestClientZoneChange_Struct {
	/*00*/	uint16_t	zone_id;
	/*02*/	uint16_t	instance_id;
	/*04*/	float	y;
	/*08*/	float	x;
	/*12*/	float	z;
	/*16*/	float	heading;
	/*20*/	uint32_t	type;	//unknown... values
};

struct Animation_Struct {
	/*00*/	uint16_t spawnid;
	/*02*/	uint8_t action;
	/*03*/	uint8_t value;
	/*04*/
};

// solar: this is what causes the caster to animate and the target to
// get the particle effects around them when a spell is cast
// also causes a buff icon
struct Action_Struct
{
	/* 00 */	uint16_t target;	// id of target
	/* 02 */	uint16_t source;	// id of caster
	/* 04 */	uint16_t level; // level of caster
	/* 06 */	uint16_t instrument_mod;
	/* 08 */	uint32_t unknown08;
	/* 12 */	uint16_t unknown16;
	// some kind of sequence that's the same in both actions
	// as well as the combat damage, to tie em together?
	/* 14 */	uint32_t sequence;
	/* 18 */	uint32_t unknown18;
	/* 22 */	uint8_t type;		// 231 (0xE7) for spells
	/* 23 */	uint32_t unknown23;
	/* 27 */	uint16_t spell;	// spell id being cast
	/* 29 */	uint8_t unknown29;
	// this field seems to be some sort of success flag, if it's 4
	/* 30 */	uint8_t buff_unknown;	// if this is 4, a buff icon is made
	/* 31 */
};

// solar: this is what prints the You have been struck. and the regular
// melee messages like You try to pierce, etc.  It's basically the melee
// and spell damage message
struct CombatDamage_Struct
{
	/* 00 */	uint16_t	target;
	/* 02 */	uint16_t	source;
	/* 04 */	uint8_t	type; //slashing, etc.  231 (0xE7) for spells
	/* 05 */	uint16_t	spellid;
	/* 07 */	uint32_t	damage;
	/* 11 */	uint32_t unknown11;
	/* 15 */	uint32_t sequence;	// see above notes in Action_Struct
	/* 19 */	uint32_t	unknown19;
	/* 23 */
};

/*
** Consider Struct
** Length: 24 Bytes
** OpCode: 3721
*/
struct Consider_Struct{
	/*000*/ uint32_t	playerid;               // PlayerID
	/*004*/ uint32_t	targetid;               // TargetID
	/*008*/ uint32_t	faction;                // Faction
	/*0012*/ uint32_t	level;                  // Level
	/*016*/ int32_t	cur_hp;                  // Current Hitpoints
	/*020*/ int32_t	max_hp;                  // Maximum Hitpoints
	/*024*/ uint8_t pvpcon;     // Pvp con flag 0/1
	/*025*/ uint8_t	unknown3[3];
};

/*
** Spawn Death Blow
** Length: 32 Bytes
** OpCode: 0114
*/
struct Death_Struct
{
	/*000*/	uint32_t	spawn_id;
	/*004*/	uint32_t	killer_id;
	/*008*/	uint32_t	corpseid;	// was corpseid
	/*012*/	uint32_t	attack_skill;	// was type
	/*016*/	uint32_t	spell_id;
	/*020*/ uint32_t	bindzoneid;	//bindzoneid?
	/*024*/	uint32_t	damage;
	/*028*/	uint32_t	unknown028;
};

struct BecomeCorpse_Struct {
	uint32_t	spawn_id;
	float y;
	float x;
	float z;
};

/*
** Spawn position update
**	Struct sent from server->client to update position of
**	another spawn's position update in zone (whether NPC or PC)
**
*/
struct MobPositionUpdate_Struct
{
	/*0000*/ uint16_t		spawn_id;
	/*0002*/ int32_t		delta_heading : 10,  // change in heading
	x_pos : 19,             // x coord
		padding0002 : 3;    // ***Placeholder
	/*0006*/ int32_t		y_pos : 19,             // y coord
	animation : 10,     // animation
			padding0006 : 3;    // ***Placeholder
	/*0010*/ int32_t		z_pos : 19,             // z coord
	delta_y : 13;        // change in y
	/*0014*/ int32_t		delta_x : 13,        // change in x
	heading : 12,       // heading
		  padding0014 : 7;    // ***Placeholder
	/*0018*/ int32_t		delta_z : 13,        // change in z
	padding0018 : 19;   // ***Placeholder
	/*0022*/
};

/*
** Player position update
**	Struct sent from client->server to update
**	player position on server
**
*/
struct PlayerPositionUpdateClient_Struct
{
	/*0000*/ uint16_t	spawn_id;
	/*0022*/ uint16_t	sequence;	//increments one each packet
	/*0004*/ float y_pos;                 // y coord
	/*0008*/ float delta_z;            // Change in z
	/*0016*/ float delta_x;            // Change in x
	/*0012*/ float delta_y;            // Change in y
	/*0020*/ int32_t animation : 10,     // animation
	delta_heading : 10,  // change in heading
				padding0020 : 12;   // ***Placeholder (mostly 1)
	/*0024*/ float x_pos;                 // x coord
	/*0028*/ float z_pos;                 // z coord
	/*0034*/ uint16_t heading : 12,     // Directional heading
	padding0004 : 4;  // ***Placeholder
	/*0032*/ uint8_t unknown0006[2];  // ***Placeholder
	/*0036*/
};

/*
** Spawn HP Update
** Length: 10 Bytes
** OpCode: OP_HPUpdate
*/
struct ExactHPUpdate_Struct
{
	/*00*/ uint32_t	cur_hp;               // Id of spawn to update
	/*04*/ int32_t	max_hp;                 // Maximum hp of spawn
	/*08*/ int16_t	spawn_id;                 // Current hp of spawn
	/*10*/
};
struct HPUpdate_Struct
{
	/*01*/ int16_t	spawn_id;
	/*00*/ uint8_t	hp;
};
/*
** Stamina
** Length: 8 Bytes
** OpCode: 5721
*/
struct Stamina_Struct {
	/*00*/ uint32_t food;                     // (low more hungry 127-0)
	/*02*/ uint32_t water;                    // (low more thirsty 127-0)
};

/*
** Level Update
** Length: 12 Bytes
*/
struct LevelUpdate_Struct
{
	/*00*/ uint32_t level;                  // New level
	/*04*/ uint32_t level_old;              // Old level
	/*08*/ uint32_t exp;                    // Current Experience
};

/*
** Experience Update
** Length: 14 Bytes
** OpCode: 9921
*/
struct ExpUpdate_Struct
{
	/*0000*/ uint32_t exp;                    // Current experience ratio from 0 to 330
	/*0004*/ uint32_t aaxp; // @BP ??
};

/*
** Item Packet Struct - Works on a variety of opcodes
** Packet Types: See ItemPacketType enum
**
*/
enum ItemPacketType
{
	ItemPacketViewLink = 0x00,
	ItemPacketTradeView = 0x65,
	ItemPacketLoot = 0x66,
	ItemPacketTrade = 0x67,
	ItemPacketCharInventory = 0x69,
	ItemPacketSummonItem = 0x6A,
	ItemPacketTributeItem = 0x6C,
	ItemPacketMerchant = 0x64,
	ItemPacketWorldContainer = 0x6B
};
struct ItemPacket_Struct
{
	/*00*/	ItemPacketType	PacketType;
	/*04*/	char			SerializedItem[1];
	/*xx*/
};

struct BulkItemPacket_Struct
{
	/*00*/	char			SerializedItem[1];
	/*xx*/
};

struct Consume_Struct
{
	/*0000*/ uint32_t	slot;
	/*0004*/ uint32_t	auto_consumed; // 0xffffffff when auto eating e7030000 when right click
	/*0008*/ uint8_t	c_unknown1[4];
	/*0012*/ uint8_t	type; // 0x01=Food 0x02=Water
	/*0013*/ uint8_t	unknown13[3];
};

struct DeleteItem_Struct
{
	/*0000*/ uint32_t	from_slot;
	/*0004*/ uint32_t	to_slot;
	/*0008*/ uint32_t	number_in_stack;
	/*0012*/
};

struct MoveItem_Struct
{
	/*0000*/ uint32_t	from_slot;
	/*0004*/ uint32_t	to_slot;
	/*0008*/ uint32_t	number_in_stack;
	/*0012*/
};

//
// from_slot/to_slot
// -1 - destroy
//  0 - cursor
//  1 - inventory
//  2 - bank
//  3 - trade
//  4 - shared bank
//
// cointype
// 0 - copeer
// 1 - silver
// 2 - gold
// 3 - platinum
//
static const uint32_t COINTYPE_PP = 3;
static const uint32_t COINTYPE_GP = 2;
static const uint32_t COINTYPE_SP = 1;
static const uint32_t COINTYPE_CP = 0;

struct MoveCoin_Struct
{
	int32_t from_slot;
	int32_t to_slot;
	int32_t cointype1;
	int32_t cointype2;
	int32_t	amount;
};
struct TradeCoin_Struct{
	uint32_t	trader;
	uint8_t	slot;
	uint16_t	unknown5;
	uint8_t	unknown7;
	uint32_t	amount;
};
struct TradeMoneyUpdate_Struct{
	uint32_t	trader;
	uint32_t	type;
	uint32_t	amount;
};
/*
** Surname struct
** Size: 100 bytes
*/
struct Surname_Struct
{
	/*0000*/	char name[64];
	/*0064*/	uint32_t unknown0064;
	/*0068*/	char lastname[32];
	/*0100*/
};

struct GuildsListEntry_Struct {
	char name[64];
};

/*
static const uint32_t MAX_NUMBER_GUILDS = 1500;
struct GuildsList_Struct {
	uint8_t head[64]; // First on guild list seems to be empty...
	GuildsListEntry_Struct Guilds[MAX_NUMBER_GUILDS];
};
*/

struct GuildUpdate_Struct {
	uint32_t	guildID;
	GuildsListEntry_Struct entry;
};

/*
** Money Loot
** Length: 22 Bytes
** OpCode: 5020
*/
struct moneyOnCorpseStruct {
	/*0000*/ uint8_t	response;		// 0 = someone else is, 1 = OK, 2 = not at this time
	/*0001*/ uint8_t	unknown1;		// = 0x5a
	/*0002*/ uint8_t	unknown2;		// = 0x40
	/*0003*/ uint8_t	unknown3;		// = 0
	/*0004*/ uint32_t	platinum;		// Platinum Pieces
	/*0008*/ uint32_t	gold;			// Gold Pieces

	/*0012*/ uint32_t	silver;			// Silver Pieces
	/*0016*/ uint32_t	copper;			// Copper Pieces
};

//opcode = 0x5220
// size 292


struct LootingItem_Struct {
	/*000*/	uint32_t	lootee;
	/*002*/	uint32_t	looter;
	/*004*/	uint16_t	slot_id;
	/*006*/	uint8_t	unknown3[2];
	/*008*/	uint32_t	auto_loot;
};

struct GuildManageStatus_Struct{
	uint32_t	guildid;
	uint32_t	oldrank;
	uint32_t	newrank;
	char	name[64];
};
// Guild invite, remove
struct GuildJoin_Struct{
	/*000*/	uint32_t	guildid;
	/*004*/	uint32_t	unknown04;
	/*008*/	uint32_t	level;
	/*012*/	uint32_t	class_;
	/*016*/	uint32_t	rank;//0 member, 1 officer, 2 leader
	/*020*/	uint32_t	zoneid;
	/*024*/	uint32_t	unknown24;
	/*028*/	char	name[64];
	/*092*/
};
struct GuildInviteAccept_Struct {
	char inviter[64];
	char newmember[64];
	uint32_t response;
	uint32_t guildeqid;
};
struct GuildManageRemove_Struct {
	uint32_t guildeqid;
	char member[64];
};
struct GuildCommand_Struct {
	char othername[64];
	char myname[64];
	uint16_t guildeqid;
	uint8_t unknown[2]; // for guildinvite all 0's, for remove 0=0x56, 2=0x02
	uint32_t officer;
};

// 4244 bytes. Is not really an 'OnLevelMessage', it causes a popup box to display in the client
// Text looks like HTML.
struct OnLevelMessage_Struct {
	/*0000*/       char    Title[128];
	/*0128*/       char    Text[4096];
	/*4224*/       uint32_t  Buttons;
	/*4228*/       uint32_t  Duration;
	/*4232*/       uint32_t  PopupID;
	/*4236*/       uint32_t  unknown4236;
	/*4240*/       uint32_t  unknown4240;
	/*4244*/
};

// Opcode OP_GMZoneRequest
// Size = 88 bytes
struct GMZoneRequest_Struct {
	/*0000*/	char	charname[64];
	/*0064*/	uint32_t	zone_id;
	/*0068*/	float	x;
	/*0072*/	float	y;
	/*0076*/	float	z;
	/*0080*/	char	unknown0080[4];
	/*0084*/	uint32_t	success;		// 0 if command failed, 1 if succeeded?
	/*0088*/
	//	/*072*/	int8_t	success;		// =0 client->server, =1 server->client, -X=specific error
	//	/*073*/	uint8_t	unknown0073[3]; // =0 ok, =ffffff error
};

struct GMSummon_Struct {
	/*  0*/	char    charname[64];
	/* 30*/	char    gmname[64];
	/* 60*/ uint32_t	success;
	/* 61*/	uint32_t	zoneID;
	/*92*/	int32_t  y;
	/*96*/	int32_t  x;
	/*100*/ int32_t  z;
	/*104*/	uint32_t unknown2; // E0 E0 56 00
};

struct GMGoto_Struct { // x,y is swapped as compared to summon and makes sense as own packet
	/*  0*/	char    charname[64];

	/* 64*/	char    gmname[64];
	/* 128*/ uint32_t	success;
	/* 132*/	uint32_t	zoneID;

	/*136*/	int32_t  y;
	/*140*/	int32_t  x;
	/*144*/ int32_t  z;
	/*148*/	uint32_t unknown2; // E0 E0 56 00
};

struct GMLastName_Struct {
	char name[64];
	char gmname[64];
	char lastname[64];
	uint16_t unknown[4];	// 0x00, 0x00
	// 0x01, 0x00 = Update the clients
};

//Combat Abilities
struct CombatAbility_Struct {
	uint32_t m_target;		//the ID of the target mob
	uint32_t m_atk;
	uint32_t m_skill;
};

//Instill Doubt
struct Instill_Doubt_Struct {
	uint8_t i_id;
	uint8_t ia_unknown;
	uint8_t ib_unknown;
	uint8_t ic_unknown;
	uint8_t i_atk;

	uint8_t id_unknown;
	uint8_t ie_unknown;
	uint8_t if_unknown;
	uint8_t i_type;
	uint8_t ig_unknown;
	uint8_t ih_unknown;
	uint8_t ii_unknown;
};

struct GiveItem_Struct {
	uint16_t to_entity;
	int16_t to_equipSlot;
	uint16_t from_entity;
	int16_t from_equipSlot;
};

struct RandomReq_Struct {
	uint32_t low;
	uint32_t high;
};

/* solar: 9/23/03 reply to /random command; struct from Zaphod */
struct RandomReply_Struct {
	/* 00 */	uint32_t low;
	/* 04 */	uint32_t high;
	/* 08 */	uint32_t result;
	/* 12 */	char name[64];
	/* 76 */
};

struct LFG_Struct {
	/*
	Wrong size on OP_LFG. Got: 80, Expected: 68
	0: 00 00 00 00 01 00 00 00 - 00 00 00 00 64 00 00 00  | ............d...
	16: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	32: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	48: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	64: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	Wrong size on OP_LFG. Got: 80, Expected: 68
	0: 00 00 00 00 01 00 00 00 - 3F 00 00 00 41 00 00 00  | ........?...A...
	16: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	32: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	48: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	64: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	Wrong size on OP_LFG. Got: 80, Expected: 68
	0: 00 00 00 00 01 00 00 00 - 3F 00 00 00 41 00 00 00  | ........?...A...
	16: 46 72 75 62 20 66 72 75 - 62 20 66 72 75 62 00 00  | Frub frub frub..
	32: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	48: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	64: 00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00  | ................
	*/
	/*000*/	uint32_t unknown000;
	/*004*/	uint32_t value; // 0x00 = off 0x01 = on
	/*008*/	uint32_t unknown008;
	/*012*/	uint32_t unknown012;
	/*016*/	char	name[64];
};

/*
** LFG_Appearance_Struct
** Packet sent to clients to notify when someone in zone toggles LFG flag
** Size: 8 bytes
** Used in: OP_LFGAppearance
**
*/
struct LFG_Appearance_Struct
{
	/*0000*/ uint32_t spawn_id;		// ID of the client
	/*0004*/ uint8_t lfg;				// 1=LFG, 0=Not LFG
	/*0005*/ char unknown0005[3];	//
	/*0008*/
};


// EverQuest Time Information:
// 72 minutes per EQ Day
// 3 minutes per EQ Hour
// 6 seconds per EQ Tick (2 minutes EQ Time)
// 3 seconds per EQ Minute

struct TimeOfDay_Struct {
	uint8_t	hour;
	uint8_t	minute;
	uint8_t	day;
	uint8_t	month;
	uint32_t	year;
};

// Darvik: shopkeeper structs
struct Merchant_Click_Struct {
	/*000*/ uint32_t	npcid;			// Merchant NPC's entity id
	/*004*/ uint32_t	playerid;
	/*008*/ uint32_t	command;		//1=open, 0=cancel/close
	/*012*/ float	rate;			//cost multiplier, dosent work anymore
};
/*
Unknowns:
0 is e7 from 01 to // MAYBE SLOT IN PURCHASE
1 is 03
2 is 00
3 is 00
4 is ??
5 is ??
6 is 00 from a0 to
7 is 00 from 3f to */
/*
0 is F6 to 01
1 is CE CE
4A 4A
00 00
00 E0
00 CB
00 90
00 3F
*/



struct Merchant_Sell_Struct {
	/*000*/	uint32_t	npcid;			// Merchant NPC's entity id
	/*004*/	uint32_t	playerid;		// Player's entity id
	/*008*/	uint32_t	itemslot;
	uint32_t	unknown12;
	/*016*/	uint8_t	quantity;		// Already sold
	/*017*/ uint8_t	Unknown016[3];
	/*020*/ uint32_t	price;
};
struct Merchant_Purchase_Struct {
	/*000*/	uint32_t	npcid;			// Merchant NPC's entity id
	/*004*/	uint32_t	itemslot;		// Player's entity id
	/*008*/	uint32_t	quantity;
	/*012*/	uint32_t	price;
};
struct Merchant_DelItem_Struct{
	/*000*/	uint32_t	npcid;			// Merchant NPC's entity id
	/*004*/	uint32_t	playerid;		// Player's entity id
	/*008*/	uint32_t	itemslot;
};
struct Adventure_Purchase_Struct {
	/*000*/	uint32_t	some_flag;	//set to 1 generally...
	/*000*/	uint32_t	npcid;
	/*004*/	uint32_t	itemid;
	/*008*/	uint32_t	variable;
};

struct Adventure_Sell_Struct {
	/*000*/	uint32_t	unknown000;	//0x01
	/*004*/	uint32_t	npcid;
	/*008*/	uint32_t	slot;
	/*012*/	uint32_t	charges;
	/*016*/	uint32_t	sell_price;
};

struct AdventurePoints_Update_Struct {
	/*000*/	uint32_t				ldon_available_points;		// Total available points
	/*004*/ uint8_t				unkown_apu004[20];
	/*024*/	uint32_t				ldon_guk_points;		// Earned Deepest Guk points
	/*028*/	uint32_t				ldon_mirugal_points;		// Earned Mirugal' Mebagerie points
	/*032*/	uint32_t				ldon_mistmoore_points;		// Earned Mismoore Catacombs Points
	/*036*/	uint32_t				ldon_rujarkian_points;		// Earned Rujarkian Hills points
	/*040*/	uint32_t				ldon_takish_points;		// Earned Takish points
	/*044*/	uint8_t				unknown_apu042[216];
};


struct AdventureFinish_Struct{
	uint32_t win_lose;//Cofruben: 00 is a lose,01 is win.
	uint32_t points;
};
//OP_AdventureRequest
struct AdventureRequest_Struct{
	uint32_t risk;//1 normal,2 hard.
	uint32_t entity_id;
};
struct AdventureRequestResponse_Struct{
	uint32_t unknown000;
	char text[2048];
	uint32_t timetoenter;
	uint32_t timeleft;
	uint32_t risk;
	float x;
	float y;
	float z;
	uint32_t showcompass;
	uint32_t unknown2080;
};



/*struct Item_Shop_Struct {
uint16_t merchantid;
uint8_t itemtype;
Item_Struct item;
uint8_t iss_unknown001[6];
};*/

struct Illusion_Struct {
	/*000*/	uint32_t	spawnid;
	/*004*/	char	charname[64];
	/*068*/	uint16_t	race;
	/*070*/	char	unknown070[2];
	/*072*/	uint8_t	gender;
	/*073*/	uint8_t	texture;
	/*074*/	uint8_t	helmtexture;
	/*075*/	uint8_t	unknown075;
	/*076*/	uint32_t	face;
	/*080*/	uint8_t	hairstyle;
	/*081*/	uint8_t	haircolor;
	/*082*/	uint8_t	beard;
	/*083*/	uint8_t	beardcolor;
	/*084*/	float	size;
	/*088*/	char	unknown084[80];
	/*168*/
};

struct ZonePoint_Entry {
	/*0000*/	uint32_t	iterator;
	/*0004*/	float	y;
	/*0008*/	float	x;
	/*0012*/	float	z;
	/*0016*/	float	heading;
	/*0020*/	uint16_t	zoneid;
	/*0022*/	uint16_t	zoneinstance; // LDoN instance
};

struct ZonePoints {
	/*0000*/	uint32_t	count;
	/*0004*/	struct	ZonePoint_Entry zpe[1]; // Always add one extra to the end after all zonepoints
};

struct SkillUpdate_Struct {
	/*00*/	uint32_t skillId;
	/*04*/	uint32_t value;
	/*08*/
};

struct ZoneUnavail_Struct {
	//This actually varies, but...
	char zonename[16];
	int16_t unknown[4];
};

struct GroupGeneric_Struct {
	char name1[64];
	char name2[64];
};

struct GroupCancel_Struct {
	char	name1[64];
	char	name2[64];
	uint8_t	toggle;
};

struct GroupUpdate_Struct {
	/*0000*/	uint32_t	action;
	/*0004*/	char	yourname[64];
	/*0068*/	char	membername[5][64];
	/*0388*/	char	leadersname[64];
};

struct GroupUpdate2_Struct {
	/*0000*/	uint32_t	action;
	/*0004*/	char	yourname[64];
	/*0068*/	char	membername[5][64];
	/*0388*/	char	leadersname[64];
	/*0452*/	GroupLeadershipAA_Struct leader_aas;
	/*0580*/	uint8_t	unknown[188];
	/*0768*/
};
struct GroupJoin_Struct {
	/*0000*/	uint32_t	action;
	/*0004*/	char	yourname[64];
	/*0068*/	char	membername[64];
	/*0132*/	uint8_t	unknown[84];
};

struct FaceChange_Struct {
	/*000*/	uint8_t	haircolor;
	/*001*/	uint8_t	beardcolor;
	/*002*/	uint8_t	eyecolor1; // the eyecolors always seem to be the same, maybe left and right eye?
	/*003*/	uint8_t	eyecolor2;
	/*004*/	uint8_t	hairstyle;
	/*005*/	uint8_t	beard;	// vesuvias
	/*006*/	uint8_t	face;
	//vesuvias:
	//there are only 10 faces for barbs changing woad just
	//increase the face value by ten so if there were 8 woad
	//designs then there would be 80 barb faces
};

/*
** Trade request from one client to another
** Used to initiate a trade
** Size: 8 bytes
** Used in: OP_TradeRequest
*/
struct TradeRequest_Struct {
	/*00*/	uint32_t to_mob_id;
	/*04*/	uint32_t from_mob_id;
	/*08*/
};

struct TradeAccept_Struct {
	/*00*/	uint32_t from_mob_id;
	/*04*/	uint32_t unknown4;		//seems to be garbage
	/*08*/
};

/*
** Cancel Trade struct
** Sent when a player cancels a trade
** Size: 8 bytes
** Used In: OP_CancelTrade
**
*/
struct CancelTrade_Struct {
	/*00*/	uint32_t fromid;
	/*04*/	uint32_t action;
	/*08*/
};

struct PetitionUpdate_Struct {
	uint32_t petnumber;    // Petition Number
	uint32_t color;		// 0x00 = green, 0x01 = yellow, 0x02 = red
	uint32_t status;
	time_t senttime;    // 4 has to be 0x1F
	char accountid[32];
	char gmsenttoo[64];
	int32_t quetotal;
	char charname[64];
};

struct Petition_Struct {
	uint32_t petnumber;
	uint32_t urgency;
	char accountid[32];
	char lastgm[32];
	uint32_t	zone;
	//char zone[32];
	char charname[64];
	uint32_t charlevel;
	uint32_t charclass;
	uint32_t charrace;
	uint32_t unknown;
	//time_t senttime; // Time?
	uint32_t checkouts;
	uint32_t unavail;
	//uint8_t unknown5[4];
	time_t senttime;
	uint32_t unknown2;
	char petitiontext[1024];
	char gmtext[1024];
};


struct Who_All_Struct { // 76 length total
	/*000*/	char	whom[64];
	/*064*/	uint32_t	wrace;		// FF FF = no race

	/*066*/	uint32_t	wclass;		// FF FF = no class
	/*068*/	uint32_t	lvllow;		// FF FF = no numbers
	/*070*/	uint32_t	lvlhigh;	// FF FF = no numbers
	/*072*/	uint32_t	gmlookup;	// FF FF = not doing /who all gm
	/*074*/	uint32_t	unknown074;
	/*076*/	uint8_t	unknown076[64];
	/*140*/
};

struct Stun_Struct { // 4 bytes total
	uint32_t duration; // Duration of stun
};

struct AugmentItem_Struct {
	/*00*/	int16_t	container_slot;
	/*02*/	char	unknown02[2];
	/*04*/	int32_t	augment_slot;
	/*08*/
};

// OP_Emote
struct Emote_Struct {
	/*0000*/	uint32_t unknown01;
	/*0004*/	char message[1024];
	/*1028*/
};

// Inspect
struct Inspect_Struct {
	uint32_t TargetID;
	uint32_t PlayerID;
};
//OP_InspectAnswer
struct InspectResponse_Struct{//Cofruben:need to send two of this for the inspect response.
	/*000*/	uint32_t TargetID;
	/*004*/	uint32_t playerid;
	/*008*/	char itemnames[22][64];
	/*1416*/uint32_t itemicons[22];
	/*1504*/char text[288];
	/*1792*/
};

//OP_SetDataRate
struct SetDataRate_Struct {
	float newdatarate;
};

//OP_SetServerFilter
struct SetServerFilter_Struct {
	uint32_t filters[29];		//see enum eqFilterType
};

//Op_SetServerFilterAck
struct SetServerFilterAck_Struct {
	uint8_t blank[8];
};
struct IncreaseStat_Struct{
	/*0000*/	uint8_t	unknown0;
	/*0001*/	uint8_t	str;
	/*0002*/	uint8_t	sta;
	/*0003*/	uint8_t	agi;
	/*0004*/	uint8_t	dex;
	/*0005*/	uint8_t	int_;
	/*0006*/	uint8_t	wis;
	/*0007*/	uint8_t	cha;
	/*0008*/	uint8_t	fire;
	/*0009*/	uint8_t	cold;
	/*0010*/	uint8_t	magic;
	/*0011*/	uint8_t	poison;
	/*0012*/	uint8_t	disease;
	/*0013*/	char	unknown13[116];
	/*0129*/	uint8_t	str2;
	/*0130*/	uint8_t	sta2;
	/*0131*/	uint8_t	agi2;
	/*0132*/	uint8_t	dex2;
	/*0133*/	uint8_t	int_2;
	/*0134*/	uint8_t	wis2;
	/*0135*/	uint8_t	cha2;
	/*0136*/	uint8_t	fire2;
	/*0137*/	uint8_t	cold2;
	/*0138*/	uint8_t	magic2;
	/*0139*/	uint8_t	poison2;
	/*0140*/	uint8_t	disease2;
};

struct GMName_Struct {
	char oldname[64];
	char gmname[64];
	char newname[64];
	uint8_t badname;
	uint8_t unknown[3];
};

struct GMDelCorpse_Struct {
	char corpsename[64];
	char gmname[64];
	uint8_t unknown;
};

struct GMKick_Struct {
	char name[64];
	char gmname[64];
	uint8_t unknown;
};


struct GMKill_Struct {
	char name[64];
	char gmname[64];
	uint8_t unknown;
};


struct GMEmoteZone_Struct {
	char text[512];
};

// This is where the Text is sent to the client.
// Use ` as a newline character in the text.
// Variable length.
struct BookText_Struct {
	uint8_t window;	// where to display the text (0xFF means new window)
	uint8_t type;             //type: 0=scroll, 1=book, 2=item info.. prolly others.
	char booktext[1]; // Variable Length
};
// This is the request to read a book.
// This is just a "text file" on the server
// or in our case, the 'name' column in our books table.
struct BookRequest_Struct {
	uint8_t window;	// where to display the text (0xFF means new window)
	uint8_t type;             //type: 0=scroll, 1=book, 2=item info.. prolly others.
	char txtfile[1];	// Variable length
};

/*
** Object/Ground Spawn struct
** Used for Forges, Ovens, ground spawns, items dropped to ground, etc
** Size: 92 bytes
** OpCodes: OP_CreateObject
** Last Updated: Oct-17-2003
**
*/
struct Object_Struct {
	/*00*/	uint32_t	linked_list_addr[2];// <Zaphod> They are, get this, prev and next, ala linked list
	/*08*/	uint16_t	unknown008[2];		//
	/*12*/	uint32_t	drop_id;			// Unique object id for zone
	/*16*/	uint16_t	zone_id;			// Redudant, but: Zone the object appears in
	/*18*/	uint16_t	zone_instance;		//
	/*20*/	uint32_t	unknown020;			//
	/*24*/	uint32_t	unknown024;			//
	/*28*/	float	heading;			// heading
	/*32*/	float	z;					// z coord
	/*36*/	float	x;					// x coord
	/*40*/	float	y;					// y coord
	/*44*/	char	object_name[32];	// Name of object, usually something like IT63_ACTORDEF
	/*76*/	uint32_t	unknown076;			//
	// ShowEQ shows an extra field in here...
	/*80*/	uint32_t	object_type;		// Type of object, not directly translated to OP_OpenObject
	/*84*/	uint32_t	unknown084;			//set to 0xFF
	/*88*/	uint32_t	spawn_id;			// Spawn Id of client interacting with object
	/*92*/
};
//<Zaphod> 01 = generic drop, 02 = armor, 19 = weapon
//[13:40] <Zaphod> and 0xff seems to be indicative of the tradeskill/openable items that end up returning the old style item type in the OP_OpenObject

/*
** Click Object Struct
** Client clicking on zone object (forge, groundspawn, etc)
** Size: 8 bytes
** Last Updated: Oct-17-2003
**
*/
struct ClickObject_Struct {
	/*00*/	uint32_t drop_id;
	/*04*/	uint32_t player_id;
	/*08*/
};

struct Shielding_Struct {
	uint32_t target_id;
};

/*
** Click Object Acknowledgement Struct
** Response to client clicking on a World Container (ie, forge)
**
*/
struct ClickObjectAck_Struct {
	/*00*/	uint32_t	player_id;	// Entity Id of player who clicked object
	/*04*/	uint32_t	drop_id;	// Zone-specified unique object identifier
	/*08*/	uint32_t	open;		// 1=opening, 0=closing
	/*12*/	uint32_t	type;		// See object.h, "Object Types"
	/*16*/	uint32_t	unknown16;	//
	/*20*/	uint32_t	icon;		// Icon to display for tradeskill containers
	/*24*/	uint32_t	unknown24;	//
	/*28*/	char	object_name[64]; // Object name to display
	/*92*/
};

/*
** This is different now, mostly unknown
**
*/
struct CloseContainer_Struct {
	/*00*/	uint32_t	player_id;	// Entity Id of player who clicked object
	/*04*/	uint32_t	drop_id;	// Zone-specified unique object identifier
	/*08*/	uint32_t	open;		// 1=opening, 0=closing
	/*12*/	uint32_t	unknown12[12];
};

/*
** Generic Door Struct
** Length: 52 Octets
** Used in:
**    cDoorSpawnsStruct(f721)
**
*/
struct Door_Struct
{
	/*0000*/ char    name[32];            // Filename of Door // Was 10char long before... added the 6 in the next unknown to it: Daeken M. BlackBlade
	/*0032*/ float   yPos;               // y loc
	/*0036*/ float   xPos;               // x loc
	/*0040*/ float   zPos;               // z loc
	/*0044*/ float	 heading;
	/*0048*/ uint32_t   incline;	// rotates the whole door
	/*0052*/ uint16_t   size;			// 100 is normal, smaller number = smaller model
	/*0054*/ uint8_t    unknown0038[6];
	/*0060*/ uint8_t   doorId;             // door's id #
	/*0061*/ uint8_t   opentype;
	/*
	*  Open types:
	* 66 = PORT1414 (Qeynos)
	* 55 = BBBOARD (Qeynos)
	* 100 = QEYLAMP (Qeynos)
	* 56 = CHEST1 (Qeynos)
	* 5 = DOOR1 (Qeynos)
	*/
	/*0062*/ uint8_t  state_at_spawn;
	/*0063*/ uint8_t  invert_state;	// if this is 1, the door is normally open
	/*0064*/ uint32_t  door_param;
	/*0068*/ uint8_t  unknown0052[12]; // mostly 0s, the last 3 bytes are something tho
	/*0080*/
};



struct DoorSpawns_Struct {
	struct Door_Struct doors[1];
};

/*
OP Code: 	Op_ClickDoor
Size:		16
*/
struct ClickDoor_Struct {
	/*000*/	uint8_t	doorid;
	/*001*/	uint8_t	unknown001;		// This may be some type of action setting
	/*002*/	uint8_t	unknown002;		// This is sometimes set after a lever is closed
	/*003*/	uint8_t	unknown003;		// Seen 0
	/*004*/	uint8_t	picklockskill;
	/*005*/	uint8_t	unknown005[3];
	/*008*/ uint32_t	item_id;
	/*012*/ uint16_t	player_id;
	/*014*/ uint8_t	unknown014[2];
	/*016*/
};

struct MoveDoor_Struct {
	uint8_t	doorid;
	uint8_t	action;
};


struct BecomeNPC_Struct {
	uint32_t id;
	int32_t maxlevel;
};

struct Underworld_Struct {
	float speed;
	float y;
	float x;
	float z;
};

struct Resurrect_Struct	{
	uint32_t	unknown00;
	uint16_t	zone_id;
	uint16_t	instance_id;
	float	y;
	float	x;
	float	z;
	char	your_name[64];
	uint32_t	unknown88;
	char	rezzer_name[64];
	uint32_t	spellid;
	char	corpse_name[64];
	uint32_t	action;
	/* 228 */
};

struct SetRunMode_Struct {
	uint8_t mode;
	uint8_t unknown[3];
};

//EnvDamage is EnvDamage2 without a few bytes at the end.

struct EnvDamage2_Struct {
	/*0000*/	uint32_t id;
	/*0004*/	uint16_t unknown4;
	/*0006*/	uint32_t damage;
	/*0010*/	uint8_t unknown10[12];
	/*0022*/	uint8_t dmgtype; //FA = Lava; FC = Falling
	/*0023*/	uint8_t unknown2[4];
	/*0027*/	uint16_t constant; //Always FFFF
	/*0029*/	uint16_t unknown29;
};

//Bazaar Stuff =D

struct BazaarWindowStart_Struct {
	uint8_t   Action;
	uint8_t   Unknown001;
	uint16_t  Unknown002;
};


struct BazaarWelcome_Struct {
	BazaarWindowStart_Struct beginning;
	uint32_t  traders;
	uint32_t  items;
	uint8_t   unknown1[8];
};

struct BazaarSearch_Struct {
	BazaarWindowStart_Struct beginning;
	uint32_t	traderid;
	uint32_t  class_;
	uint32_t  race;
	uint32_t  stat;
	uint32_t  slot;
	uint32_t  type;
	char   name[64];
	uint32_t	minprice;
	uint32_t	maxprice;
	uint32_t	minlevel;
	uint32_t	maxlevel;
};
struct BazaarInspect_Struct{
	uint32_t item_id;
	uint32_t unknown;
	char name[64];
};
struct BazaarReturnDone_Struct{
	uint32_t type;
	uint32_t traderid;
	uint32_t unknown8;
	uint32_t unknown12;
	uint32_t unknown16;
};
struct BazaarSearchResults_Struct {
	BazaarWindowStart_Struct Beginning;
	uint32_t	SellerID;
	uint32_t   NumItems; // Don't know. Don't know the significance of this field.
	uint32_t   SerialNumber;
	uint32_t   Unknown016;
	uint32_t   Unknown020; // Something to do with stats as well
	char	ItemName[64];
	uint32_t	Cost;
	uint32_t	ItemStat;
};

struct ServerSideFilters_Struct {
	uint8_t	clientattackfilters; // 0) No, 1) All (players) but self, 2) All (players) but group
	uint8_t	npcattackfilters;	 // 0) No, 1) Ignore NPC misses (all), 2) Ignore NPC Misses + Attacks (all but self), 3) Ignores NPC Misses + Attacks (all but group)
	uint8_t	clientcastfilters;	 // 0) No, 1) Ignore PC Casts (all), 2) Ignore PC Casts (not directed towards self)
	uint8_t	npccastfilters;		 // 0) No, 1) Ignore NPC Casts (all), 2) Ignore NPC Casts (not directed towards self)
};

/*
** Client requesting item statistics
** Size: 44 bytes
** Used In: OP_ItemLinkClick
** Last Updated: 2/15/2009
**
*/
struct	ItemViewRequest_Struct {
	/*000*/	uint32_t	item_id;
	/*004*/	uint32_t	augments[5];
	/*024*/ uint32_t	link_hash;
	/*028*/	char	unknown028[16];
};

/*
*  Client to server packet
*/
struct PickPocket_Struct {
	// Size 18
	uint32_t to;
	uint32_t from;
	uint16_t myskill;
	uint8_t type; // -1 you are being picked, 0 failed , 1 = plat, 2 = gold, 3 = silver, 4 = copper, 5 = item
	uint8_t unknown1; // 0 for response, unknown for input
	uint32_t coin;
	uint8_t lastsix[2];
};
/*
* Server to client packet
*/

struct sPickPocket_Struct {
	// Size 28 = coin/fail
	uint32_t to;
	uint32_t from;
	uint32_t myskill;
	uint32_t type;
	uint32_t coin;
	char itemname[64];
};

struct LogServer_Struct {
	// Op_Code OP_LOGSERVER
	/*000*/	uint32_t	unknown000;
	/*004*/	uint32_t	unknown004;
	/*008*/	uint32_t	unknown008;
	/*012*/	uint32_t	unknown012;	// htonl(1) on live
	/*016*/	uint32_t	unknown016;	// htonl(1) on live
	/*020*/	uint8_t	unknown020[12];
	/*032*/	char	worldshortname[32];
	/*064*/	uint8_t	unknown064[32];
	/*096*/	char	unknown096[16];	// 'pacman' on live
	/*112*/	char	unknown112[16];	// '64.37,148,36' on live
	/*126*/	uint8_t	unknown128[48];
	/*176*/	uint32_t	unknown176;	// htonl(0x00002695)
	/*180*/	char	unknown180[80];	// 'eqdataexceptions@mail.station.sony.com' on live
	/*260*/	uint8_t	unknown260;	// 0x01 on live
	/*261*/	uint8_t	unknown261;	// 0x01 on live
	/*262*/	uint8_t	unknown262[2];
	/*264*/
};

struct ApproveWorld_Struct {
	// Size 544
	// Op_Code OP_ApproveWorld
	uint8_t unknown544[544];
};

struct ClientError_Struct
{
	/*00001*/	char	type;
	/*00001*/	char	unknown0001[69];
	/*00069*/	char	character_name[64];
	/*00134*/	char	unknown134[192];
	/*00133*/	char	message[31994];
	/*32136*/
};

struct MobHealth
{
	/*0000*/	uint8_t	hp; //health percent
	/*0001*/	uint16_t	id;//mobs id
};

struct Track_Struct {
	uint16_t entityid;
	uint16_t padding002;
	float distance;
};

struct Tracking_Struct {
	Track_Struct Entrys[1];
};

/*
** ZoneServerInfo_Struct
** Zone server information
** Size: 130 bytes
** Used In: OP_ZoneServerInfo
**
*/
struct ZoneServerInfo_Struct
{
	/*0000*/	char	ip[128];
	/*0128*/	uint16_t	port;
};

struct WhoAllPlayer{
	uint32_t	formatstring;
	uint32_t	pidstring;
	char*	name;
	uint32_t	rankstring;
	char*	guild;
	uint32_t	unknown80[2];
	uint32_t	zonestring;
	uint32_t	zone;
	uint32_t	class_;
	uint32_t	level;
	uint32_t	race;
	char*	account;
	uint32_t	unknown100;
};

struct WhoAllReturnStruct {
	uint32_t	id;
	uint32_t	playerineqstring;
	char	line[27];
	uint8_t	unknown35; //0A
	uint32_t	unknown36;//0s
	uint32_t	playersinzonestring;
	uint32_t	unknown44[2]; //0s
	uint32_t	unknown52;//1
	uint32_t	unknown56;//1
	uint32_t	playercount;//1
	struct WhoAllPlayer player[1];
};

struct Trader_Struct {
	uint32_t	code;
	uint32_t	itemid[160];
	uint32_t	unknown;
	uint32_t	itemcost[80];
};

struct ClickTrader_Struct {
	uint32_t	code;
	uint32_t	unknown[161];//damn soe this is totally pointless :/ but at least your finally using memset! Good job :) -LE
	uint32_t	itemcost[80];
};

struct GetItems_Struct{
	uint32_t	items[80];
};

struct BecomeTrader_Struct{
	uint32_t ID;
	uint32_t Code;
};

struct Trader_ShowItems_Struct{
	uint32_t code;
	uint32_t traderid;
	uint32_t unknown08[3];
};

struct TraderBuy_Struct {
	/*000*/ uint32_t   Action;
	/*004*/ uint32_t   Price;
	/*008*/ uint32_t   TraderID;
	/*012*/ char    ItemName[64];
	/*076*/ uint32_t   Unknown076;
	/*080*/ uint32_t   ItemID;
	/*084*/ uint32_t   AlreadySold;
	/*088*/ uint32_t   Quantity;
	/*092*/ uint32_t   Unknown092;
};


struct TraderItemUpdate_Struct{
	uint32_t unknown0;
	uint32_t traderid;
	uint8_t  fromslot;
	uint8_t  toslot; //7?
	uint16_t charges;
};

struct MoneyUpdate_Struct{
	int32_t platinum;
	int32_t gold;
	int32_t silver;
	int32_t copper;
};

struct TraderDelItem_Struct{
	uint32_t slotid;
	uint32_t quantity;
	uint32_t unknown;
};

struct TraderClick_Struct{
	uint32_t traderid;
	uint32_t unknown4[2];
	uint32_t approval;
};

struct FormattedMessage_Struct{
	uint32_t	unknown0;
	uint32_t	string_id;
	uint32_t	type;
	char	message[1];
};
struct SimpleMessage_Struct{
	uint32_t	string_id;
	uint32_t	color;
	uint32_t	unknown8;
};

struct GuildMemberEntry_Struct {
	char	name[1];					//variable length
	uint32_t	level;						//network byte order
	uint32_t	banker;						//1=yes, 0=no, network byte order
	uint32_t	class_;						//network byte order
	uint32_t	rank;						//network byte order
	uint32_t	time_last_on;				//network byte order
	uint32_t	tribute_enable;				//network byte order
	uint32_t	total_tribute;				//total guild tribute donated, network byte order
	uint32_t	last_tribute;				//unix timestamp
	uint32_t	unknown_one;		//unknown, set to one. (network byte order)
	char	public_note[1];				//variable length.
	uint16_t	zoneinstance;				//network byte order
	uint16_t	zone_id;					//network byte order
	/* 42 + strings */
};

struct GuildMembers_Struct {	//just for display purposes, this is not actually used in the message encoding.
	char	player_name[1];		//variable length.
	uint32_t	count;				//network byte order
	GuildMemberEntry_Struct member[1];
};

struct GuildMOTD_Struct{
	/*0000*/	uint32_t	unknown0;
	/*0004*/	char	name[64];
	/*0068*/	char	setby_name[64];
	/*0132*/	uint32_t	unknown132;
	/*0136*/	char	motd[512];
};
struct GuildUpdate_PublicNote{
	uint32_t	unknown0;
	char	name[64];
	char	target[64];
	char	note[100]; //we are cutting this off at 100, actually around 252
};
struct GuildDemoteStruct{
	char	name[64];
	char	target[64];
};
struct GuildRemoveStruct{
	char	target[64];
	char	name[64];
	uint32_t	unknown128;
	uint32_t	leaderstatus; //?
};
struct GuildMakeLeader{
	char	name[64];
	char	target[64];
};
struct BugStruct{
	/*0000*/	char	chartype[64];
	/*0064*/	char	name[96];
	/*0160*/	char	ui[128];
	/*0288*/	float	x;
	/*0292*/	float	y;
	/*0296*/	float	z;
	/*0300*/	float	heading;
	/*0304*/	uint32_t	unknown304;
	/*0308*/	uint32_t	type;
	/*0312*/	char	unknown312[2144];
	/*2456*/	char	bug[1024];
	/*3480*/	char	placeholder[2];
	/*3482*/	char	system_info[4098];
};
struct Make_Pet_Struct { //Simple struct for getting pet info
	uint8_t level;
	uint8_t class_;
	uint16_t race;
	uint8_t texture;
	uint8_t pettype;
	float size;
	uint8_t type;
	uint32_t min_dmg;
	uint32_t max_dmg;
};
struct Ground_Spawn{
	float max_x;
	float max_y;
	float min_x;
	float min_y;
	float max_z;
	float heading;
	char name[16];
	uint32_t item;
	uint32_t max_allowed;
	uint32_t respawntimer;
};
struct Ground_Spawns {
	struct Ground_Spawn spawn[50]; //Assigned max number to allow
};
struct PetitionBug_Struct{
	uint32_t	petition_number;
	uint32_t	unknown4;
	char	accountname[64];
	uint32_t	zoneid;
	char	name[64];
	uint32_t	level;
	uint32_t	class_;
	uint32_t	race;
	uint32_t	unknown152[3];
	uint32_t	time;
	uint32_t	unknown168;
	char	text[1028];
};

struct DyeStruct
{
	union
	{
		struct
		{
			struct Color_Struct head;
			struct Color_Struct chest;
			struct Color_Struct arms;
			struct Color_Struct wrists;
			struct Color_Struct hands;
			struct Color_Struct legs;
			struct Color_Struct feet;
			struct Color_Struct primary;	// you can't actually dye this
			struct Color_Struct secondary;	// or this
		}
		dyes;
		struct Color_Struct dye[9];
	};
};

struct ApproveZone_Struct {
	char	name[64];
	uint32_t	zoneid;
	uint32_t	approve;
};
struct ZoneInSendName_Struct {
	uint32_t	unknown0;
	char	name[64];
	char	name2[64];
	uint32_t	unknown132;
};
struct ZoneInSendName_Struct2 {
	uint32_t	unknown0;
	char	name[64];
	uint32_t	unknown68[145];
};

static const uint32_t MAX_TRIBUTE_TIERS = 10;

struct StartTribute_Struct {
	uint32_t	client_id;
	uint32_t	tribute_master_id;
	uint32_t	response;
};

struct TributeLevel_Struct {
	uint32_t	level;	//backwards byte order!
	uint32_t	tribute_item_id;	//backwards byte order!
	uint32_t	cost;	//backwards byte order!
};

struct TributeAbility_Struct {
	uint32_t	tribute_id;	//backwards byte order!
	uint32_t	tier_count;	//backwards byte order!
	TributeLevel_Struct tiers[MAX_TRIBUTE_TIERS];
	char	name[1];
};

struct GuildTributeAbility_Struct {
	uint32_t	guild_id;
	TributeAbility_Struct ability;
};

struct SelectTributeReq_Struct {
	uint32_t	client_id;	//? maybe action ID?
	uint32_t	tribute_id;
	uint32_t	unknown8;	//seen E3 00 00 00
};

struct SelectTributeReply_Struct {
	uint32_t	client_id;	//echoed from request.
	uint32_t	tribute_id;
	char	desc[1];
};

struct TributeInfo_Struct {
	uint32_t	active;		//0 == inactive, 1 == active
	uint32_t	tributes[MAX_PLAYER_TRIBUTES];	//-1 == NONE
	uint32_t	tiers[MAX_PLAYER_TRIBUTES];		//all 00's
	uint32_t	tribute_master_id;
};

struct TributeItem_Struct {
	uint32_t	slot;
	uint32_t	quantity;
	uint32_t	tribute_master_id;
	int32_t	tribute_points;
};

struct TributePoint_Struct {
	int32_t   tribute_points;
	uint32_t   unknown04;
	int32_t   career_tribute_points;
	uint32_t   unknown12;
};

struct TributeMoney_Struct {
	uint32_t   platinum;
	uint32_t   tribute_master_id;
	int32_t   tribute_points;
};


struct Split_Struct
{
	uint32_t	platinum;
	uint32_t	gold;
	uint32_t	silver;
	uint32_t	copper;
};


/*
** New Combine Struct
** Client requesting to perform a tradeskill combine
** Size: 4 bytes
** Used In: OP_TradeSkillCombine
** Last Updated: Oct-15-2003
**
*/
struct NewCombine_Struct {
	/*00*/	int16_t	container_slot;
	/*02*/	int16_t	guildtribute_slot;
	/*04*/
};


//client requesting favorite recipies
struct TradeskillFavorites_Struct {
	uint32_t object_type;
	uint32_t some_id;
	uint32_t favorite_recipes[500];
};

//search request
struct RecipesSearch_Struct {
	uint32_t object_type;	//same as in favorites
	uint32_t some_id;			//same as in favorites
	uint32_t mintrivial;
	uint32_t maxtrivial;
	char query[56];
	uint32_t unknown4;	//is set to 00 03 00 00
	uint32_t unknown5; //is set to 4C DD 12 00
	/*80*/
};

//one sent for each item, from server in reply to favorites or search
struct RecipeReply_Struct {
	uint32_t object_type;
	uint32_t some_id;	 //same as in favorites
	uint32_t component_count;
	uint32_t recipe_id;
	uint32_t trivial;
	char recipe_name[64];
	/*84*/
};

//received and sent back as an ACK with different reply_code
struct RecipeAutoCombine_Struct {
	uint32_t object_type;
	uint32_t some_id;
	uint32_t unknown1;		//echoed in reply
	uint32_t recipe_id;
	uint32_t reply_code;		// 93 64 e1 00 (junk) in request
	// 00 00 00 00 in successful reply
	// f5 ff ff ff in 'you dont have all the stuff' reply
};

struct LevelAppearance_Struct { //Sends a little graphic on level up
	uint32_t	spawn_id;
	uint32_t	parm1;
	uint32_t	value1a;
	uint32_t	value1b;
	uint32_t	parm2;
	uint32_t	value2a;
	uint32_t	value2b;
	uint32_t	parm3;
	uint32_t	value3a;
	uint32_t	value3b;
	uint32_t	parm4;
	uint32_t	value4a;
	uint32_t	value4b;
	uint32_t	parm5;
	uint32_t	value5a;
	uint32_t	value5b;
	/*64*/
};
struct MerchantList{
	uint32_t	id;
	uint32_t	slot;
	uint32_t	item;
};
struct TempMerchantList{
	uint32_t	npcid;
	uint32_t	slot;
	uint32_t	item;
	uint32_t	charges; //charges/quantity
	uint32_t	origslot;
};


struct FindPerson_Point {
	float y;
	float x;
	float z;
};

struct FindPersonRequest_Struct {
	uint32_t	npc_id;
	FindPerson_Point client_pos;
};

//variable length packet of points
struct FindPersonResult_Struct {
	FindPerson_Point dest;
	FindPerson_Point path[1];	//last element must be the same as dest
};

struct MobRename_Struct {
	/*000*/	char	old_name[64];
	/*064*/	char	old_name_again[64];	//not sure what the difference is
	/*128*/	char	new_name[64];
	/*192*/	uint32_t	unknown192;		//set to 0
	/*196*/	uint32_t	unknown196;		//set to 1
	/*200*/
};

struct PlayMP3_Struct {
	char filename[1];
};

//this is for custom title display in the skill window
struct TitleEntry_Struct {
	uint32_t	skill_id;
	uint32_t	skill_value;
	char	title[1];
};

struct Titles_Struct {
	uint32_t	title_count;
	TitleEntry_Struct titles[1];
};

//this is for title selection by the client
struct TitleListEntry_Struct {
	uint32_t	unknown0;	//title ID
	char prefix[1];		//variable length, null terminated
	char postfix[1];		//variable length, null terminated
};

struct TitleList_Struct {
	uint32_t title_count;
	TitleListEntry_Struct titles[1];	//list of title structs
	//uint32_t unknown_ending; seen 0x7265, 0
};

struct SetTitle_Struct {
	uint32_t	is_suffix;	//guessed: 0 = prefix, 1 = suffix
	uint32_t	title_id;
};

struct SetTitleReply_Struct {
	uint32_t	is_suffix;	//guessed: 0 = prefix, 1 = suffix
	char	title[32];
	uint32_t	entity_id;
};

struct TaskDescription_Struct {
	/*000*/	uint32_t	activity_count;		//not right.
	/*004*/	uint32_t	taskid;
	/*008*/	uint8_t	unk;
	/*009*/	uint32_t	id3;
	/*013*/	uint32_t	unknown13;
	/*017*/	char	name[1];	//variable length, 0 terminated
	/*018*/	uint32_t	unknown18;
	/*022*/	uint32_t	unknown22;
	/*026*/	char	desc[1];	//variable length, 0 terminated
	/*027*/	uint32_t	reward_count;   //not sure
	/*031*/	uint32_t	unknown31;
	/*035*/	uint32_t	unknown35;
	/*039*/	uint16_t	unknown39;
	/*041*/	char	reward_link[1];	//variable length, 0 terminated
	/*042*/	uint32_t	unknown43;  //maybe crystal count?
};

struct TaskMemberList_Struct {
	/*00*/  uint32_t  gopher_id;
	/*04*/  uint32_t  unknown04;
	/*08*/  uint32_t  member_count;   //1 less than the number of members
	/*12*/  char	list_pointer[1];
	/*	list is of the form:
	char member_name[1]	//null terminated string
	uint8_t   task_leader	//boolean flag
	*/
};


struct TaskActivity_Struct {
	/*000*/	uint32_t	activity_count;		//not right
	/*004*/	uint32_t	id3;
	/*008*/	uint32_t	taskid;
	/*012*/	uint32_t	activity_id;
	/*016*/	uint32_t	unknown016;
	/*020*/	uint32_t	activity_type;
	/*024*/	uint32_t	unknown024;
	/*028*/	uint32_t	unknown28;
	/*032*/	char mob_name[1];	//variable length, 0 terminated
	/*033*/	char item_name[1];	//variable length, 0 terminated
	/*034*/	uint32_t	goal_count;
	/*038*/	uint32_t	unknown38;	//0xFFFFFFFF
	/*042*/	uint32_t	unknown42;	//0xFFFFFFFF
	/*046*/	uint32_t	unknown46;  //saw 0x151,0x156
	/*050*/	uint32_t	unknown50;  //saw 0x404,0
	/*054*/	char activity_name[1];  //variable length, 0 terminated... commonly empty
	/*055*/	uint32_t	done_count;
	/*059*/	uint32_t	unknown59;	//=1 except on unknown and terminal activities?
	/*063*/
};

struct TaskHistoryEntry_Struct {
	uint32_t	task_id;
	char	name[1];
	uint32_t	completed_time;
};
struct TaskHistory_Struct {
	uint32_t completed_count;
	TaskHistoryEntry_Struct entries[1];
};

struct AcceptNewTask_Struct {
	uint32_t	task_id;		//set to 0 for 'decline'
	uint32_t	task_master_id;	//entity ID
};

//was all 0's from client, server replied with same op, all 0's
struct CancelTask_Struct {
	uint32_t unknown0;
	uint32_t unknown4;
};

struct AvaliableTask_Struct {
	uint32_t	task_index;		//no idea, seen 0x1
	uint32_t	task_master_id;	//entity ID
	uint32_t	task_id;
	uint32_t	unknown012;
	uint32_t	activity_count;	//not sure, seen 2
	char desc[1];	//variable length, 0 terminated
	uint32_t	reward_platinum;//not sure on these
	uint32_t	reward_gold;
	uint32_t	reward_silver;
	uint32_t	reward_copper;
	char some_name[1];	//variable length, 0 terminated
	uint8_t	unknown1;
	uint32_t	unknown2;	//0xFFFFFFFF
	uint32_t	unknown3;	//0xFFFFFFFF
	uint32_t	unknown4;	//seen 0x16
	uint8_t	unknown5;
};


struct BankerChange_Struct {
	uint32_t	platinum;
	uint32_t	gold;
	uint32_t	silver;
	uint32_t	copper;
	uint32_t	platinum_bank;
	uint32_t	gold_bank;
	uint32_t	silver_bank;
	uint32_t	copper_bank;
};

struct LeadershipExpUpdate_Struct {
	/*00*/	double	group_leadership_exp;
	/*08*/	uint32_t	group_leadership_points;
	/*12*/	uint32_t	Unknown12;
	/*16*/	double	raid_leadership_exp;
	/*24*/	uint32_t	raid_leadership_points;
};

struct UpdateLeadershipAA_Struct {
	/*00*/	uint32_t	ability_id;
	/*04*/	uint32_t	new_rank;
	/*08*/	uint32_t	pointsleft;
	/*12*/
};

/**
* Leadership AA update
* Length: 32 Octets
* OpCode: LeadExpUpdate
*/
struct leadExpUpdateStruct {
	/*0000*/ uint32_t unknown0000;          // All zeroes?
	/*0004*/ uint32_t group_leadership_exp;         // Group leadership exp value
	/*0008*/ uint32_t group_leadership_points;   // Unspent group points
	/*0012*/ uint32_t unknown0012;          // Type?
	/*0016*/ uint32_t unknown0016;          // All zeroes?
	/*0020*/ uint32_t raid_leadership_exp;          // Raid leadership exp value
	/*0024*/ uint32_t raid_leadership_points;    // Unspent raid points
	/*0028*/ uint32_t unknown0028;
};



struct RaidGeneral_Struct {
	/*00*/	uint32_t		action;	//=10
	/*04*/	char		player_name[64];	//should both be the player's name
	/*04*/	char		leader_name[64];
	/*132*/	uint32_t		parameter;
};

struct RaidAdd_Struct {
	/*000*/	uint32_t		action;	//=0
	/*004*/	char		player_name[64];	//should both be the player's name
	/*068*/	char		leader_name[64];
	/*132*/	uint8_t		_class;
	/*133*/	uint8_t		level;
	/*134*/	uint8_t		has_group;
	/*135*/	uint8_t		unknown135;	//seems to be 0x42 or 0
};

struct RaidCreate_Struct {
	/*00*/	uint32_t		action;	//=8
	/*04*/	char		leader_name[64];
	/*68*/	uint32_t		leader_id;
};

struct RaidMemberInfo_Struct {
	/*00*/	uint8_t		group_number;
	/*01*/	char		member_name[1];		//dyanmic length, null terminated '\0'
	/*00*/	uint8_t		unknown00;
	/*01*/	uint8_t		_class;
	/*02*/	uint8_t		level;
	/*03*/	uint8_t		is_raid_leader;
	/*04*/	uint8_t		is_group_leader;
	/*05*/	uint8_t		main_tank;		//not sure
	/*06*/	uint8_t		unknown06[5];	//prolly more flags
};

struct RaidDetails_Struct {
	/*000*/	uint32_t		action;	//=6,20
	/*004*/	char		leader_name[64];
	/*068*/	uint32_t		unknown68[4];
	/*084*/	LeadershipAA_Struct abilities;	//ranks in backwards byte order
	/*128*/	uint8_t		unknown128[142];
	/*354*/	uint32_t		leader_id;
};

struct RaidMembers_Struct {
	/*000*/	RaidDetails_Struct		details;
	/*358*/	uint32_t					member_count;		//including leader
	/*362*/	RaidMemberInfo_Struct	members[1];
	/*...*/	RaidMemberInfo_Struct	empty;	//seem to have an extra member with a 0 length name on the end
};

struct DynamicWall_Struct {
	/*00*/  char	name[32];
	/*32*/  float   y;
	/*36*/  float   x;
	/*40*/  float   z;
	/*44*/  uint32_t  something;
	/*48*/  uint32_t  unknown48;  //0
	/*52*/  uint32_t  one_hundred;	//0x64
	/*56*/  uint32_t  unknown56;  //0
	/*60*/  uint32_t  something2;
	/*64*/  int32_t  unknown64;  //-1
	/*68*/  uint32_t  unknown68;  //0
	/*72*/  uint32_t  unknown72;  //0
	/*76*/  uint32_t  unknown76;  //0x100
	/*80*/
};

enum {	//bandolier actions
	BandolierCreate = 0,
	BandolierRemove = 1,
	BandolierSet = 2
};

struct BandolierCreate_Struct {
	/*00*/	uint32_t	action;	//0 for create
	/*04*/	uint8_t	number;
	/*05*/	char	name[32];
	/*37*/	uint16_t	unknown37;	//seen 0x93FD
	/*39*/	uint8_t	unknown39;	//0
};

struct BandolierDelete_Struct {
	/*00*/	uint32_t	action;
	/*04*/	uint8_t	number;
	/*05*/	uint8_t	unknown05[35];
};

struct BandolierSet_Struct {
	/*00*/	uint32_t	action;
	/*04*/	uint8_t	number;
	/*05*/	uint8_t	unknown05[35];
};

struct Arrow_Struct {
	/*000*/	uint32_t	type;		//unsure on name, seems to be 0x1, dosent matter
	/*005*/	uint8_t	unknown004[12];
	/*016*/	float	src_y;
	/*020*/	float	src_x;
	/*024*/	float	src_z;
	/*028*/	uint8_t	unknown028[12];
	/*040*/	float	velocity;		//4 is normal, 20 is quite fast
	/*044*/	float	launch_angle;	//0-450ish, not sure the units, 140ish is straight
	/*048*/	float	tilt;		//on the order of 125
	/*052*/	uint8_t	unknown052[8];
	/*060*/	float	arc;
	/*064*/	uint8_t	unknown064[12];
	/*076*/	uint32_t	source_id;
	/*080*/ uint32_t	target_id;	//entity ID
	/*084*/	uint32_t	item_id;	//1 to about 150ish
	/*088*/	uint32_t	unknown088;	//seen 125, dosent seem to change anything..
	/*092*/ uint32_t	unknown092;	//seen 16, dosent seem to change anything
	/*096*/	uint8_t	unknown096[5];
	/*101*/	char	model_name[16];
	/*117*/	uint8_t	unknown117[19];
};

//made a bunch of trivial structs for stuff for opcode finder to use
struct Consent_Struct {
	char name[1];	//always at least a null
};

struct AdventureMerchant_Struct {
	uint32_t	unknown_flag;		//seems to be 1
	uint32_t	entity_id;
};

struct Save_Struct {
	uint8_t	unknown00[192];
};

struct GMToggle_Struct {
	uint8_t unknown0[64];
	uint32_t toggle;
};

struct GroupInvite_Struct {
	char invitee_name[64];
	char inviter_name[64];
	//	uint8_t	unknown128[65];
};

struct ColoredText_Struct {
	uint32_t color;
	char msg[1];
};

struct UseAA_Struct {
	uint32_t begin;
	uint32_t ability;
	uint32_t end;
};

struct AA_Ability {
	/*00*/	uint32_t skill_id;
	/*04*/	uint32_t base1;
	/*08*/	uint32_t base2;
	/*12*/	uint32_t slot;
};

struct SendAA_Struct {
	/*0000*/	uint32_t id;
	/*0004*/	uint32_t unknown004;		//set to 1.
	/*0008*/	uint32_t hotkey_sid;
	/*0012*/	uint32_t hotkey_sid2;
	/*0016*/	uint32_t title_sid;
	/*0020*/	uint32_t desc_sid;
	/*0024*/	uint32_t class_type;
	/*0028*/	uint32_t cost;
	/*0032*/	uint32_t seq;
	/*0036*/	uint32_t current_level; //1s, MQ2 calls this AARankRequired
	/*0040*/	uint32_t prereq_skill;		//is < 0, abs() is category #
	/*0044*/	uint32_t prereq_minpoints; //min points in the prereq
	/*0048*/	uint32_t type;
	/*0052*/	uint32_t spellid;
	/*0056*/	uint32_t spell_type;
	/*0060*/	uint32_t spell_refresh;
	/*0064*/	uint16_t classes;
	/*0066*/	uint16_t berserker; //seems to be 1 if its a berserker ability
	/*0068*/	uint32_t max_level;
	/*0072*/	uint32_t last_id;
	/*0076*/	uint32_t next_id;
	/*0080*/	uint32_t cost2;
	/*0084*/	uint32_t unknown80[2]; //0s
	/*0088*/	uint32_t total_abilities;
	/*0092*/	AA_Ability abilities[1];
};

struct AA_List {
	SendAA_Struct* aa[1];
};

struct AA_Action {
	/*00*/	uint32_t	action;
	/*04*/	uint32_t	ability;
	/*08*/	uint32_t	unknown08;
	/*12*/	uint32_t	exp_value;
};

struct AA_Skills {		//this should be removed and changed to AA_Array
	/*00*/	uint32_t	aa_skill;
	/*04*/	uint32_t	aa_value;
};

struct AAExpUpdate_Struct {
	/*00*/	uint32_t unknown00;	//seems to be a value from AA_Action.ability
	/*04*/	uint32_t aapoints_unspent;
	/*08*/	uint8_t aaxp_percent;	//% of exp that goes to AAs
	/*09*/	uint8_t unknown09[3];	//live dosent always zero these, so they arnt part of aaxp_percent
};


struct AltAdvStats_Struct {
	/*000*/  uint32_t experience;
	/*004*/  uint16_t unspent;
	/*006*/  uint16_t	unknown006;
	/*008*/  uint8_t	percentage;
	/*009*/  uint8_t	unknown009[3];
};

struct PlayerAA_Struct {
	AA_Skills aa_list[MAX_PP_AA_ARRAY];
};

struct AATable_Struct {
	AA_Skills aa_list[MAX_PP_AA_ARRAY];
};

struct Weather_Struct {
	uint32_t	val1;	//generall 0x000000FF
	uint32_t	type;	//0x31=rain, 0x02=snow(i think), 0 = normal
	uint32_t	mode;
};

struct ZoneInUnknown_Struct {
	uint32_t	val1;
	uint32_t	val2;
	uint32_t	val3;
};

struct MobHealth_Struct {
	uint16_t entity_id;
	uint8_t hp;
};

struct AnnoyingZoneUnknown_Struct {
	uint32_t	entity_id;
	uint32_t	value;		//always 4
};

struct ApplyPoison_Struct {
	uint32_t inventorySlot;
	uint32_t success;
};

struct GuildMemberUpdate_Struct {
	/*000*/	uint32_t guild_id;	//not sure
	/*004*/	char	member_name[64];
	/*068*/	uint16_t	zone_id;
	/*070*/	uint16_t	instance_id;
	/*072*/	uint32_t	unknown072;
};

struct VeteranRewardItem
{
	/*000*/	uint32_t item_id;
	/*004*/	char item_name[256];
};

struct VeteranReward
{
	/*000*/	uint32_t claim_id;
	/*004*/	VeteranRewardItem item;
};

struct ExpeditionExpireWarning
{
	/*000*/ uint32_t unknown000;
	/*004*/ uint32_t minutes_remaining;
};

struct ExpeditionInfo_Struct
{
	/*000*/ uint32_t clientid;
	/*004*/ uint32_t enabled_max;
	/*008*/ uint32_t max_players;
	/*012*/ char expedition_name[128];
	/*142*/ char leader_name[64];
};

struct ExpeditionCompassEntry_Struct
{
	/*000*/ float unknown000; //seen *((uint32_t*)) = 1584791871
	/*004*/ uint32_t enabled; //guess
	/*008*/ uint32_t unknown008; //seen 1019
	/*012*/ float y;
	/*016*/ float x;
	/*020*/ float z;
};

struct ExpeditionCompass_Struct
{
	/*000*/ uint32_t clientid;
	/*004*/ uint32_t count;
	/*008*/ ExpeditionCompassEntry_Struct entries[1];
};

struct ExpeditionJoinPrompt_Struct
{
	/*000*/ uint32_t clientid;
	/*004*/ char player_name[64];
	/*068*/ char expedition_name[64];
};

struct LFGuild_SearchPlayer_Struct
{
	/*00*/	uint32_t	Command;
	/*04*/	uint32_t	Unknown04;
	/*08*/	uint32_t	FromLevel;
	/*12*/	uint32_t	ToLevel;
	/*16*/	uint32_t	MinAA;
	/*20*/	uint32_t	TimeZone;
	/*24*/	uint32_t	Classes;
};

struct LFGuild_SearchGuild_Struct
{
	/*00*/	uint32_t	Command;
	/*04*/	uint32_t	Unknown04;
	/*08*/	uint32_t	Level;
	/*12*/	uint32_t	AAPoints;
	/*16*/	uint32_t	TimeZone;
	/*20*/	uint32_t	Class;
	/*24*/
};

struct LFGuild_PlayerToggle_Struct
{
	/*000*/ uint32_t	Command;
	/*004*/ uint8_t	Unknown004[68];
	/*072*/ char	Comment[256];
	/*328*/ uint8_t	Unknown328[268];
	/*596*/ uint32_t	TimeZone;
	/*600*/ uint8_t	Toggle;
	/*601*/ uint8_t	Unknown601[7];
	/*608*/ uint32_t	Expires;
	/*612*/
};

struct LFGuild_GuildToggle_Struct
{
	/*000*/ uint32_t	Command;
	/*004*/ uint8_t	Unknown004[8];
	/*012*/ char	Comment[256];
	/*268*/ uint8_t	Unknown268[256];
	/*524*/ uint32_t	FromLevel;
	/*528*/ uint32_t	 ToLevel;
	/*532*/ uint32_t	Classes;
	/*536*/ uint32_t	AACount;
	/*540*/ uint32_t	TimeZone;
	/*544*/ uint8_t	Toggle;
	/*545*/ uint8_t	Unknown545[3];
	/*548*/ uint32_t	Expires;
	/*552*/ char	Name[64];
	/*616*/
};

#pragma pack()

}

#endif//_EQNET_STRUCTS_TITANIUM_H
