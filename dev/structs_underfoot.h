
#ifndef _EQNET_STRUCTS_UNDERFOOT_H_
#define _EQNET_STRUCTS_UNDERFOOT_H_

#include <cstdint>

namespace Underfoot
{

static const uint32_t BUFF_COUNT = 25;
static const size_t BANDOLIERS_SIZE = 20;
static const size_t BANDOLIER_ITEM_COUNT = 4;
static const size_t POTION_BELT_ITEM_COUNT = 5;
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

//New For SoF
struct WorldObjectsSent_Struct {
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
	union {
		struct {
			uint8_t blue;
			uint8_t Green;
			uint8_t Red;
			uint8_t UseTint;	// if there's a tint this is FF
		} RGB;
		uint32_t Color;
	};
};

struct CharSelectEquip
{
	uint32_t Material;
	uint32_t Unknown1;
	uint32_t EliteMaterial;
	Color_Struct Color;
};

struct CharacterSelectEntryA_Struct
{
	/*0000*/	uint8_t Level;				//
	/*0000*/	uint8_t HairStyle;			//
	/*0002*/	uint8_t Gender;				//
	/*0003*/	char Name[1];				// variable length, edi+0
};

struct CharacterSelectEntryB_Struct
{
	/*0000*/	uint8_t Beard;				//
	/*0001*/	uint8_t HairColor;			//
	/*0000*/	uint8_t Face;					//
	/*0000*/	CharSelectEquip	Equip[9];
	/*0000*/	uint32_t PrimaryIDFile;		//
	/*0000*/	uint32_t SecondaryIDFile;		//
	/*0000*/	uint8_t Unknown15;			// 0xff
	/*0000*/	uint32_t Deity;				//
	/*0000*/	uint16_t Zone;				//
	/*0000*/	uint16_t Instance;
	/*0000*/	uint8_t GoHome;				//
	/*0000*/	uint8_t Unknown19;			// 0xff
	/*0000*/	uint32_t Race;				//
	/*0000*/	uint8_t Tutorial;				//
	/*0000*/	uint8_t Class;				//
	/*0000*/	uint8_t EyeColor1;			//
	/*0000*/	uint8_t BeardColor;			//
	/*0000*/	uint8_t EyeColor2;			//
	/*0000*/	uint32_t DrakkinHeritage;		// Drakkin Heritage
	/*0000*/	uint32_t DrakkinTattoo;		// Drakkin Tattoo
	/*0000*/	uint32_t DrakkinDetails;		// Drakkin Details (Facial Spikes)
	/*0000*/	uint8_t Unknown;				// New field to Underfoot

};

/*
** Character Selection Struct
**
*/
struct CharacterSelect_Struct
{
	/*0000*/	uint32_t CharCount;	//number of chars in this packet
	/*0004*/	uint32_t TotalChars;	//total number of chars allowed?
};

/*
* Visible equiptment.
* Size: 12 Octets
*/
struct EquipStruct
{
	/*00*/ uint32_t Material;
	/*04*/ uint32_t Unknown1;
	/*08*/ uint32_t EliteMaterial;
	/*12*/
};


/*
** Generic Spawn Struct
** Length: 897 Octets
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

struct Spawn_Struct_Bitfields
{

	unsigned   ispet : 1;		// Could be 'is summoned pet' rather than just is pet.
	unsigned   afk : 1;		// 0=no, 1=afk
	unsigned   sneak : 1;
	unsigned   lfg : 1;
	unsigned   padding5 : 1;
	unsigned   invis : 1;		// 0 = visible, 1 = invis/sneaking
	unsigned   padding7 : 11;
	unsigned   gm : 1;
	unsigned   anon : 2;		// 0=normal, 1=anon, 2=roleplay
	unsigned   gender : 2;		// Gender (0=male, 1=female, 2=monster)
	unsigned   linkdead : 1;		// Toggles LD on or off after name
	unsigned   betabuffed : 1;
	unsigned   showhelm : 1;
	unsigned   padding26 : 1;
	unsigned   targetable : 1;	// 1 = Targetable 0 = Not Targetable (is_npc?)
	unsigned   targetable_with_hotkey : 1;	// is_npc?
	unsigned   showname : 1;
	unsigned   statue : 1;
	unsigned   trader : 1;
	unsigned   buyer : 1;
};

struct Spawn_Struct_Position
{
	/*0000*/ signed   padding0000 : 12; // ***Placeholder
	signed   deltaX : 13;      // change in x
	signed   padding0005 : 7;  // ***Placeholder
	/*0000*/ signed   deltaHeading : 10;// change in heading
	signed   deltaY : 13;      // change in y
	signed   padding0006 : 9;  // ***Placeholder
	/*0000*/ signed   y : 19;           // y coord
	signed   animation : 13;   // animation
	/*0000*/ unsigned heading : 12;     // heading
	signed   x : 19;           // x coord
	signed   padding0014 : 1;  // ***Placeholder
	/*0000*/ signed   z : 19;           // z coord
	signed   deltaZ : 13;      // change in z
};

struct Spawn_Struct
{
	// Note this struct is not used as such, it is here for reference. As the struct is variable sized, the packets
	// are constructed in Underfoot.cpp
	//
	/*0000*/ char     name[1];	//name[64];
	/*0000*/ //uint8_t     nullterm1; // hack to null terminate name
	/*0064*/ uint32_t spawnId;
	/*0068*/ uint8_t  level;
	/*0069*/ float    unknown1;
	/*0073*/ uint8_t  NPC;           // 0=player,1=npc,2=pc corpse,3=npc corpse
	Spawn_Struct_Bitfields	Bitfields;
	/*0000*/ uint8_t  otherData; // & 4 - has title, & 8 - has suffix, & 1 - it's a chest or untargetable
	/*0000*/ float unknown3;	// seen -1
	/*0000*/ float unknown4;
	/*0000*/ float size;
	/*0000*/ uint8_t  face;
	/*0000*/ float    walkspeed;
	/*0000*/ float    runspeed;
	/*0000*/ uint32_t race;
	/*0000*/ uint8_t  showname; // for body types - was charProperties
	/*0000*/ uint32_t bodytype;
	/*0000*/ //uint32_t bodytype2;      // this is only present if charProperties==2
	// are there more than two possible properties?
	/*0000*/ uint8_t  curHp;
	/*0000*/ uint8_t  haircolor;
	/*0000*/ uint8_t  beardcolor;
	/*0000*/ uint8_t  eyecolor1;
	/*0000*/ uint8_t  eyecolor2;
	/*0000*/ uint8_t  hairstyle;
	/*0000*/ uint8_t  beard;
	/*0000*/ uint32_t drakkin_heritage;
	/*0000*/ uint32_t drakkin_tattoo;
	/*0000*/ uint32_t drakkin_details;
	/*0000*/ uint8_t  statue;				// was holding
	/*0000*/ uint32_t deity;
	/*0000*/ uint32_t guildID;
	/*0000*/ uint32_t guildrank;			// 0=member, 1=officer, 2=leader, -1=not guilded
	/*0000*/ uint8_t  class_;
	/*0000*/ uint8_t  pvp;					// 0 = normal name color, 2 = PVP name color
	/*0000*/ uint8_t  StandState;			// stand state - 0x64 for normal animation
	/*0000*/ uint8_t  light;
	/*0000*/ uint8_t  flymode;
	/*0000*/ uint8_t  equip_chest2;
	/*0000*/ uint8_t  unknown9;
	/*0000*/ uint8_t  unknown10;
	/*0000*/ uint8_t  helm;
	/*0000*/ char     lastName[1];
	/*0000*/ //uint8_t     lastNameNull; //hack!
	/*0000*/ uint32_t aatitle;		// 0=none, 1=general, 2=archtype, 3=class was AARank
	/*0000*/ uint8_t  unknown12;
	/*0000*/ uint32_t petOwnerId;
	/*0000*/ uint8_t  unknown13;
	/*0000*/ uint32_t PlayerState;		// Stance 64 = normal 4 = aggressive 40 = stun/mezzed
	/*0000*/ uint32_t unknown15;
	/*0000*/ uint32_t unknown16;
	/*0000*/ uint32_t unknown17;
	/*0000*/ uint32_t unknown18;
	/*0000*/ uint32_t unknown19;
	Spawn_Struct_Position Position;
	/*0000*/ union
	{
		struct
		{
			/*0000*/ Color_Struct color_helmet;    // Color of helmet item
			/*0000*/ Color_Struct color_chest;     // Color of chest item
			/*0000*/ Color_Struct color_arms;      // Color of arms item
			/*0000*/ Color_Struct color_bracers;   // Color of bracers item
			/*0000*/ Color_Struct color_hands;     // Color of hands item
			/*0000*/ Color_Struct color_legs;      // Color of legs item
			/*0000*/ Color_Struct color_feet;      // Color of feet item
			/*0000*/ Color_Struct color_primary;   // Color of primary item
			/*0000*/ Color_Struct color_secondary; // Color of secondary item
		} equipment_colors;
		/*0000*/ Color_Struct colors[9]; // Array elements correspond to struct equipment_colors above
	};

	// skip these bytes if not a valid player race
	/*0000*/ union
	{
		struct
		{
			/*0000*/ EquipStruct equip_helmet;     // Equiptment: Helmet visual
			/*0000*/ EquipStruct equip_chest;      // Equiptment: Chest visual
			/*0000*/ EquipStruct equip_arms;       // Equiptment: Arms visual
			/*0000*/ EquipStruct equip_bracers;    // Equiptment: Wrist visual
			/*0000*/ EquipStruct equip_hands;      // Equiptment: Hands visual
			/*0000*/ EquipStruct equip_legs;       // Equiptment: Legs visual
			/*0000*/ EquipStruct equip_feet;       // Equiptment: Boots visual
			/*0000*/ EquipStruct equip_primary;    // Equiptment: Main visual
			/*0000*/ EquipStruct equip_secondary;  // Equiptment: Off visual
		} equip;
		/*0000*/ EquipStruct equipment[9];
	};

	/*0000*/ //char title[1];  // only read if(hasTitleOrSuffix & 4)
	/*0000*/ //char suffix[1]; // only read if(hasTitleOrSuffix & 8)
	char unknown20[8];
	uint8_t IsMercenary;	// If NPC == 1 and this == 1, then the NPC name is Orange.
	/*0000*/ char unknown21[28];
};


/*
** Generic Spawn Struct
** Fields from old struct not yet found:
**	uint8_t	traptype;	// 65 is disarmable trap, 66 and 67 are invis triggers/traps
**	uint8_t	is_pet;		// 0=no, 1=yes
**	uint8_t	afk;		// 0=no, 1=afk
**	uint8_t	is_npc;		// 0=no, 1=yes
**	uint8_t	max_hp;		// (name prolly wrong)takes on the value 100 for players, 100 or 110 for NPCs and 120 for PC corpses...
**	uint8_t	guildrank;	// 0=normal, 1=officer, 2=leader
**	uint8_t	eyecolor2;	//not sure, may be face
**	uint8_t	aaitle;		// 0=none, 1=general, 2=archtype, 3=class
*/

/*
** New Spawn
** Length: 176 Bytes
** OpCode: 4921
*/
struct NewSpawn_Struct
{
	struct Spawn_Struct spawn;	// Spawn Information
};


/*
** Client Zone Entry struct
** Length: 68 Octets
** OpCode: ZoneEntryCode (when direction == client)
*/
struct ClientZoneEntry_Struct {
	/*0000*/ uint32_t unknown0000;            // ***Placeholder
	/*0004*/ char     char_name[64];               // Player firstname [32]
	//*0036*/ uint8_t  unknown0036[28];        // ***Placeholder
	//*0064*/ uint32_t unknown0064;            // unknown
};


/*
** Server Zone Entry Struct
** Length: 452 Bytes
** OPCodes: OP_ServerZoneEntry
**
*/
struct ServerZoneEntry_Struct //Adjusted from SEQ Everquest.h Struct
{
	struct NewSpawn_Struct player;
};


//New Zone Struct - Size: 932
struct NewZone_Struct {
	/*0000*/	char	char_name[64];			// Character Name
	/*0064*/	char	zone_short_name[32];	// Zone Short Name
	/*0096*/	char    unknown0096[96];
	/*0192*/	char	zone_long_name[278];	// Zone Long Name
	/*0470*/	uint8_t	ztype;					// Zone type (usually FF)
	/*0471*/	uint8_t	fog_red[4];				// Zone fog (red)
	/*0475*/	uint8_t	fog_green[4];				// Zone fog (green)
	/*0479*/	uint8_t	fog_blue[4];				// Zone fog (blue)
	/*0483*/	uint8_t	unknown323;
	/*0484*/	float	fog_minclip[4];
	/*0500*/	float	fog_maxclip[4];
	/*0516*/	float	gravity;
	/*0520*/	uint8_t	time_type;
	/*0521*/    uint8_t   rain_chance[4];
	/*0525*/    uint8_t   rain_duration[4];
	/*0529*/    uint8_t   snow_chance[4];
	/*0533*/    uint8_t   snow_duration[4];
	/*0537*/    uint8_t   unknown537[33];
	/*0570*/	uint8_t	sky;					// Sky Type
	/*0571*/	uint8_t	unknown571[13];			// ***Placeholder
	/*0584*/	float	zone_exp_multiplier;	// Experience Multiplier
	/*0588*/	float	safe_y;					// Zone Safe Y
	/*0592*/	float	safe_x;					// Zone Safe X
	/*0596*/	float	safe_z;					// Zone Safe Z
	/*0600*/	float	min_z;					// Guessed - NEW - Seen 0
	/*0604*/	float	max_z;					// Guessed
	/*0608*/	float	underworld;				// Underworld, min z (Not Sure?)
	/*0612*/	float	minclip;				// Minimum View Distance
	/*0616*/	float	maxclip;				// Maximum View DIstance
	/*0620*/	uint8_t	unknown620[84];		// ***Placeholder
	/*0704*/	char	zone_short_name2[96];	//zone file name? excludes instance number which can be in previous version.
	/*0800*/	int32_t	unknown800;	//seen -1
	/*0804*/	char	unknown804[40]; //
	/*0844*/	int32_t	unknown844;	//seen 600
	/*0848*/	int32_t	unknown848;
	/*0852*/	uint16_t	zone_id;
	/*0854*/	uint16_t	zone_instance;
	/*0856*/	char	unknown856[20];
	/*0876*/	uint32_t	SuspendBuffs;
	/*0880*/	uint32_t	unknown880;	//seen 50
	/*0884*/	uint32_t	unknown884;	//seen 10
	/*0888*/	uint8_t	unknown888;	//seen 1
	/*0889*/	uint8_t	unknown889;	//seen 0 (POK) or 1 (rujj)
	/*0890*/	uint8_t	unknown890;	//seen 1
	/*0891*/	uint8_t	unknown891;	//seen 0
	/*0892*/	uint8_t	unknown892;	//seen 0
	/*0893*/	uint8_t	unknown893;	//seen 0 - 00
	/*0894*/	uint8_t	fall_damage;	// 0 = Fall Damage on, 1 = Fall Damage off
	/*0895*/	uint8_t	unknown895;	//seen 0 - 00
	/*0896*/	uint32_t	unknown896;	//seen 180
	/*0900*/	uint32_t	unknown900;	//seen 180
	/*0904*/	uint32_t	unknown904;	//seen 180
	/*0908*/	uint32_t	unknown908;	//seen 2
	/*0912*/	uint32_t	unknown912;	//seen 2
	/*0916*/	float	FogDensity;	//Of about 10 or so zones tested, all but one have this set to 0.33 Blightfire had 0.16
	/*0920*/	uint32_t	unknown920;	//seen 0
	/*0924*/	uint32_t	unknown924;	//seen 0
	/*0928*/	uint32_t	unknown928;	//seen 0
	/*0932*/	uint8_t  unknown932[12];
};


/*
** Memorize Spell Struct
** Length: 16 Bytes
**
*/
struct MemorizeSpell_Struct {
	uint32_t slot;     // Spot in the spell book/memorized slot
	uint32_t spell_id; // Spell id (200 or c8 is minor healing, etc)
	uint32_t scribing; // 1 if memorizing a spell, set to 0 if scribing to book, 2 if un-memming
	//uint32_t unknown12;
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
	uint32_t	unknown16;
};

struct SwapSpell_Struct
{
	uint32_t from_slot;
	uint32_t to_slot;


};

struct BeginCast_Struct
{
	// len = 8
	/*004*/	uint16_t	caster_id;
	/*006*/	uint16_t	spell_id;
	/*016*/	uint32_t	cast_time;		// in miliseconds
};

struct CastSpell_Struct
{
	uint32_t	slot;
	uint32_t	spell_id;
	uint32_t	inventoryslot;  // slot for clicky item, 0xFFFF = normal cast
	uint32_t	target_id;
	uint32_t  cs_unknown1;
	uint32_t  cs_unknown2;
	float   y_pos;
	float   x_pos;
	float   z_pos;
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

// Size 76 (was 24)
struct SpellBuff_Struct
{
	/*000*/	uint8_t slotid;				// badly named... seems to be 2 for a real buff, 0 otherwise
	/*001*/ uint8_t level;
	/*002*/	uint8_t bard_modifier;
	/*003*/	uint8_t effect;				// not real
	/*004*/	uint32_t unknown004;			// Seen 1 for no buff
	/*008*/ uint32_t spellid;
	/*012*/	int32_t duration;
	/*016*/ uint32_t unknown016;
	/*020*/	uint32_t player_id;			// 'global' ID of the caster, for wearoff messages
	/*024*/ uint32_t counters;
	/*028*/ uint8_t unknown0028[48];
	/*076*/
};

// Not functional yet, but this is what the packet looks like on Underfoot
struct SpellBuffFade_Struct_Underfoot {
	/*000*/	uint32_t entityid;	// Player id who cast the buff
	/*004*/	uint8_t slot;
	/*005*/	uint8_t level;
	/*006*/	uint8_t effect;
	/*007*/	uint8_t unknown7;
	/*008*/	float unknown008;
	/*012*/	uint32_t spellid;
	/*016*/	int32_t duration;
	/*020*/	uint32_t num_hits;
	/*024*/ uint32_t playerId;	// Global player ID?
	/*028*/	uint32_t unknown020;
	/*032*/ uint8_t unknown0028[48];
	/*080*/	uint32_t slotid;
	/*084*/	uint32_t bufffade;
	/*088*/
};

struct SpellBuffFade_Struct {
	/*000*/	uint32_t entityid;
	/*004*/	uint8_t slot;
	/*005*/	uint8_t level;
	/*006*/	uint8_t effect;
	/*007*/	uint8_t unknown7;
	/*008*/	uint32_t spellid;
	/*012*/	int32_t duration;
	/*016*/	uint32_t unknown016;
	/*020*/	uint32_t unknown020;		// Global player ID?
	/*024*/ uint32_t playerId;		// Player id who cast the buff
	/*028*/	uint32_t slotid;
	/*032*/	uint32_t bufffade;
	/*036*/
};

#if 0
struct BuffIconEntry_Struct {
	/*000*/ uint32_t buff_slot;
	/*004*/ uint32_t spell_id;
	/*008*/ uint32_t tics_remaining;
	/*012*/ uint32_t num_hits;
	// char name[1]; caster name is also here sometimes
	// uint8_t  unknownend; 1 when single, 0 when all opposite of all_buffs?
};

struct BuffIcon_Struct {
	/*000*/ uint32_t entity_id;
	/*004*/ uint32_t unknown004;
	/*008*/ uint8_t  all_buffs; // 1 when updating all buffs, 0 when doing one
	/*009*/ uint16_t count;
	/*011*/ BuffIconEntry_Struct entires[1];
};
#endif

struct BuffRemoveRequest_Struct
{
	/*00*/ uint32_t SlotID;
	/*04*/ uint32_t EntityID;
	/*08*/
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
	char zonename[64];
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
** OpCode: 0x009b
*/
struct CharCreate_Struct
{
	/*0000*/	uint32_t	class_;
	/*0004*/	uint32_t	haircolor;
	/*0008*/	uint32_t	beard;
	/*0012*/	uint32_t	beardcolor;
	/*0016*/	uint32_t	gender;
	/*0020*/	uint32_t	race;
	/*0024*/	uint32_t	start_zone;
	/*0028*/	uint32_t	hairstyle;
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
	/*0080*/	uint32_t	drakkin_heritage;
	/*0084*/	uint32_t	drakkin_tattoo;
	/*0088*/	uint32_t	drakkin_details;
	/*0092*/
};

/*
** Character Creation struct
** Length: 0 Bytes
** OpCode: 0x
*/
struct CharCreate_Struct_Temp //Size is now 0
{
};

/*
*Used in PlayerProfile
*/
struct AA_Array
{
	uint32_t AA;
	uint32_t value;
	uint32_t charges;	// expendable
};


static const uint32_t MAX_PP_DISCIPLINES = 200;

struct Disciplines_Struct {
	uint32_t values[MAX_PP_DISCIPLINES];
};

static const uint32_t MAX_PLAYER_TRIBUTES = 5;
static const uint32_t TRIBUTE_NONE = 0xFFFFFFFF;

struct Tribute_Struct {
	uint32_t tribute;
	uint32_t tier;
};

// Bandolier item positions
enum
{
	bandolierPrimary = 0,
	bandolierSecondary,
	bandolierRange,
	bandolierAmmo
};

//len = 72
struct BandolierItem_Struct
{
	uint32_t ID;
	uint32_t Icon;
	char Name[64];
};

//len = 320
struct Bandolier_Struct
{
	char Name[32];
	BandolierItem_Struct Items[BANDOLIER_ITEM_COUNT];
};

//len = 72
struct PotionBeltItem_Struct
{
	uint32_t ID;
	uint32_t Icon;
	char Name[64];
};

//len = 288
struct PotionBelt_Struct
{
	PotionBeltItem_Struct Items[POTION_BELT_ITEM_COUNT];
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


/*
** Player Profile
**
** Length: 4308 bytes
** OpCode: 0x006a
*/
static const uint32_t MAX_PP_LANGUAGE = 25; //
static const uint32_t MAX_PP_SPELLBOOK = 720; // Confirmed 60 pages on Underfoot now
static const uint32_t MAX_PP_MEMSPELL = 10; //was 9 now 10 on Underfoot
static const uint32_t MAX_PP_SKILL = PACKET_SKILL_ARRAY_SIZE;	// 100 - actual skills buffer size
static const uint32_t MAX_PP_AA_ARRAY = 300; //was 299
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

// Underfoot May 5 2010 - Size 25312 + 1320
// Underfoot May 12 2010 - Size 26632
struct PlayerProfile_Struct
{
	/*00000*/ uint32_t  checksum;				//
	//BEGIN SUB-STRUCT used for shrouding stuff...
	/*00004*/ uint32_t  gender;				// Player Gender - 0 Male, 1 Female
	/*00008*/ uint32_t  race;					// Player race
	/*00012*/ uint32_t  class_;				// Player class
	/*00016*/ uint8_t  unknown00016[40];		// #### uint32_t  unknown00016;   in Titanium ####uint8_t[40]
	/*00056*/ uint8_t   level;				// Level of player
	/*00057*/ uint8_t   level1;				// Level of player (again?)
	/*00058*/ uint8_t   unknown00058[2];		// ***Placeholder
	/*00060*/ BindStruct binds[5];			// Bind points (primary is first)
	/*00160*/ uint32_t  deity;				// deity
	/*00164*/ uint32_t  intoxication;			// Alcohol level (in ticks till sober?)
	/*00168*/ uint32_t  spellSlotRefresh[MAX_PP_MEMSPELL]; // Refresh time (millis) - 4 Octets Each
	/*00208*/ uint8_t   unknown00208[14];		// Seen 00 00 00 00 00 00 00 00 00 00 00 00 02 01
	/*00222*/ uint32_t  abilitySlotRefresh;
	/*00226*/ uint8_t   haircolor;			// Player hair color
	/*00227*/ uint8_t   beardcolor;			// Player beard color
	/*00228*/ uint8_t   eyecolor1;			// Player left eye color
	/*00229*/ uint8_t   eyecolor2;			// Player right eye color
	/*00230*/ uint8_t   hairstyle;			// Player hair style
	/*00231*/ uint8_t   beard;				// Player beard type
	/*00232*/ uint8_t	  unknown00232[4];		// was 14
	/*00236*/ union
	{
		struct
		{
			/*00236*/ EquipStruct equip_helmet; // Equiptment: Helmet visual
			/*00248*/ EquipStruct equip_chest; // Equiptment: Chest visual
			/*00260*/ EquipStruct equip_arms; // Equiptment: Arms visual
			/*00272*/ EquipStruct equip_bracers; // Equiptment: Wrist visual
			/*00284*/ EquipStruct equip_hands; // Equiptment: Hands visual
			/*00296*/ EquipStruct equip_legs; // Equiptment: Legs visual
			/*00308*/ EquipStruct equip_feet; // Equiptment: Boots visual
			/*00320*/ EquipStruct equip_primary; // Equiptment: Main visual
			/*00332*/ EquipStruct equip_secondary; // Equiptment: Off visual
		} equip;
		/*00236*/ EquipStruct equipment[9]; //Underfoot Shows [108] for this part
	};
	/*00344*/ uint8_t unknown00344[168];		// Underfoot Shows [160]
	/*00512*/ Color_Struct item_tint[9];	// RR GG BB 00
	/*00548*/ AA_Array  aa_array[MAX_PP_AA_ARRAY];	// [3600] AAs 12 bytes each
	/*04148*/ uint32_t  points;				// Unspent Practice points - RELOCATED???
	/*04152*/ uint32_t  mana;					// Current mana
	/*04156*/ uint32_t  cur_hp;				// Current HP without +HP equipment
	/*04160*/ uint32_t  STR;					// Strength - 6e 00 00 00 - 110
	/*04164*/ uint32_t  STA;					// Stamina - 73 00 00 00 - 115
	/*04168*/ uint32_t  CHA;					// Charisma - 37 00 00 00 - 55
	/*04172*/ uint32_t  DEX;					// Dexterity - 50 00 00 00 - 80
	/*04176*/ uint32_t  INT;					// Intelligence - 3c 00 00 00 - 60
	/*04180*/ uint32_t  AGI;					// Agility - 5f 00 00 00 - 95
	/*04184*/ uint32_t  WIS;					// Wisdom - 46 00 00 00 - 70
	/*04188*/ uint8_t   unknown04188[28];		//
	/*04216*/ uint8_t   face;					// Player face - Actually uint32_t?
	/*04217*/ uint8_t   unknown04217[147];		// was [175]
	/*04364*/ uint32_t   spell_book[MAX_PP_SPELLBOOK];	// List of the Spells in spellbook 720 = 90 pages [2880] was [1920]
	/*07244*/ uint32_t   mem_spells[MAX_PP_MEMSPELL]; // List of spells memorized
	/*07284*/ uint8_t   unknown07284[28];		//#### uint8_t unknown04396[32]; in Titanium ####[28]
	/*07312*/ uint32_t  platinum;				// Platinum Pieces on player
	/*07316*/ uint32_t  gold;					// Gold Pieces on player
	/*07320*/ uint32_t  silver;				// Silver Pieces on player
	/*07324*/ uint32_t  copper;				// Copper Pieces on player
	/*07328*/ uint32_t  platinum_cursor;		// Platinum Pieces on cursor
	/*07332*/ uint32_t  gold_cursor;			// Gold Pieces on cursor
	/*07336*/ uint32_t  silver_cursor;		// Silver Pieces on cursor
	/*07340*/ uint32_t  copper_cursor;		// Copper Pieces on cursor
	/*07344*/ uint32_t  skills[MAX_PP_SKILL];	// [400] List of skills	// 100 dword buffer
	/*07744*/ uint8_t   unknown07644[136];
	/*07880*/ uint32_t  toxicity;				// Potion Toxicity (15=too toxic, each potion adds 3)
	/*07884*/ uint32_t  thirst_level;			// Drink (ticks till next drink)
	/*07888*/ uint32_t  hunger_level;			// Food (ticks till next eat)
	/*07892*/ SpellBuff_Struct buffs[BUFF_COUNT];	// [1900] Buffs currently on the player (30 Max) - (Each Size 76)
	/*09792*/ uint8_t   unknown09792[380];		// BUFF_COUNT has been left at 25. These are the extra 5 buffs in Underfoot
	/*10172*/ Disciplines_Struct  disciplines;	// [400] Known disciplines
	/*10972*/ uint32_t  recastTimers[MAX_RECAST_TYPES]; // Timers (UNIX Time of last use)
	/*11052*/ uint8_t   unknown11052[160];		// Some type of Timers
	/*11212*/ uint32_t  endurance;			// Current endurance
	/*11216*/ uint8_t   unknown11216[20];		// ?
	/*11236*/ uint32_t  aapoints_spent;		// Number of spent AA points
	/*11240*/ uint32_t  aapoints;				// Unspent AA points
	/*11244*/ uint8_t unknown11244[4];
	/*11248*/ Bandolier_Struct bandoliers[BANDOLIERS_SIZE]; // [6400] bandolier contents
	/*17648*/ PotionBelt_Struct  potionbelt;	// [360] potion belt 72 extra octets by adding 1 more belt slot
	/*18008*/ uint8_t unknown18008[8];
	/*18016*/ uint32_t available_slots;
	/*18020*/ uint8_t unknown18020[80];		//
	//END SUB-STRUCT used for shrouding.
	/*18100*/ char    name[64];				// Name of player
	/*18164*/ char    last_name[32];		// Last name of player
	/*18196*/ uint8_t   unknown18196[8];  //#### Not In Titanium #### new to SoF[12]
	/*18204*/ uint32_t   guild_id;            // guildid
	/*18208*/ uint32_t  birthday;       // character birthday
	/*18212*/ uint32_t  lastlogin;       // character last save time
	/*18216*/ uint32_t  account_startdate;       // Date the Account was started - New Field for Underfoot***
	/*18220*/ uint32_t  timePlayedMin;      // time character played
	/*18224*/ uint8_t   pvp;                // 1=pvp, 0=not pvp
	/*18225*/ uint8_t   anon;               // 2=roleplay, 1=anon, 0=not anon
	/*18226*/ uint8_t   gm;                 // 0=no, 1=yes (guessing!)
	/*18227*/ uint8_t    guildrank;        // 0=member, 1=officer, 2=guildleader -1=no guild
	/*18228*/ uint32_t  guildbanker;
	/*18232*/ uint8_t unknown18232[4];  //was [8]
	/*18236*/ uint32_t  exp;                // Current Experience
	/*18240*/ uint8_t unknown18240[8];
	/*18248*/ uint32_t  timeentitledonaccount;
	/*18252*/ uint8_t   languages[MAX_PP_LANGUAGE]; // List of languages
	/*18277*/ uint8_t   unknown18277[7];    //#### uint8_t   unknown13109[4]; in Titanium ####[7]
	/*18284*/ float     y;                  // Players y position (NOT positive about this switch)
	/*18288*/ float     x;                  // Players x position
	/*18292*/ float     z;                  // Players z position
	/*18296*/ float     heading;            // Players heading
	/*18300*/ uint8_t   unknown18300[4];    // ***Placeholder
	/*18304*/ uint32_t  platinum_bank;      // Platinum Pieces in Bank
	/*18308*/ uint32_t  gold_bank;          // Gold Pieces in Bank
	/*18312*/ uint32_t  silver_bank;        // Silver Pieces in Bank
	/*18316*/ uint32_t  copper_bank;        // Copper Pieces in Bank
	/*18320*/ uint32_t  platinum_shared;    // Shared platinum pieces
	/*18324*/ uint8_t unknown18324[1036];    // was [716]
	/*19360*/ uint32_t  expansions;         // Bitmask for expansions ff 7f 00 00 - SoD
	/*19364*/ uint8_t unknown19364[12];
	/*19376*/ uint32_t  autosplit;          // 0 = off, 1 = on
	/*19380*/ uint8_t unknown19380[16];
	/*19396*/ uint16_t  zone_id;             // see zones.h
	/*19398*/ uint16_t  zoneInstance;       // Instance id
	/*19400*/ char      groupMembers[MAX_GROUP_MEMBERS][64];// 384 all the members in group, including self
	/*19784*/ char      groupLeader[64];    // Leader of the group ?
	/*19848*/ uint8_t unknown19848[540];  // was [348]
	/*20388*/ uint32_t  entityid;
	/*20392*/ uint32_t  leadAAActive;       // 0 = leader AA off, 1 = leader AA on
	/*20396*/ uint8_t unknown20396[4];
	/*20400*/ int32_t  ldon_points_guk;    // Earned GUK points
	/*20404*/ int32_t  ldon_points_mir;    // Earned MIR points
	/*20408*/ int32_t  ldon_points_mmc;    // Earned MMC points
	/*20412*/ int32_t  ldon_points_ruj;    // Earned RUJ points
	/*20416*/ int32_t  ldon_points_tak;    // Earned TAK points
	/*20420*/ int32_t  ldon_points_available;  // Available LDON points
	/*20424*/ uint32_t  unknown20424[7];
	/*20452*/ uint32_t  unknown20452;
	/*20456*/ uint32_t  unknown20456;
	/*20460*/ uint8_t unknown20460[4];
	/*20464*/ uint32_t  unknown20464[6];
	/*20488*/ uint8_t unknown20488[72]; // was [136]
	/*20560*/ float  tribute_time_remaining;        // Time remaining on tribute (millisecs)
	/*20564*/ uint32_t  career_tribute_points;      // Total favor points for this char
	/*20568*/ uint32_t  unknown20546;        // *** Placeholder
	/*20572*/ uint32_t  tribute_points;     // Current tribute points
	/*20576*/ uint32_t  unknown20572;        // *** Placeholder
	/*20580*/ uint32_t  tribute_active;      // 0 = off, 1=on
	/*20584*/ Tribute_Struct tributes[MAX_PLAYER_TRIBUTES]; // [40] Current tribute loadout
	/*20624*/ uint8_t unknown20620[4];
	/*20628*/ double group_leadership_exp;     // Current group lead exp points
	/*20636*/ double raid_leadership_exp;      // Current raid lead AA exp points
	/*20644*/ uint32_t  group_leadership_points; // Unspent group lead AA points
	/*20648*/ uint32_t  raid_leadership_points;  // Unspent raid lead AA points
	/*20652*/ LeadershipAA_Struct leader_abilities; // [128]Leader AA ranks 19332
	/*20780*/ uint8_t unknown20776[128];		// was [128]
	/*20908*/ uint32_t  air_remaining;       // Air supply (seconds)
	/*20912*/ uint32_t  PVPKills;
	/*20916*/ uint32_t  PVPDeaths;
	/*20920*/ uint32_t  PVPCurrentPoints;
	/*20924*/ uint32_t  PVPCareerPoints;
	/*20928*/ uint32_t  PVPBestKillStreak;
	/*20932*/ uint32_t  PVPWorstDeathStreak;
	/*20936*/ uint32_t  PVPCurrentKillStreak;
	/*20940*/ PVPStatsEntry_Struct PVPLastKill;		// size 88
	/*21028*/ PVPStatsEntry_Struct PVPLastDeath;	// size 88
	/*21116*/ uint32_t  PVPNumberOfKillsInLast24Hours;
	/*21120*/ PVPStatsEntry_Struct PVPRecentKills[50];	// size 4400 - 88 each
	/*25520*/ uint32_t expAA;               // Exp earned in current AA point
	/*25524*/ uint8_t unknown25524[40];
	/*25564*/ uint32_t currentRadCrystals;  // Current count of radiant crystals
	/*25568*/ uint32_t careerRadCrystals;   // Total count of radiant crystals ever
	/*25572*/ uint32_t currentEbonCrystals; // Current count of ebon crystals
	/*25576*/ uint32_t careerEbonCrystals;  // Total count of ebon crystals ever
	/*25580*/ uint8_t  groupAutoconsent;    // 0=off, 1=on
	/*25581*/ uint8_t  raidAutoconsent;     // 0=off, 1=on
	/*25582*/ uint8_t  guildAutoconsent;    // 0=off, 1=on
	/*25583*/ uint8_t  unknown25583;     // ***Placeholder (6/29/2005)
	/*25584*/ uint32_t level3;		// SoF looks at the level here to determine how many leadership AA you can bank.
	/*25588*/ uint32_t showhelm;            // 0=no, 1=yes
	/*25592*/ uint32_t RestTimer;
	/*25596*/ uint8_t   unknown25596[1036]; // ***Placeholder (2/13/2007) was[1028]or[940]or[1380] - END of Struct
	/*26632*/
};

/**
* Shroud spawn. For others shrouding, this has their spawnId and
* spawnStruct.
*
* Length: 586
* OpCode: OP_Shroud
*/
//struct spawnShroudOther_Struct
//{
//*0000*/ uint32_t spawnId;          // Spawn Id of the shrouded player
//*0004*/ spawn_Struct spawn;         // Updated spawn struct for the player
//*0586*/
//};

/**
* Shroud yourself. For yourself shrouding, this has your spawnId, spawnStruct,
* bits of your charProfileStruct (no checksum, then charProfile up till
* but not including name), and an itemPlayerPacket for only items on the player
* and not the bank.
*
* Length: Variable
* OpCode: OP_Shroud
*/
//struct spawnShroudSelf_Struct
//{
//*00000*/ uint32_t spawnId;            // Spawn Id of you
//*00004*/ spawn_Struct spawn;           // Updated spawnStruct for you
//*00586*/ PlayerProfile_Struct profile; // Character profile for shrouded char
//*13522*/ uint8_t items;  // Items on the player
/*xxxxx*/
//};



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
	/*004*/ uint32_t	target;
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
	/*11*/	char	sayer[1];				// Who is the source of the info - Was 1
	/*12*/	uint8_t	unknown12[12];
	/*24*/	char	message[128];				// What is being said? - was 128
};

/*
** When somebody changes what they're wearing
**      or give a pet a weapon (model changes)
** Length: 19 Bytes
*/
struct WearChange_Struct{
	/*000*/ uint16_t spawn_id;
	/*002*/ uint32_t material;
	/*006*/ uint32_t unknown06;
	/*010*/ uint32_t elite_material;	// 1 for Drakkin Elite Material
	/*014*/ Color_Struct color;
	/*018*/ uint8_t wear_slot_id;
	/*019*/
};

/*
** Type:   Bind Wound Structure
** Length: 8 Bytes
*/
//Fixed for 7-14-04 patch
struct BindWound_Struct
{
	/*000*/	uint16_t	to;			// TargetID
	/*002*/	uint16_t	unknown2;		// ***Placeholder
	/*004*/	uint16_t	type;
	/*006*/	uint16_t	unknown6;
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
	/*02*/	uint8_t speed;
	/*03*/	uint8_t action;
	/*04*/
};

// this is what causes the caster to animate and the target to
// get the particle effects around them when a spell is cast
// also causes a buff icon
struct Action_Struct
{
	/*00*/	uint16_t target;			// id of target
	/*02*/	uint16_t source;			// id of caster
	/*04*/	uint16_t level;			// level of caster - Seen 0
	/*06*/  uint32_t unknown06;
	/*10*/	uint16_t instrument_focus;
	/*12*/	uint16_t unknown12;		// seems to always be set to something and it doesn't change between casts except in special cases like changing instrument mods
	/*14*/  uint32_t unknown14;       // seen 0
	/*18*/  float knockback_angle;  //seems to go from 0-512 then it rolls over again
	/*22*/  uint32_t unknown22;
	/*26*/  uint8_t type;
	/*27*/  uint32_t damage;
	/*31*/  uint16_t unknown31;
	/*33*/	uint16_t spell;			// spell id being cast
	/*35*/	uint8_t level2;			// level of caster again? Or maybe the castee
	/*36*/	uint8_t effect_flag;		// if this is 4, the effect is valid: or if two are sent at the same time?
};



// Starting with 2/21/2006, OP_Actions seem to come in pairs, duplicating
// themselves, with the second one with slightly more information. Maybe this
// has to do with buff blocking??
struct ActionAlt_Struct
{
	/*00*/	uint16_t target;			// id of target
	/*02*/	uint16_t source;			// id of caster
	/*04*/	uint16_t level;			// level of caster - Seen 0
	/*06*/  uint32_t unknown06;
	/*10*/	float instrument_mod;
	/*14*/  uint32_t unknown14;       // seen 0
	/*18*/  float knockback_angle;  //seems to go from 0-512 then it rolls over again
	/*22*/  uint32_t unknown22;
	/*26*/  uint8_t type;
	/*27*/  uint32_t damage;
	/*31*/  uint16_t unknown31;
	/*33*/	uint16_t spell;			// spell id being cast
	/*35*/	uint8_t level2;			// level of caster again? Or maybe the castee
	/*36*/	uint8_t effect_flag;		// if this is 4, the effect is valid: or if two are sent at the same time?
	/*37*/	uint32_t unknown37;		// New field to Underfoot - Seen 14
	/*41*/	uint8_t unknown41;			// New field to Underfoot - Seen 0
	/*42*/	uint8_t unknown42;			// New field to Underfoot - Seen 0
	/*43*/	uint8_t unknown43;			// New field to Underfoot - Seen 0
	/*44*/	uint32_t unknown44;		// New field to Underfoot - Seen 23
	/*48*/	uint32_t unknown48;		// New field to Underfoot - Seen -1
	/*52*/	uint32_t unknown52;		// New field to Underfoot - Seen -1
	/*56*/	uint32_t unknown56;		// New field to Underfoot - Seen 0
	/*60*/	uint32_t unknown60;		// New field to Underfoot - Seen 0
	/*64*/
};

// this is what prints the You have been struck. and the regular
// melee messages like You try to pierce, etc.  It's basically the melee
// and spell damage message
struct CombatDamage_Struct
{
	/* 00 */	uint16_t	target;
	/* 02 */	uint16_t	source;
	/* 04 */	uint8_t	type;			//slashing, etc.  231 (0xE7) for spells
	/* 05 */	uint16_t	spellid;
	/* 07 */	int32_t	damage;
	/* 11 */	float	force;		// cd cc cc 3d
	/* 15 */	float	meleepush_xy;		// see above notes in Action_Struct
	/* 19 */	float	meleepush_z;
	/* 23 */	uint8_t	unknown23[5];	// was [9]
	/* 28 */
};


/*
** Consider Struct
** Length: 20 Bytes
*/
struct Consider_Struct{
	/*000*/ uint32_t	playerid;               // PlayerID
	/*004*/ uint32_t	targetid;               // TargetID
	/*008*/ uint32_t	faction;                // Faction
	/*012*/ uint32_t	level;					// Level
	/*016*/ uint8_t	pvpcon;					// Pvp con flag 0/1
	/*017*/ uint8_t	unknown017[3];			//
	/*020*/
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

struct ZonePlayerToBind_Struct {
	/*000*/	uint16_t	bind_zone_id;
	/*002*/	uint16_t	bind_instance_id;
	/*004*/	float	x;
	/*008*/	float	y;
	/*012*/	float	z;
	/*016*/	float	heading;
	/*020*/	char	zone_name[1];  // Or "Bind Location"
	/*000*/	uint8_t	unknown021;	// Seen 1 - Maybe 0 would be to force a rezone and 1 is just respawn
	/*000*/	uint32_t	unknown022;	// Seen 32 or 59
	/*000*/	uint32_t	unknown023;	// Seen 0
	/*000*/	uint32_t	unknown024;	// Seen 21 or 43
};

struct ZonePlayerToBindHeader_Struct
{
	/*000*/	uint16_t	bind_zone_id;
	/*002*/	uint16_t	bind_instance_id;
	/*004*/	float	x;
	/*008*/	float	y;
	/*012*/	float	z;
	/*016*/	float	heading;
	/*020*/	char	zone_name[1];  // Or "Bind Location"
};

struct ZonePlayerToBindFooter_Struct
{
	/*000*/	uint8_t	unknown021;	// Seen 1 - Maybe 0 would be to force a rezone and 1 is just respawn
	/*000*/	uint32_t	unknown022;	// Seen 32 or 59
	/*000*/	uint32_t	unknown023;	// Seen 0
	/*000*/	uint32_t	unknown024;	// Seen 21 or 43
};

typedef struct {
	/*000*/	uint32_t	bind_number;		// Number of this bind in the iteration
	/*004*/	uint32_t	bind_zone_id;		// ID of the zone for this bind point or resurect point
	/*008*/	float	x;					// X loc for this bind point
	/*012*/	float	y;					// Y loc for this bind point
	/*016*/	float	z;					// Z loc for this bind point
	/*020*/	float	heading;			// Heading for this bind point
	/*024*/	char	bind_zone_name[1];	// Or "Bind Location" or "Resurrect"
	/*000*/	uint8_t	validity;		// 0 = valid choice, 1 = not a valid choice at this time (resurrection)
} RespawnOptions_Struct;

struct RespawnWindow_Struct {
	/*000*/	uint32_t	unknown000;		// Seen 0
	/*004*/	uint32_t	time_remaining;	// Total time before respawn in milliseconds
	/*008*/	uint32_t	unknown008;		// Seen 0
	/*012*/	uint32_t	total_binds;	// Total Bind Point Options? - Seen 2
	/*016*/ RespawnOptions_Struct bind_points;
	// First bind point is "Bind Location" and the last one is "Ressurect"
};


/*
** Spawn position update - Size: 22
**	Struct sent from server->client to update position of
**	another spawn's position update in zone (whether NPC or PC)
**
*/
struct PlayerPositionUpdateServer_Struct
{
	/*0000*/ uint16_t		spawn_id;
	/*0002*/ signed		padding0000 : 12; // ***Placeholder
	signed		delta_x : 13;      // change in x
	signed		padding0005 : 7;  // ***Placeholder
	/*0006*/ signed		delta_heading : 10;// change in heading
	signed		delta_y : 13;      // change in y
	signed		padding0006 : 9;  // ***Placeholder
	/*0010*/ signed		y_pos : 19;           // y coord
	signed		animation : 10;   // animation
	signed		padding0010 : 3;  // ***Placeholder
	/*0014*/ unsigned	heading : 12;     // heading
	signed		x_pos : 19;           // x coord
	signed		padding0014 : 1;  // ***Placeholder
	/*0018*/ signed		z_pos : 19;           // z coord
	signed		delta_z : 13;      // change in z
	/*0022*/
};


/*
** Player position update - Size: 40
**	Struct sent from client->server to update
**	player position on server
**
*/
struct PlayerPositionUpdateClient_Struct
{
	/*0000*/ uint16_t		spawn_id;			// Player's spawn id
	/*0002*/ uint16_t		sequence;			// increments one each packet - Verified
	/*0004*/ uint8_t		unknown0004[4];		// ***Placeholder
	/*0008*/ float		x_pos;				// x coord (2nd loc value)
	/*0012*/ float		y_pos;				// y coord (1st loc value)
	/*0016*/ signed		delta_heading : 10;	// change in heading
	unsigned	padding0036 : 10;		// animation
	unsigned	padding0016 : 12;		// ***Placeholder
	/*0020*/ float		delta_x;			// Change in x
	/*0024*/ float		delta_y;			// Change in y
	/*0028*/ float		z_pos;				// z coord (3rd loc value)
	/*0032*/ float		delta_z;			// Change in z
	/*0036*/ unsigned	animation : 10;		// ***Placeholder
	unsigned	heading : 12;			// Directional heading
	unsigned	padding0037 : 10;		// ***Placeholder
	/*0040*/
};

/*
** Spawn HP Update
** Length: 10 Bytes
** OpCode: OP_HPUpdate
*/
struct SpawnHPUpdate_Struct
{
	/*00*/ uint32_t	cur_hp;               // Id of spawn to update
	/*04*/ int32_t	max_hp;                 // Maximum hp of spawn
	/*08*/ int16_t	spawn_id;                 // Current hp of spawn
	/*10*/
};

/*
** SendExpZonein
** Length: 152 Bytes
** OpCode: OP_SendExpZonein
*/
struct SendExpZonein_Struct
{
	/*0000*/ uint16_t spawn_id;          // ID of the spawn
	/*0002*/ uint16_t type;              // Values associated with the type
	/*0004*/ uint32_t parameter;         // Type of data sent
	/*0008*/ uint32_t exp;                    // Current experience ratio from 0 to 330
	/*0012*/ uint32_t	expAA;
	/*0016*/ uint8_t	unknown0016[4];
	/*0020*/ char	name[64];
	/*0084*/ char	last_name[64];
	/*00148*/ uint32_t	unknown132;
	/*00152*/
};

/*
** SendExpZonein
** Length: 0 Bytes
** OpCode: OP_SendExpZonein
*/
//struct SendExpZonein_Struct {};

struct SpawnHPUpdate_Struct2
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
	/*04*/	char			SerializedItem[1]; //was 1
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
	/*0016*/
};

struct ItemNamePacket_Struct {
	/*000*/	uint32_t item_id;
	/*004*/	uint32_t unkown004;
	/*008*/ char name[64];
	/*072*/
};

// Length: 16
struct ItemProperties_Struct_Old {

	/*000*/ uint8_t	unknown01[2];
	/*002*/ uint8_t	charges;
	/*003*/ uint8_t	unknown02[13];
	/*016*/
};

// Length: 8
struct ItemProperties_Struct {

	/*000*/ uint8_t	unknown01[4];
	/*004*/ uint8_t	charges;
	/*005*/ uint8_t	unknown02[3];
	/*008*/
};

struct DeleteItem_Struct {
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

static const uint32_t MAX_NUMBER_GUILDS = 1500;
struct GuildsList_Struct {
	uint8_t head[64]; // First on guild list seems to be empty...
	GuildsListEntry_Struct Guilds[MAX_NUMBER_GUILDS];
};

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

struct LootingItem_Struct {
	/*000*/	uint32_t	lootee;
	/*004*/	uint32_t	looter;
	/*008*/	uint32_t	slot_id;
	/*012*/	uint32_t	auto_loot;
	/*016*/	uint32_t	unknown16;
	/*020*/
};

struct GuildManageStatus_Struct{
	uint32_t	guildid;
	uint32_t	oldrank;
	uint32_t	newrank;
	char	name[64];
};
// Guild invite, remove
struct GuildJoin_Struct{
	/*000*/	uint32_t	guild_id;
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

struct OnLevelMessage_Struct {
	/*0000*/	char    Title[128];
	/*0128*/	char    Text[4096];
	/*4224*/	char	ButtonName0[25];	// If Buttons = 1, these two are the text for the left and right buttons respectively
	/*4249*/	char	ButtonName1[25];
	/*4274*/	uint8_t	Buttons;
	/*4275*/	uint8_t	Unknown4275;	// Something to do with audio controls
	/*4276*/	uint32_t  Duration;
	/*4280*/	uint32_t  PopupID;	// If none zero, a response packet with 00 00 00 00 <PopupID> is returned on clicking the left button
	/*4284*/	uint32_t  NegativeID;	// If none zero, a response packet with 01 00 00 00 <NegativeID> is returned on clicking the right button
	/*4288*/	uint32_t  Unknown4288;
	/*4292*/
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

/* 9/23/03 reply to /random command */
struct RandomReply_Struct {
	/* 00 */	uint32_t low;
	/* 04 */	uint32_t high;
	/* 08 */	uint32_t result;
	/* 12 */	char name[64];
	/* 76 */
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
	uint16_t	year;
	/*0006*/ uint16_t unknown0016;            // Placeholder
	/*0008*/
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
	/*012*/	uint32_t	unknown12;
	/*016*/	uint8_t	quantity;		// Already sold
	/*017*/ uint8_t	Unknown017[3];
	/*020*/	uint32_t	Unknown020;
	/*024*/	uint32_t	price;
	/*028*/	uint32_t	pricehighorderbits;	// It appears the price is 64 bits in Underfoot+
	/*032*/
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
	/*004*/	uint32_t	npcid;
	/*008*/	uint32_t	itemid;
	/*012*/	uint32_t	variable;
};

struct Adventure_Sell_Struct {
	/*000*/	uint32_t	unknown000;	//0x01 - Stack Size/Charges?
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

//this is mostly right but something is off that causes the client to crash sometimes
//I don't really care enough about the feature to work on it anymore though.
struct AdventureLeaderboardEntry_Struct
{
	/*004*/ char name[64];
	/*008*/ uint32_t success;
	/*012*/ uint32_t failure;
	/*016*/
};

struct AdventureLeaderboard_Struct
{
	/*000*/ uint32_t unknown000;
	/*004*/ uint32_t unknown004;
	/*008*/ uint32_t success;
	/*012*/ uint32_t failure;
	/*016*/ uint32_t our_rank;
	/*020*/
};

/*struct Item_Shop_Struct {
uint16_t merchantid;
uint8_t itemtype;
Item_Struct item;
uint8_t iss_unknown001[6];
};*/

struct Illusion_Struct {  //size: 256
	/*000*/	uint32_t	spawnid;
	/*004*/	char	charname[64];	//
	/*068*/	uint16_t	race;			//
	/*070*/	char	unknown006[2];	// Weird green name
	/*072*/	uint8_t	gender;
	/*073*/	uint8_t	texture;
	/*074*/	uint8_t	unknown074;		//
	/*075*/	uint8_t	unknown075;		//
	/*076*/	uint8_t	helmtexture;	//
	/*077*/	uint8_t	unknown077;		//
	/*078*/	uint8_t	unknown078;		//
	/*079*/	uint8_t	unknown079;		//
	/*080*/	uint32_t	face;			//
	/*084*/	uint8_t	hairstyle;		// Some Races don't change Hair Style Properly in SoF
	/*085*/	uint8_t	haircolor;		//
	/*086*/	uint8_t	beard;			//
	/*087*/	uint8_t	beardcolor;		//
	/*088*/ float	size;			//
	/*092*/	uint8_t	unknown092[148];
	/*240*/ uint32_t	unknown240;		// Removes armor?
	/*244*/ uint32_t	drakkin_heritage;	//
	/*248*/ uint32_t	drakkin_tattoo;		//
	/*252*/ uint32_t	drakkin_details;	//
	/*256*/
};

struct ZonePoint_Entry { //28 octets
	/*0000*/	uint32_t	iterator;
	/*0004*/	float	y;
	/*0008*/	float	x;
	/*0012*/	float	z;
	/*0016*/	float	heading;
	/*0020*/	uint16_t	zoneid;
	/*0022*/	uint16_t	zoneinstance; // LDoN instance
	/*0024*/    uint32_t  unknown024;
	/*0028*/
};

struct ZonePoints {
	/*0000*/	uint32_t	count;
	/*0004*/	struct	ZonePoint_Entry zpe[1]; // Always add one extra to the end after all zonepoints
	//*0xxx*/    uint8_t     unknown0xxx[24]; //New from SEQ
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

struct GroupInvite_Struct {
	/*0000*/	char	invitee_name[64];
	/*0064*/	char	inviter_name[64];
	/*0128*/	uint32_t	unknown0128;
	/*0132*/	uint32_t	unknown0132;
	/*0136*/	uint32_t	unknown0136;
	/*0140*/	uint32_t	unknown0140;
	/*0144*/	uint32_t	unknown0144;
	/*0148*/
};

struct GroupGeneric_Struct {
	/*0000*/	char	name1[64];
	/*0064*/	char	name2[64];
	/*0128*/	uint32_t	unknown0128;
	/*0132*/	uint32_t	unknown0132;
	/*0136*/	uint32_t	unknown0136;
	/*0140*/	uint32_t	unknown0140;
	/*0144*/	uint32_t	unknown0144;
	/*0148*/
};

struct GroupCancel_Struct {
	/*000*/	char	name1[64];
	/*064*/	char	name2[64];
	/*128*/	uint8_t	unknown128[20];
	/*148*/	uint32_t	toggle;
	/*152*/
};

struct GroupUpdate_Struct {
	/*0000*/	uint32_t	action;
	/*0004*/	char	yourname[64];
	/*0068*/	char	membername[5][64];
	/*0388*/	char	leadersname[64];
	/*0452*/
};

struct GroupUpdate2_Struct {
	/*0000*/	uint32_t	action;
	/*0004*/	char	yourname[64];
	/*0068*/	char	membername[5][64];
	/*0388*/	char	leadersname[64];
	/*0452*/	GroupLeadershipAA_Struct leader_aas;
	/*0516*/	uint8_t	unknown[252];	// Titanium uses [188] here
	/*0768*/
};

struct GroupUpdate_Struct_Underfoot {	// New for Underfoot
	/*0000*/	uint32_t	groupid;		// Guess - Matches unknown0136 from GroupFollow_Struct
	/*0004*/	uint32_t	totalmembers;	// Guess
	/*0000*/	//uint32_t	leadersname[1];	// Group Leader Name Null Terminated
	/*0008*/	//GroupMembers_Struct groupmembers;
};

struct GroupMembers_Struct {	// New for Underfoot
	/*0000*/	uint32_t	membernumber;	// Guess - number of member in the group (0 to 5?)
	/*0000*/	//char	membername[1];	// Member Name Null Terminated
	/*0000*/	uint8_t	unknown001[3];	// Seen 0
	/*0000*/	uint32_t	memberlevel;	// Guess
	/*0000*/	uint8_t	unknown002[11];	// Seen 0
};

struct GroupJoin_Struct_Underfoot {	// New for Underfoot
	/*0000*/	uint32_t	unknown0000;	// Matches unknown0136 from GroupFollow_Struct
	/*0004*/	uint32_t	action;
	/*0008*/	uint8_t	unknown0008[5];	// Seen 0
	/*0013*/	//char	membername[1];	// Null Terminated?
	/*0000*/	uint8_t	unknown0013[3];	// Seen 0
	/*0000*/	uint32_t	unknown0016;	// Matches unknown0132 from GroupFollow_Struct
	/*0000*/	uint8_t	unknown0020[11];	// Seen 0
};

struct GroupJoin_Struct {
	/*000*/	char	unknown000[64];
	/*064*/	char	membername[64];
	/*128*/	uint8_t	unknown128[20];	// Leadership AA ?
	/*148*/
};

struct GroupFollow_Struct { // Underfoot Follow Struct
	/*0000*/	char	name1[64];	// inviter
	/*0064*/	char	name2[64];	// invitee
	/*0128*/	uint32_t	unknown0128;	// Seen 0
	/*0132*/	uint32_t	unknown0132;	// Group ID or member level?
	/*0136*/	uint32_t	unknown0136;	// Maybe Voice Chat Channel or Group ID?
	/*0140*/	uint32_t	unknown0140;	// Seen 0
	/*0144*/	uint32_t	unknown0144;	// Seen 0
	/*0148*/	uint32_t	unknown0148;
	/*0152*/
};

struct InspectBuffs_Struct {
	/*000*/ uint32_t spell_id[BUFF_COUNT];
	/*100*/ uint32_t filler100[5];	// BUFF_COUNT is really 30...
	/*120*/ int32_t tics_remaining[BUFF_COUNT];
	/*220*/ uint32_t filler220[5];	// BUFF_COUNT is really 30...
};


struct LFG_Struct {
	/*000*/	uint32_t unknown000;
	/*004*/	uint32_t value; // 0x00 = off 0x01 = on
	/*008*/	uint32_t unknown008;
	/*012*/	uint32_t unknown012;
	/*016*/	char	name[64];
};

struct FaceChange_Struct {
	/*000*/	uint8_t	haircolor;
	/*001*/	uint8_t	beardcolor;
	/*002*/	uint8_t	eyecolor1;
	/*003*/	uint8_t	eyecolor2;
	/*004*/	uint8_t	hairstyle;
	/*005*/	uint8_t	beard;
	/*006*/	uint8_t	face;
	/*007*/ uint8_t	unknown007;
	/*008*/ uint32_t	drakkin_heritage;
	/*012*/ uint32_t	drakkin_tattoo;
	/*016*/ uint32_t	drakkin_details;
	/*020*/ uint32_t	unknown020;
	/*024*/
};
//there are only 10 faces for barbs changing woad just
//increase the face value by ten so if there were 8 woad
//designs then there would be 80 barb faces

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

	/*068*/	uint32_t	wclass;		// FF FF = no class
	/*072*/	uint32_t	lvllow;		// FF FF = no numbers
	/*076*/	uint32_t	lvlhigh;	// FF FF = no numbers
	/*080*/	uint32_t	gmlookup;	// FF FF = not doing /who all gm
	/*084*/	uint32_t	guildid;	// Also used for Buyer/Trader/LFG
	/*088*/	uint8_t	unknown088[64];
	/*156*/	uint32_t	type;		// 0 = /who 3 = /who all
};

struct Stun_Struct { // 8 bytes total
	/*000*/	uint32_t	duration; // Duration of stun
	/*004*/	uint8_t	unknown004; // seen 0
	/*005*/	uint8_t	unknown005; // seen 163
	/*006*/	uint8_t	unknown006; // seen 67
	/*007*/	uint8_t	unknown007; // seen 0
	/*008*/
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
	/*0004*/	char message[1024]; // was 1024
	/*1028*/
};

// Inspect
struct Inspect_Struct {
	uint32_t TargetID;
	uint32_t PlayerID;
};

//OP_InspectAnswer - Size: 1860
struct InspectResponse_Struct{
	/*000*/	uint32_t TargetID;
	/*004*/	uint32_t playerid;
	/*008*/	char itemnames[23][64];
	/*1480*/uint32_t itemicons[23];
	/*1572*/char text[288];	// Max number of chars in Inspect Window appears to be 254
	/*1860*/
};

//OP_SetDataRate
struct SetDataRate_Struct {
	float newdatarate;
};

//OP_SetServerFilter
struct SetServerFilter_Struct {
	uint32_t filters[34];		//see enum eqFilterType [31]
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

// The BookText_Struct is not used in  SoF and later clients.
// The BookRequest_Struct is used instead for both request and reply.
//
struct BookText_Struct {
	uint8_t window;	// where to display the text (0xFF means new window)
	uint8_t type;             //type: 0=scroll, 1=book, 2=item info.. prolly
	char booktext[1]; // Variable Length - was 1
};
// This is the request to read a book.
// This is just a "text file" on the server
// or in our case, the 'name' column in our books table.
struct BookRequest_Struct {
	/*0000*/	uint32_t window;		// where to display the text (0xFFFFFFFF means new window).
	/*0004*/	uint32_t invslot;		// The inventory slot the book is in. Not used, but echoed in the response packet.
	/*0008*/	uint32_t type;		// 0 = Scroll, 1 = Book, 2 = Item Info. Possibly others
	/*0012*/	uint32_t unknown0012;
	/*0016*/	uint16_t unknown0016;
	/*0018*/	char txtfile[8194];
};

/*
** Object/Ground Spawn struct
** Used for Forges, Ovens, ground spawns, items dropped to ground, etc
** Size: 104 bytes
** OpCodes: OP_CreateObject
** Last Updated: Oct-17-2003
**
*/
struct Object_Struct {
	/*00*/	uint32_t	linked_list_addr[2];// They are, get this, prev and next, ala linked list
	/*08*/	uint32_t	unknown008;			// Something related to the linked list?
	/*12*/	uint32_t	drop_id;			// Unique object id for zone
	/*16*/	uint16_t	zone_id;			// Redudant, but: Zone the object appears in
	/*18*/	uint16_t	zone_instance;		//
	/*20*/	uint32_t	unknown020;			// 00 00 00 00
	/*24*/	uint32_t	unknown024;			// 53 9e f9 7e - same for all objects in the zone?
	/*40*/	float	heading;			// heading
	/*32*/	uint8_t	unknown032[8];		// 00 00 00 00 00 00 00 00
	/*28*/	float	size;			// Size - default 1
	/*44*/	float	z;					// z coord
	/*48*/	float	x;					// x coord
	/*52*/	float	y;					// y coord
	/*56*/	char	object_name[32];	// Name of object, usually something like IT63_ACTORDEF was [20]
	/*88*/	uint32_t	unknown088;			// unique ID?  Maybe for a table that includes the contents?
	/*92*/	uint32_t	object_type;		// Type of object, not directly translated to OP_OpenObject
	/*96*/	uint8_t	unknown096[4];		// ff ff ff ff
	/*100*/	uint32_t	spawn_id;			// Spawn Id of client interacting with object
	/*104*/
};
//01 = generic drop, 02 = armor, 19 = weapon
//[13:40] and 0xff seems to be indicative of the tradeskill/openable items that end up returning the old style item type in the OP_OpenObject

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
struct ClickObjectAction_Struct {
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
	/*0052*/ uint32_t   size;			// 100 is normal, smaller number = smaller model
	/*0054*/ uint8_t    unknown0054[4]; // 00 00 00 00
	/*0060*/ uint8_t   doorId;             // door's id #
	/*0061*/ uint8_t   opentype;
	/*0062*/ uint8_t  state_at_spawn;
	/*0063*/ uint8_t  invert_state;	// if this is 1, the door is normally open
	/*0064*/ uint32_t  door_param; // normally ff ff ff ff (-1)
	/*0068*/ uint32_t	unknown0068; // 00 00 00 00
	/*0072*/ uint32_t	unknown0072; // 00 00 00 00
	/*0076*/ uint8_t	unknown0076; // seen 1 or 0
	/*0077*/ uint8_t	unknown0077; // seen 1 (always?)
	/*0078*/ uint8_t	unknown0078; // seen 0 (always?)
	/*0079*/ uint8_t	unknown0079; // seen 1 (always?)
	/*0080*/ uint8_t	unknown0080; // seen 0 (always?)
	/*0081*/ uint8_t	unknown0081; // seen 1 or 0 or rarely 2C or 90 or ED or 2D or A1
	/*0082*/ uint8_t  unknown0082; // seen 0 or rarely FF or FE or 10 or 5A or 82
	/*0083*/ uint8_t  unknown0083; // seen 0 or rarely 02 or 7C
	/*0084*/ uint8_t  unknown0084[8]; // mostly 0s, the last 3 bytes are something tho
	/*0092*/
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
	uint8_t mode;                    //01=run  00=walk
	uint8_t unknown[3];
};

// EnvDamage is EnvDamage2 without a few bytes at the end.
// Size: 37 bytes
struct EnvDamage2_Struct {
	/*0000*/	uint32_t id;
	/*0004*/	uint16_t unknown4;
	/*0006*/	uint32_t damage;
	/*0010*/	float unknown10;	// New to Underfoot - Seen 1
	/*0014*/	uint8_t unknown14[12];
	/*0026*/	uint8_t dmgtype;		// FA = Lava; FC = Falling
	/*0027*/	uint8_t unknown27[4];
	/*0031*/	uint16_t unknown31;	// New to Underfoot - Seen 66
	/*0033*/	uint16_t constant;		// Always FFFF
	/*0035*/	uint16_t unknown35;
	/*0037*/
};

//Bazaar Stuff

enum {
	BazaarTrader_StartTraderMode = 1,
	BazaarTrader_EndTraderMode = 2,
	BazaarTrader_UpdatePrice = 3,
	BazaarTrader_EndTransaction = 4,
	BazaarSearchResults = 7,
	BazaarWelcome = 9,
	BazaarBuyItem = 10,
	BazaarTrader_ShowItems = 11,
	BazaarSearchDone = 12,
	BazaarTrader_CustomerBrowsing = 13
};

enum {
	BazaarPriceChange_Fail = 0,
	BazaarPriceChange_UpdatePrice = 1,
	BazaarPriceChange_RemoveItem = 2,
	BazaarPriceChange_AddItem = 3
};

struct BazaarWindowStart_Struct {
	uint8_t   Action;
	uint8_t   Unknown001;
	uint16_t  Unknown002;
};


struct BazaarWelcome_Struct {
	BazaarWindowStart_Struct Beginning;
	uint32_t  Traders;
	uint32_t  Items;
	uint8_t   Unknown012[8];
};

struct BazaarSearch_Struct {
	BazaarWindowStart_Struct Beginning;
	uint32_t	TraderID;
	uint32_t	Class_;
	uint32_t	Race;
	uint32_t	ItemStat;
	uint32_t	Slot;
	uint32_t	Type;
	char	Name[64];
	uint32_t	MinPrice;
	uint32_t	MaxPrice;
	uint32_t	Minlevel;
	uint32_t	MaxLlevel;
};
struct BazaarInspect_Struct{
	uint32_t ItemID;
	uint32_t Unknown004;
	char Name[64];
};

struct NewBazaarInspect_Struct {
	/*000*/	BazaarWindowStart_Struct Beginning;
	/*004*/	char Name[64];
	/*068*/	uint32_t Unknown068;
	/*072*/	int32_t SerialNumber;
	/*076*/	uint32_t Unknown076;
	/*080*/	uint32_t SellerID;
	/*084*/	uint32_t Unknown084;
};

struct BazaarReturnDone_Struct{
	uint32_t Type;
	uint32_t TraderID;
	uint32_t Unknown008;
	uint32_t Unknown012;
	uint32_t Unknown016;
};

struct BazaarSearchResults_Struct {
	/*000*/	BazaarWindowStart_Struct Beginning;
	/*004*/	uint32_t	SellerID;
	/*008*/	char	SellerName[64];
	/*072*/	uint32_t	NumItems;
	/*076*/	uint32_t	ItemID;
	/*080*/	uint32_t	SerialNumber;
	/*084*/	uint32_t	Unknown084;
	/*088*/	char	ItemName[64];
	/*152*/	uint32_t	Cost;
	/*156*/	uint32_t	ItemStat;
	/*160*/
};

struct ServerSideFilters_Struct {
	uint8_t	clientattackfilters; // 0) No, 1) All (players) but self, 2) All (players) but group
	uint8_t	npcattackfilters;	 // 0) No, 1) Ignore NPC misses (all), 2) Ignore NPC Misses + Attacks (all but self), 3) Ignores NPC Misses + Attacks (all but group)
	uint8_t	clientcastfilters;	 // 0) No, 1) Ignore PC Casts (all), 2) Ignore PC Casts (not directed towards self)
	uint8_t	npccastfilters;		 // 0) No, 1) Ignore NPC Casts (all), 2) Ignore NPC Casts (not directed towards self)
};

/*
** Client requesting item statistics
** Size: 48 bytes
** Used In: OP_ItemLinkClick
** Last Updated: 2/15/2009
**
*/
struct	ItemViewRequest_Struct {
	/*000*/	uint32_t	item_id;
	/*004*/	uint32_t	augments[5];
	/*024*/ uint32_t	link_hash;
	/*028*/	uint32_t	unknown028;	//seems to always be 4 on SoF client
	/*032*/	char	unknown032[12];	//probably includes loregroup & evolving info. see Client::MakeItemLink() in zone/inventory.cpp:469
	/*044*/	uint16_t	icon;
	/*046*/	char	unknown046[2];
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
	/*004*/	uint8_t	enable_pvp;
	/*005*/	uint8_t	unknown005;
	/*006*/	uint8_t	unknown006;
	/*007*/	uint8_t	unknown007;
	/*008*/	uint8_t	enable_FV;
	/*009*/	uint8_t	unknown009;
	/*010*/	uint8_t	unknown010;
	/*011*/	uint8_t	unknown011;
	/*012*/	uint32_t	unknown012;	// htonl(1) on live
	/*016*/	uint32_t	unknown016;	// htonl(1) on live
	/*020*/	uint8_t	unknown020[12];
	/*032*/ uint32_t	unknown032;
	/*036*/	char	worldshortname[32];
	/*068*/	uint8_t	unknown064[32];
	/*100*/	char	unknown096[16];	// 'pacman' on live
	/*116*/	char	unknown112[16];	// '64.37,148,36' on live
	/*132*/	uint8_t	unknown128[48];
	/*180*/	uint32_t	unknown176;	// htonl(0x00002695)
	/*184*/	char	unknown180[80];	// 'eqdataexceptions@mail.station.sony.com' on live
	/*264*/	uint8_t	unknown260;	// 0x01 on live
	/*265*/	uint8_t	enablevoicemacros;
	/*266*/	uint8_t	enablemail;
	/*267*/	uint8_t	unknown263[41];
	/*308*/
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
	uint16_t y;
	uint16_t x;
	uint16_t z;
};

struct Tracking_Struct {
	Track_Struct Entrys[1];
};

// Looks like new tracking structures - Opcode: 0x57a7
struct Tracking_Struct_New {
	uint16_t totalcount;			// Total Count of mobs within tracking range
	Track_Struct Entrys[1];
};

struct Track_Struct_New {
	uint16_t entityid;				// Entity ID
	uint16_t unknown002;			// 00 00
	uint32_t unknown004;			//
	uint8_t  level;				// level of mob
	uint8_t  unknown009;			// 01 maybe type of mob? player/npc?
	char  name[1];				// name of mob
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

// The following four structs are the WhoAllPlayer struct above broken down
// for use in World ClientList::SendFriendsWho to accomodate the user of variable
// length strings within the struct above.

struct	WhoAllPlayerPart1 {
	uint32_t	FormatMSGID;
	uint32_t	Unknown04;
	uint32_t	Unknown08;
	char	Name[1];
};

struct	WhoAllPlayerPart2 {
	uint32_t	RankMSGID;
	char	Guild[1];
};

struct	WhoAllPlayerPart3 {
	uint32_t	Unknown80[2];
	uint32_t	ZoneMSGID;
	uint32_t	Zone;
	uint32_t	Class_;
	uint32_t	Level;
	uint32_t	Race;
	char	Account[1];
};

struct	WhoAllPlayerPart4 {
	uint32_t	Unknown100;
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
	uint32_t id;
	uint32_t code;
};

struct Trader_ShowItems_Struct{
	uint32_t code;
	uint32_t traderid;
	uint32_t unknown08[3];
};

struct TraderBuy_Struct {
	/*000*/ uint32_t   Action;
	/*004*/	uint32_t	Unknown004;
	/*008*/ uint32_t   Price;
	/*012*/	uint32_t	Unknown008;	// Probably high order bits of a 64 bit price.
	/*016*/ uint32_t   TraderID;
	/*020*/ char    ItemName[64];
	/*084*/ uint32_t   Unknown076;
	/*088*/ uint32_t   ItemID;
	/*092*/ uint32_t   AlreadySold;
	/*096*/ uint32_t   Quantity;
	/*100*/ uint32_t   Unknown092;
	/*104*/
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

//struct MoneyUpdate_Struct
//{
//*0000*/ uint32_t spawn_id;            // ***Placeholder
//*0004*/ uint32_t cointype;           // Coin Type
//*0008*/ uint32_t amount;             // Amount
//*0012*/
//};


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
	//*0???*/ uint8_t  unknown0[8];         // ***Placeholder
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
	/*0136*/	char	motd[1]; //was 512
};

struct GuildURL_Struct{
	/*0000*/	uint32_t	unknown0;	//index? seen server send 0 w/ the Guild URL, followed by 1 with nothing.
	/*0004*/	uint32_t	unknown4;
	/*0008*/	uint32_t	unknown8;	//seen 7
	/*0068*/	char	setby_name[64];
	/*0132*/	uint32_t	unknown132;	//seen 0x167
	/*0136*/	char	url[4080];
};

struct GuildMemberUpdate_Struct {
	/*00*/	uint32_t guild_id;
	/*04*/	char	member_name[64];
	/*68*/	uint16_t	zone_id;
	/*70*/	uint16_t	instance_id;
	/*72*/	uint32_t	some_timestamp;
};

struct GuildMemberLevelUpdate_Struct {
	/*00*/	uint32_t guild_id;
	/*04*/	char	member_name[64];
	/*68*/	uint32_t	level;	//not sure
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

struct FindPersonRequest_Struct
{
	/*000*/	uint32_t	unknown000;
	/*004*/	uint32_t	npc_id;
	/*008*/	FindPerson_Point client_pos;
	/*020*/	uint32_t	unknown020;
	/*024*/
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


#if 0
// Old struct not used by Task System implementation but left for reference
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
#endif

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

#if 0
// Old structs not used by Task System implentation but left for reference
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
#endif

struct AcceptNewTask_Struct {
	uint32_t  unknown00;
	uint32_t	task_id;		//set to 0 for 'decline'
	uint32_t	task_master_id;	//entity ID
};

//was all 0's from client, server replied with same op, all 0's
struct CancelTask_Struct {
	uint32_t SequenceNumber;
	uint32_t unknown4; // Only seen 0x00000002
};

#if 0
// old struct, not used by Task System implementation but left for reference.
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
#endif


// Many of the Task System packets contain variable length strings, as well as variable numbers
// of records, hence splitting them into multiple structs (header, middle, trailer) etc.
//
struct AvailableTaskHeader_Struct {
	uint32_t	TaskCount;
	uint32_t	unknown1;
	uint32_t	TaskGiver;
};

struct AvailableTaskData1_Struct {
	uint32_t	TaskID;
	uint32_t	unknown1;
	uint32_t	TimeLimit;
	uint32_t	unknown2;
};

struct AvailableTaskData2_Struct {
	uint32_t	unknown1, unknown2, unknown3, unknown4;
};

struct AvailableTaskTrailer_Struct {
	uint32_t	ItemCount;
	uint32_t	unknown1, unknown2;
	uint32_t	StartZone;
};

struct TaskDescriptionHeader_Struct {
	uint32_t	SequenceNumber; // The order the tasks appear in the journal. 0 for first task, 1 for second, etc.
	uint32_t	TaskID;
	uint32_t	unknown2;
	uint32_t	unknown3;
	uint8_t	unknown4;
};

struct TaskDescriptionData1_Struct {
	uint32_t	Duration;
	uint32_t	unknown2;
	uint32_t	StartTime;
};

struct TaskDescriptionData2_Struct {
	uint32_t	RewardCount; // ??
	uint32_t	unknown1;
	uint32_t	unknown2;
	uint16_t	unknown3;
	//uint8_t	unknown4;
};

struct TaskDescriptionTrailer_Struct {
	//uint16_t  unknown1; // 0x0012
	uint32_t	Points;
};

struct TaskActivityHeader_Struct {
	uint32_t	TaskSequenceNumber;
	uint32_t	unknown2; // Seen 0x00000002
	uint32_t	TaskID;
	uint32_t	ActivityID;
	uint32_t	unknown3;
	uint32_t	ActivityType;
	uint32_t	Optional;
	uint32_t	unknown5;
};

struct TaskActivityData1_Struct {
	uint32_t	GoalCount;
	uint32_t	unknown1; // 0xffffffff
	uint32_t	unknown2; // 0xffffffff
	uint32_t	ZoneID; // seen 0x36
	uint32_t  unknown3;
};

struct TaskActivityTrailer_Struct {
	uint32_t	DoneCount;
	uint32_t	unknown1; // Seen 1
};

// The Short_Struct is sent for tasks that are hidden and act as a placeholder
struct TaskActivityShort_Struct {
	uint32_t	TaskSequenceNumber;
	uint32_t	unknown2; // Seen 0x00000002
	uint32_t	TaskID;
	uint32_t	ActivityID;
	uint32_t	unknown3;
	uint32_t	ActivityType; // 0xffffffff for the short packet
	uint32_t  unknown4;
};

struct TaskActivityComplete_Struct {
	uint32_t	TaskIndex;
	uint32_t	unknown2; // 0x00000002
	uint32_t	unknown3;
	uint32_t	ActivityID;
	uint32_t	unknown4; // 0x00000001
	uint32_t	unknown5; // 0x00000001
};

#if 0
// This is a dupe of the CancelTask struct
struct TaskComplete_Struct {
	uint32_t	unknown00; // 0x00000000
	uint32_t	unknown04; // 0x00000002
};
#endif

struct TaskHistoryRequest_Struct {
	uint32_t	TaskIndex; // This is the sequence the task was sent in the Completed Tasks packet.
};

struct TaskHistoryReplyHeader_Struct {
	uint32_t	TaskID;
	uint32_t	ActivityCount;
};

struct TaskHistoryReplyData1_Struct {
	uint32_t	ActivityType;
};

struct TaskHistoryReplyData2_Struct {
	uint32_t  GoalCount;
	uint32_t	unknown04; // 0xffffffff
	uint32_t	unknown08; // 0xffffffff
	uint32_t	ZoneID;
	uint32_t	unknown16;
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
	/*08*/	uint32_t	unknown08;
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
	/*00*/	uint32_t		action;
	/*04*/	char		player_name[64];
	/*68*/	uint32_t		unknown68;
	/*72*/	char		leader_name[64];
	/*136*/	uint32_t		parameter;
};

struct RaidAddMember_Struct {
	/*000*/ RaidGeneral_Struct raidGen; //param = (group num-1); 0xFFFFFFFF = no group
	/*136*/ uint8_t _class;
	/*137*/	uint8_t level;
	/*138*/	uint8_t isGroupLeader;
	/*139*/	uint8_t flags[5]; //no idea if these are needed...
};

struct RaidMOTD_Struct {
	/*000*/ RaidGeneral_Struct general; // leader_name and action only used
	/*140*/ char motd[1]; // max size 1024, but reply is variable
};

struct RaidLeadershipUpdate_Struct {
	/*000*/	uint32_t action;
	/*004*/	char player_name[64];
	/*068*/	uint32_t Unknown068;
	/*072*/	char leader_name[64];
	/*136*/	GroupLeadershipAA_Struct group; //unneeded
	/*200*/	RaidLeadershipAA_Struct raid;
	/*264*/	char Unknown264[128];
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

// Bandolier actions
enum
{
	bandolierCreate = 0,
	bandolierRemove,
	bandolierSet
};

struct BandolierCreate_Struct
{
	/*00*/	uint32_t Action;		//0 for create
	/*04*/	uint8_t Number;
	/*05*/	char Name[32];
	/*37*/	uint16_t Unknown37;	//seen 0x93FD
	/*39*/	uint8_t Unknown39;	//0
};

struct BandolierDelete_Struct
{
	/*00*/	uint32_t Action;
	/*04*/	uint8_t Number;
	/*05*/	uint8_t Unknown05[35];
};

struct BandolierSet_Struct
{
	/*00*/	uint32_t Action;
	/*04*/	uint8_t Number;
	/*05*/	uint8_t Unknown05[35];
};

// Not 100% sure on this struct. Live as of 1/1/11 is different than UF. Seems to work 'OK'
struct Arrow_Struct
{
	/*000*/	float	src_y;
	/*004*/	float	src_x;
	/*008*/	float	src_z;
	/*012*/	uint8_t	unknown012[12];
	/*024*/	float	velocity;		//4 is normal, 20 is quite fast
	/*028*/	float	launch_angle;	//0-450ish, not sure the units, 140ish is straight
	/*032*/	float	tilt;		//on the order of 125
	/*036*/	uint8_t	unknown036[8];
	/*044*/	float	arc;
	/*048*/	uint32_t	source_id;
	/*052*/	uint32_t	target_id;	//entity ID
	/*056*/	uint32_t	item_id;
	/*060*/	uint8_t	unknown060[10];
	/*070*/	uint8_t	unknown070;
	/*071*/	uint8_t	item_type;
	/*072*/	uint8_t	skill;
	/*073*/	uint8_t	unknown073[13];
	/*086*/	char	model_name[30];
	/*116*/
};

//made a bunch of trivial structs for stuff for opcode finder to use
struct Consent_Struct {
	char name[1];	//always at least a null - was 1
};

struct AdventureMerchant_Struct {
	uint32_t	unknown_flag;		//seems to be 1
	uint32_t	entity_id;
};

struct Save_Struct {
	uint8_t	unknown00[192];
	uint8_t	unknown0192[176];
};

struct GMToggle_Struct {
	uint8_t unknown0[64];
	uint32_t toggle;
};

struct ColoredText_Struct {
	uint32_t color;
	char msg[1]; //was 1
	/*0???*/ uint8_t  paddingXXX[3];          // always 0's
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
	/*16*/
};

struct SendAA_Struct {
	/*0000*/	uint32_t id;
	/*0004*/	uint8_t unknown004;		// uint32_t unknown004; set to 1.
	/*0005*/	uint32_t hotkey_sid;
	/*0009*/	uint32_t hotkey_sid2;
	/*0013*/	uint32_t title_sid;
	/*0017*/	uint32_t desc_sid;
	/*0021*/	uint32_t class_type;
	/*0025*/	uint32_t cost;
	/*0029*/	uint32_t seq;
	/*0033*/	uint32_t current_level; //1s, MQ2 calls this AARankRequired
	/*0037*/	uint32_t prereq_skill;		//is < 0, abs() is category #
	/*0041*/	uint32_t prereq_minpoints; //min points in the prereq
	/*0045*/	uint32_t type;
	/*0049*/	uint32_t spellid;
	/*0053*/	uint32_t spell_type;
	/*0057*/	uint32_t spell_refresh;
	/*0061*/	uint16_t classes;
	/*0063*/	uint16_t berserker; //seems to be 1 if its a berserker ability
	/*0065*/	uint32_t max_level;
	/*0069*/	uint32_t last_id;
	/*0073*/	uint32_t next_id;
	/*0077*/	uint32_t cost2;
	/*0081*/	uint8_t unknown81;
	/*0082*/	uint8_t grant_only; // VetAAs, progression, etc
	/*0083*/	uint8_t unknown83; // 1 for skill cap increase AAs, Mystical Attuning, and RNG attack inc, doesn't seem to matter though
	/*0084*/	uint32_t expendable_charges; // max charges of the AA
	/*0088*/	uint32_t aa_expansion;
	/*0092*/	uint32_t special_category;
	/*0096*/	uint8_t shroud;
	/*0097*/	uint8_t unknown97;
	/*0098*/	uint8_t layonhands; // 1 for lay on hands -- doesn't seem to matter?
	/*0099*/	uint8_t unknown99;
	/*0100*/	uint32_t total_abilities;
	/*0104*/	AA_Ability abilities[1];
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


struct AAExpUpdate_Struct {
	/*00*/	uint32_t unknown00;	//seems to be a value from AA_Action.ability
	/*04*/	uint32_t aapoints_unspent;
	/*08*/	uint8_t aaxp_percent;	//% of exp that goes to AAs
	/*09*/	uint8_t unknown09[3];	//live doesn't always zero these, so they arnt part of aaxp_percent
};


struct AltAdvStats_Struct {
	/*000*/  uint32_t experience;
	/*004*/  uint16_t unspent;
	/*006*/  uint16_t	unknown006;
	/*008*/  uint8_t	percentage;
	/*009*/  uint8_t	unknown009[3];
};

struct PlayerAA_Struct {						// Is this still used?
	AA_Array aa_list[MAX_PP_AA_ARRAY];
};

struct AATable_Struct {
	/*00*/ int32_t	aa_spent;	// Total AAs Spent
	/*04*/ int32_t	aa_assigned;	// Assigned: field in the AA window.
	/*08*/ int32_t	aa_spent3;	// Unknown. Same as aa_spent in observed packets.
	/*12*/ int32_t	unknown012;
	/*16*/ int32_t	unknown016;
	/*20*/ int32_t	unknown020;
	/*24*/ AA_Array aa_list[MAX_PP_AA_ARRAY];
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

struct LoadSpellSet_Struct {
	uint8_t  spell[MAX_PP_MEMSPELL];      // 0 if no action
	uint16_t unknown2;	// is this two more spell gems?
	uint32_t unknown;	// there seems to be an extra field in this packet...
};

struct BlockedBuffs_Struct {
	/*000*/	uint8_t	unknown000[80];
	/*080*/	uint8_t	unknown081;
	/*081*/	uint8_t	unknown082;
	/*082*/	uint8_t	unknown083;
	/*083*/	uint8_t	unknown084;
	/*084*/	uint8_t	unknown085;
	/*085*/	uint8_t	unknown086;
	/*086*/	uint8_t	unknown087;
	/*087*/	uint8_t	unknown088;
	/*088*/
};

//Size 24 Bytes
struct WorldObfuscator_Struct
{
	/*000*/ uint32_t var1;
	/*004*/ uint32_t Unknown1;
	/*008*/ uint32_t Unknown2;
	/*012*/ uint32_t Unknown3;
	/*016*/ uint32_t var2;
	/*020*/ uint32_t Unknown4;
	/*024*/
};

struct ExpansionInfo_Struct {
	/*000*/	char	Unknown000[64];
	/*064*/	uint32_t	Expansions;
};

struct ApplyPoison_Struct {
	uint32_t inventorySlot;
	uint32_t success;
};

struct ItemVerifyRequest_Struct {
	/*000*/	int32_t	slot;		// Slot being Right Clicked
	/*004*/	uint32_t	target;		// Target Entity ID
	/*008*/
};

struct ItemVerifyReply_Struct {
	/*000*/	int32_t	slot;		// Slot being Right Clicked
	/*004*/	uint32_t	spell;		// Spell ID to cast if different than item effect
	/*008*/	uint32_t	target;		// Target Entity ID
	/*012*/
};

struct ItemSerializationHeader
{
	/*000*/	uint32_t stacksize;
	/*004*/	uint32_t unknown004;
	/*008*/	uint32_t slot;
	/*012*/	uint32_t price;
	/*016*/	uint32_t merchant_slot; //1 if not a merchant item
	/*020*/	uint32_t scaled_value; //0
	/*024*/	uint32_t instance_id; //unique instance id if not merchant item, else is merchant slot
	/*028*/	uint32_t unknown028; //0
	/*032*/	uint32_t last_cast_time;	// Unix Time from PP of last cast for this recast type if recast delay > 0
	/*036*/	uint32_t charges; //Total Charges an item has (-1 for unlimited)
	/*040*/	uint32_t inst_nodrop; // 1 if the item is no drop (attuned items)
	/*044*/	uint32_t unknown044; //0
	/*048*/	uint32_t unknown048; //0
	/*052*/	uint32_t unknown052; //0
	/*056*/ uint8_t isEvolving; //0 // If 1 Add evolving item data in between Header and HeaderFinish
};

struct EvolvingItem {
	uint8_t unknown001;
	uint8_t unknown002;
	uint8_t unknown003;
	uint8_t unknown004;
	int32_t evoLevel;
	double progress;
	uint8_t Activated;
	int32_t evomaxlevel;
	uint8_t unknown02[4];
};

struct ItemSerializationHeaderFinish
{
	uint16_t ornamentIcon;
	/*060*/	uint8_t unknown060; //0
	/*061*/	uint8_t unknown061; //0 - 
	/*062*/	uint8_t isCopied; // New to Underfoot // Copied flag on item
	/*063*/	uint8_t ItemClass; //0, 1, or 2
};

struct ItemBodyStruct
{
	uint32_t id;
	uint8_t weight;
	uint8_t norent;
	uint8_t nodrop;
	uint8_t attune;
	uint8_t size;
	uint32_t slots;
	uint32_t price;
	uint32_t icon;
	uint8_t unknown1;
	uint8_t unknown2;
	uint32_t BenefitFlag;
	uint8_t tradeskills;
	int8_t CR;
	int8_t DR;
	int8_t PR;
	int8_t MR;
	int8_t FR;
	int8_t SVCorruption;
	int8_t AStr;
	int8_t ASta;
	int8_t AAgi;
	int8_t ADex;
	int8_t ACha;
	int8_t AInt;
	int8_t AWis;
	int32_t HP;
	int32_t Mana;
	uint32_t Endur;
	int32_t AC;
	int32_t regen;
	int32_t mana_regen;
	int32_t end_regen;
	uint32_t Classes;
	uint32_t Races;
	uint32_t Deity;
	int32_t SkillModValue;
	uint32_t unknown5;
	uint32_t SkillModType;
	uint32_t BaneDmgRace;
	uint32_t BaneDmgBody;
	uint32_t BaneDmgRaceAmt;
	int32_t BaneDmgAmt;
	uint8_t Magic;
	int32_t CastTime_;
	uint32_t ReqLevel;
	uint32_t RecLevel;
	uint32_t RecSkill;
	uint32_t BardType;
	int32_t BardValue;
	uint8_t Light;
	uint8_t Delay;
	uint8_t ElemDmgType;
	uint8_t ElemDmgAmt;
	uint8_t Range;
	uint32_t Damage;
	uint32_t Color;
	uint8_t ItemType;
	uint32_t Material;
	uint32_t unknown7;
	uint32_t EliteMaterial;
	float SellRate;
	int32_t CombatEffects;
	int32_t Shielding;
	int32_t StunResist;
	int32_t StrikeThrough;
	int32_t ExtraDmgSkill;
	int32_t ExtraDmgAmt;
	int32_t SpellShield;
	int32_t Avoidance;
	int32_t Accuracy;
	uint32_t CharmFileID; //not sure the point of this; disables all stats on item if > 0
	uint32_t	FactionMod1;
	int32_t	FactionAmt1;
	uint32_t	FactionMod2;
	int32_t	FactionAmt2;
	uint32_t  FactionMod3;
	int32_t	FactionAmt3;
	uint32_t  FactionMod4;
	int32_t	FactionAmt4;
};

struct AugSlotStruct
{
	uint32_t type;
	uint8_t visible;
	uint8_t unknown;
};

struct ItemTertiaryBodyStruct
{
	int32_t loregroup;
	uint8_t artifact;
	uint8_t summonedflag;
	uint32_t favor;
	uint8_t fvnodrop;
	int32_t dotshield;
	int32_t atk;
	int32_t haste;
	int32_t damage_shield;
	uint32_t guildfavor;
	uint32_t augdistil;
	int32_t unknown3;
	uint32_t unknown4;
	uint8_t no_pet;
	uint8_t unknown5;

	uint8_t potion_belt_enabled;
	uint32_t potion_belt_slots;

	uint32_t stacksize;
	uint8_t no_transfer;
	uint16_t expendablearrow;

	uint32_t unknown8;
	uint32_t unknown9;
	uint32_t unknown10;
	uint32_t unknown11;
	uint8_t unknown12;
	uint8_t unknown13;
	uint8_t unknown14;
};

struct ClickEffectStruct
{
	int32_t effect;
	uint8_t level2;
	uint32_t type;
	uint8_t level;
	int32_t max_charges;
	int32_t cast_time;
	uint32_t recast;
	int32_t recast_type;
	uint32_t clickunk5;
	//uint8_t effect_string; //unused
	//int32_t clickunk7;
};

struct ProcEffectStruct
{
	uint32_t effect;
	uint8_t level2;
	uint32_t type;
	uint8_t level;
	uint32_t unknown1; // poison?
	uint32_t unknown2;
	uint32_t unknown3;
	uint32_t unknown4;
	uint32_t procrate;
	//uint8_t effect_string;
	//uint32_t unknown5;
};

struct WornEffectStruct //worn, focus and scroll effect
{
	uint32_t effect;
	uint8_t level2;
	uint32_t type;
	uint8_t level;
	uint32_t unknown1;
	uint32_t unknown2;
	uint32_t unknown3;
	uint32_t unknown4;
	uint32_t unknown5;
	//uint8_t effect_string;
	//uint32_t unknown6;
};


struct ItemSecondaryBodyStruct{
	uint32_t augtype;
	uint32_t augrestrict;
	AugSlotStruct augslots[5];

	uint32_t ldonpoint_type;
	uint32_t ldontheme;
	uint32_t ldonprice;
	uint32_t ldonsellbackrate;
	uint32_t ldonsold;

	uint8_t bagtype;
	uint8_t bagslots;
	uint8_t bagsize;
	uint8_t wreduction;

	uint8_t book;
	uint8_t booktype;
	//int32_t filename; filename is either 0xffffffff/0x00000000 or the null term string ex: CREWizardNote\0
};

struct ItemQuaternaryBodyStruct
{

	uint32_t scriptfileid;
	uint8_t quest_item;
	uint32_t unknown15; //0xffffffff - Power Source Capacity?
	uint32_t Purity;
	uint32_t BackstabDmg;
	uint32_t DSMitigation;
	int32_t HeroicStr;
	int32_t HeroicInt;
	int32_t HeroicWis;
	int32_t HeroicAgi;
	int32_t HeroicDex;
	int32_t HeroicSta;
	int32_t HeroicCha;
	int32_t HeroicMR;
	int32_t HeroicFR;
	int32_t HeroicCR;
	int32_t HeroicDR;
	int32_t HeroicPR;
	int32_t HeroicSVCorrup;
	int32_t HealAmt;
	int32_t SpellDmg;
	int32_t clairvoyance;
	uint8_t unknown18;	//Power Source Capacity or evolve filename?
	uint32_t evolve_string; // Some String, but being evolution related is just a guess
	uint8_t unknown19;
	uint32_t unknown20;	// Bard Stuff?
	uint32_t unknown21;
	uint32_t unknown22;
	uint32_t subitem_count;
};

struct AugmentInfo_Struct
{
	/*000*/ uint32_t	itemid;			// id of the solvent needed
	/*004*/ uint32_t	window;			// window to display the information in
	/*008*/ char	augment_info[64];	// total packet length 76, all the rest were always 00
	/*072*/ uint32_t	unknown072;
};

struct VeteranRewardItem
{
	/*000*/	uint32_t item_id;
	/*004*/	uint32_t charges;
	/*008*/	char item_name[64];
};

struct VeteranReward
{
	/*000*/	uint32_t claim_id;
	/*004*/	uint32_t number_available;
	/*008*/	uint32_t claim_count;
	/*012*/	VeteranRewardItem items[8];
};

struct ExpeditionEntryHeader_Struct
{
	/*000*/ uint32_t unknown000;
	/*000*/ uint32_t number_of_entries;
};

struct ExpeditionJoinPrompt_Struct
{
	/*000*/ uint32_t clientid;
	/*004*/ uint32_t unknown004;
	/*008*/ char player_name[64];
	/*072*/ char expedition_name[64];
};

struct ExpeditionExpireWarning
{
	/*000*/ uint32_t clientid;
	/*004*/ uint32_t unknown004;
	/*008*/ uint32_t minutes_remaining;
};

struct ExpeditionInfo_Struct
{
	/*000*/ uint32_t clientid;
	/*004*/ uint32_t unknown004;
	/*008*/ uint32_t unknown008;
	/*012*/ uint32_t max_players;
	/*016*/ char expedition_name[128];
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

struct AltCurrencySelectItem_Struct {
	uint32_t merchant_entity_id;
	uint32_t slot_id;
	uint32_t unknown008;
	uint32_t unknown012;
	uint32_t unknown016;
	uint32_t unknown020;
	uint32_t unknown024;
	uint32_t unknown028;
	uint32_t unknown032;
	uint32_t unknown036;
	uint32_t unknown040;
	uint32_t unknown044;
	uint32_t unknown048;
	uint32_t unknown052;
	uint32_t unknown056;
	uint32_t unknown060;
	uint32_t unknown064;
	uint32_t unknown068;
	uint32_t unknown072;
	uint32_t unknown076;
};

struct AltCurrencySellItem_Struct {
	/*000*/ uint32_t merchant_entity_id;
	/*004*/ uint32_t slot_id;
	/*008*/ uint32_t charges;
	/*012*/ uint32_t cost;
};

struct AltCurrencyPopulateEntry_Struct
{
	/*000*/ uint32_t currency_number; //corresponds to a dbstr id as well, the string matches what shows up in the "alternate currency" tab.
	/*004*/ uint32_t unknown00; //always 1
	/*008*/ uint32_t currency_number2; //always same as currency number
	/*012*/ uint32_t item_id; //appears to be the item id
	/*016*/ uint32_t item_icon; //actual icon
	/*020*/ uint32_t stack_size; //most are set to 1000, the stack size for the item; should match db i think or there will be problems.
	/*024*/ uint8_t  unknown024; //seen 0 and 1
};

struct AltCurrencyPopulate_Struct {
	/*000*/ uint32_t opcode; //8 for populate
	/*004*/ uint32_t count; //number of entries
	/*008*/ AltCurrencyPopulateEntry_Struct entries[1];
};

// Used by MercenaryListEntry_Struct
struct MercenaryStance_Struct {
	/*0000*/	uint32_t	StanceIndex;	// Index of this stance (sometimes reverse reverse order - 3, 2, 1, 0 for 4 stances etc)
	/*0004*/	uint32_t	Stance;			// From dbstr_us.txt - 1^24^Passive^0, 2^24^Balanced^0, etc (1 to 9 as of April 2012)
};

// Used by MercenaryMerchantList_Struct
struct MercenaryListEntry_Struct {
	/*0000*/	uint32_t	MercID;				// ID unique to each type of mercenary (probably a DB id)
	/*0004*/	uint32_t	MercType;			// From dbstr_us.txt - Apprentice (330000100), Journeyman (330000200), Master (330000300)
	/*0008*/	uint32_t	MercSubType;		// From dbstr_us.txt - 330020105^23^Race: Guktan<br>Type: Healer<br>Confidence: High<br>Proficiency: Apprentice, Tier V...
	/*0012*/	uint32_t	PurchaseCost;		// Purchase Cost (in gold)
	/*0016*/	uint32_t	UpkeepCost;			// Upkeep Cost (in gold)
	/*0020*/	uint32_t	AltCurrencyCost;	// Alternate Currency Purchase Cost? (all seen costs show N/A Bayle Mark) - Seen 0
	/*0024*/	uint32_t	AltCurrencyUpkeep;	// Alternate Currency Upkeep Cost? (all seen costs show 1 Bayle Mark) - Seen 1
	/*0028*/	uint32_t	AltCurrencyType;	// Alternate Currency Type? - 19^17^Bayle Mark^0 - Seen 19
	/*0032*/	uint8_t	MercUnk01;			// Unknown (always see 0)
	/*0033*/	int32_t	TimeLeft;			// Unknown (always see -1 at merchant) - Seen 900000 (15 minutes in ms for newly hired merc)
	/*0037*/	uint32_t	MerchantSlot;		// Merchant Slot? Increments, but not always by 1 - May be for Merc Window Options (Seen 5, 36, 1 for active mercs)?
	/*0041*/	uint32_t	MercUnk02;			// Unknown (normally see 1, but sometimes 2 or 0)
	/*0045*/	uint32_t	StanceCount;		// Iterations of MercenaryStance_Struct - Normally 2 to 4 seen
	/*0049*/	int32_t	MercUnk03;			// Unknown (always 0 at merchant) - Seen on active merc: 93 a4 03 77, b8 ed 2f 26, 88 d5 8b c3, and 93 a4 ad 77
	/*0053*/	uint8_t	MercUnk04;			// Seen 1
	/*0054*/	MercenaryStance_Struct Stances[1];	// Count Varies, but hard set to 2 for now - From dbstr_us.txt - 1^24^Passive^0, 2^24^Balanced^0, etc (1 to 9 as of April 2012)
};

// [OPCode: 0x27ac OP_MercenaryDataResponse] On Live as of April 2 2012 [Server->Client]
// Opcode should be renamed to something like OP_MercenaryMerchantShopResponse since the Data Response packet is different
// Sent by the server when browsing the Mercenary Merchant
struct MercenaryMerchantList_Struct {
	/*0000*/	uint32_t	MercTypeCount;			// Number of Merc Types to follow
	/*0004*/	uint32_t	MercTypes[1];			// Count varies, but hard set to 3 for now - From dbstr_us.txt - Apprentice (330000100), Journeyman (330000200), Master (330000300)
	/*0016*/	uint32_t	MercCount;				// Number of MercenaryInfo_Struct to follow
	/*0020*/	MercenaryListEntry_Struct Mercs[1];	// Data for individual mercenaries in the Merchant List
};

// [OPCode: 0x4dd9 OP_MercenaryDataRequest] On Live as of April 2 2012 [Client->Server]
// Opcode should be renamed to something like OP_MercenaryMerchantShopRequest since the Data Request packet is different
// Right clicking merchant - shop request
struct MercenaryMerchantShopRequest_Struct {
	/*0000*/	uint32_t	MercMerchantID;			// Entity ID of the Mercenary Merchant
	/*0004*/
};

// Used by MercenaryDataUpdate_Struct
struct MercenaryData_Struct {
	/*0000*/	uint32_t	MercID;				// ID unique to each type of mercenary (probably a DB id)
	/*0004*/	uint32_t	MercType;			// From dbstr_us.txt - Apprentice (330000100), Journeyman (330000200), Master (330000300)
	/*0008*/	uint32_t	MercSubType;		// From dbstr_us.txt - 330020105^23^Race: Guktan<br>Type: Healer<br>Confidence: High<br>Proficiency: Apprentice, Tier V...
	/*0012*/	uint32_t	PurchaseCost;		// Purchase Cost (in gold)
	/*0016*/	uint32_t	UpkeepCost;			// Upkeep Cost (in gold)
	/*0020*/	uint32_t	AltCurrencyCost;	// Alternate Currency Purchase Cost? (all seen costs show N/A Bayle Mark) - Seen 0
	/*0024*/	uint32_t	AltCurrencyUpkeep;	// Alternate Currency Upkeep Cost? (all seen costs show 1 Bayle Mark) - Seen 1
	/*0028*/	uint32_t	AltCurrencyType;	// Alternate Currency Type? - 19^17^Bayle Mark^0 - Seen 19
	/*0032*/	uint8_t	MercUnk01;			// Unknown (always see 0)
	/*0033*/	int32_t	TimeLeft;			// Unknown (always see -1 at merchant) - Seen 900000 (15 minutes in ms for newly hired merc)
	/*0037*/	uint32_t	MerchantSlot;		// Merchant Slot? Increments, but not always by 1 - May be for Merc Window Options (Seen 5, 36, 1 for active mercs)?
	/*0041*/	uint32_t	MercUnk02;			// Unknown (normally see 1, but sometimes 2 or 0)
	/*0045*/	uint32_t	StanceCount;		// Iterations of MercenaryStance_Struct - Normally 2 to 4 seen
	/*0049*/	int32_t	MercUnk03;			// Unknown (always 0 at merchant) - Seen on active merc: 93 a4 03 77, b8 ed 2f 26, 88 d5 8b c3, and 93 a4 ad 77
	/*0053*/	uint8_t	MercUnk04;			// Seen 1
	/*0054*/	MercenaryStance_Struct Stances[1];	// Count Varies, but hard set to 2 for now - From dbstr_us.txt - 1^24^Passive^0, 2^24^Balanced^0, etc (1 to 9 as of April 2012)
	/*0000*/	uint32_t	MercUnk05;			// Seen 1 - Extra Merc Data field that differs from MercenaryListEntry_Struct
	// MercUnk05 may be a field that is at the end of the packet only, even if multiple mercs are listed (haven't seen examples of multiple mercs owned at once)
};

// [OPCode: 0x6537] On Live as of April 2 2012 [Server->Client]
// Should be named OP_MercenaryDataResponse, but the current opcode using that name should be renamed first
// Size varies if mercenary is hired or if browsing Mercenary Merchant
// This may also be the response for Client->Server 0x0327 (size 0) packet On Live as of April 2 2012
struct MercenaryDataUpdate_Struct {
	/*0000*/	int32_t	MercStatus;					// Seen 0 with merc and -1 with no merc hired
	/*0004*/	uint32_t	MercCount;					// Seen 1 with 1 merc hired and 0 with no merc hired
	/*0008*/	MercenaryData_Struct MercData[1];	// Data for individual mercenaries in the Merchant List
};

// [OPCode: 0x6537] On Live as of April 2 2012 [Server->Client]
// Size 12 and sent on Zone-In if no mercenary is currently hired and when merc is dismissed
// (Same packet as MercAssign_Struct?)
struct NoMercenaryHired_Struct {
	/*0000*/	int32_t	MercStatus;			// Seen -1 with no merc hired
	/*0004*/	uint32_t	MercCount;			// Seen 0 with no merc hired
	/*0008*/	uint32_t	MercID;				// Seen 1 when no merc is hired - ID unique to each type of mercenary
	/*0012*/
};

// [OPCode: 0x495d OP_MercenaryTimer] On Live as of April 2 2012 [Server->Client] [Size: 20]
// Sent on Zone-In, or after Dismissing, Suspending, or Unsuspending Mercs
struct MercenaryStatus_Struct {
	/*0000*/	uint32_t	MercEntityID;	// Seen 0 (no merc spawned) or 615843841 and 22779137
	/*0004*/	uint32_t	UpdateInterval;	// Seen 900000 - Matches from 0x6537 packet (15 minutes in ms?)
	/*0008*/	uint32_t	MercUnk01;		// Seen 180000 - 3 minutes in milleseconds? Maybe next update interval?
	/*0012*/	uint32_t	MercState;		// Seen 5 (normal) or 1 (suspended)
	/*0016*/	uint32_t	SuspendedTime;	// Seen 0 (not suspended) or c9 c2 64 4f (suspended on Sat Mar 17 11:58:49 2012) - Unix Timestamp
	/*0020*/
};

// [OPCode: 0x4c6c] On Live as of April 2 2012 [Client->Server] [Size: 8]
// Sent from the client when using the Mercenary Window
struct MercenaryCommand_Struct {
	/*0000*/	uint32_t	MercCommand;	// Seen 0 (zone in with no merc or suspended), 1 (dismiss merc), 5 (normal state), 36 (zone in with merc)
	/*0004*/	int32_t	Option;			// Seen -1 (zone in with no merc), 0 (setting to passive stance), 1 (normal or setting to balanced stance)
	/*0008*/
};

// [OPCode: 0x1a79] On Live as of April 2 2012 [Client->Server] [Size: 1]
// Requesting to suspend or unsuspend merc
struct SuspendMercenary_Struct {
	/*0000*/	uint8_t	SuspendMerc;	// Seen 30 (48) for suspending or unsuspending
	/*0001*/
};

// [OPCode: 0x2528] On Live as of April 2 2012 [Server->Client] [Size: 4]
// Response to suspend merc with timestamp
struct SuspendMercenaryResponse_Struct {
	/*0000*/	uint32_t	SuspendTime;	// Unix Timestamp - Seen a9 11 78 4f
	/*0004*/
};

// [OPCode: 0x5e78 (OP_MercenaryHire?)] On Live as of April 2 2012
// Sent by client when requesting to view Mercenary info or Hire a Mercenary
struct MercenaryMerchantRequest_Struct {
	/*0000*/	uint32_t	RequestType;	// Seen 399 for a Hire Request and 400 for a view merc info request? (may actually be merc ID)
	/*0004*/	uint32_t	MercUnk01;		// Seen 1
	/*0008*/	uint32_t	MercMerchantID;	// Entity ID for Mercenary Merchant
	/*0012*/	uint32_t	MercUnk02;		// Seen 65302016 (00 6e e4 03) - (probably actually individual uint8_t fields)
	/*0016*/
};

// [OPCode: 0x5e78 (OP_MercenaryHire?)] On Live as of April 2 2012
// Sent by Server in response to requesting to view Mercenary info or Hire a Mercenary
struct MercenaryMerchantResponse_Struct {
	/*0000*/	uint32_t	ResponseType;	// Seen 0 for hire response, 6 for info response, and 9 for denied hire request
	/*0004*/
};

// (Same packet as NoMercenaryHired_Struct?)
struct MercenaryAssign_Struct {
	/*0000*/	uint32_t	MercEntityID;	// Seen 0 (no merc spawned) or 615843841 and 22779137
	/*0004*/	uint32_t	MercUnk01;		//
	/*0008*/	uint32_t	MercUnk02;		//
	/*0012*/
};

}

#endif //_EQNET_STRUCTS_UNDERFOOT_H_
