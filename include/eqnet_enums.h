
#ifndef _EQNET_ENUMS_H_
#define _EQNET_ENUMS_H_

enum EQNet_EventType
{
	EQNET_EVENT_FatalError,
	EQNET_EVENT_Error,
	/* Connection */
	EQNET_EVENT_Timeout,
	EQNET_EVENT_Disconnected,
	/* Login */
	EQNET_EVENT_BadCredentials,
	EQNET_EVENT_AtServerSelect,
	EQNET_EVENT_LoginToWorld,
	/* World */
	EQNET_EVENT_WorldConnectFailed,
	EQNET_EVENT_AtCharacterSelect,
	/* Zone */
	EQNET_EVENT_Zoning,
	EQNET_EVENT_ZoneUnavailable,
	EQNET_EVENT_Packet,
	EQNET_EVENT_AtZone
};

enum EQNet_ClientVersion
{
	EQNET_CLIENT_Titanium,
	EQNET_CLIENT_SecretsOfFaydwer,
	EQNET_CLIENT_SeedsOfDestruction,
	EQNET_CLIENT_Underfoot,
	EQNET_CLIENT_ReignOfFear,
	EQNET_CLIENT_ReignOfFear2
};

enum EQNet_Skill
{
	EQNET_SKILL_1HBlunt,
	EQNET_SKILL_1HSlashing,
	EQNET_SKILL_2HBlunt,
	EQNET_SKILL_2HSlashing,
	EQNET_SKILL_Abjuration,
	EQNET_SKILL_Alteration,
	EQNET_SKILL_ApplyPoison,
	EQNET_SKILL_Archery,
	EQNET_SKILL_Backstab,
	EQNET_SKILL_BindWound,
	EQNET_SKILL_Bash,
	EQNET_SKILL_Block,
	EQNET_SKILL_BrassInstruments,
	EQNET_SKILL_Channeling,
	EQNET_SKILL_Conjuration,
	EQNET_SKILL_Defense,
	EQNET_SKILL_Disarm,
	EQNET_SKILL_DisarmTraps,
	EQNET_SKILL_Divination,
	EQNET_SKILL_Dodge,
	EQNET_SKILL_DoubleAttack,
	EQNET_SKILL_DragonPunch,
	EQNET_SKILL_DualWield,
	EQNET_SKILL_EagleStrike,
	EQNET_SKILL_Evocation,
	EQNET_SKILL_FeignDeath,
	EQNET_SKILL_FlyingKick,
	EQNET_SKILL_Forage,
	EQNET_SKILL_HandtoHand,
	EQNET_SKILL_Hide,
	EQNET_SKILL_Kick,
	EQNET_SKILL_Meditate,
	EQNET_SKILL_Mend,
	EQNET_SKILL_Offense,
	EQNET_SKILL_Parry,
	EQNET_SKILL_PickLock,
	EQNET_SKILL_1HPiercing,
	EQNET_SKILL_Riposte,
	EQNET_SKILL_RoundKick,
	EQNET_SKILL_SafeFall,
	EQNET_SKILL_SenseHeading,
	EQNET_SKILL_Singing,
	EQNET_SKILL_Sneak,
	EQNET_SKILL_SpecializeAbjuration,
	EQNET_SKILL_SpecializeAlteration,
	EQNET_SKILL_SpecializeConjuration,
	EQNET_SKILL_SpecializeDivination,
	EQNET_SKILL_SpecializeEvocation,
	EQNET_SKILL_PickPockets,
	EQNET_SKILL_StringedInstruments,
	EQNET_SKILL_Swimming,
	EQNET_SKILL_Throwing,
	EQNET_SKILL_TigerClaw,
	EQNET_SKILL_Tracking,
	EQNET_SKILL_WindInstruments,
	EQNET_SKILL_Fishing,
	EQNET_SKILL_MakePoison,
	EQNET_SKILL_Tinkering,
	EQNET_SKILL_Research,
	EQNET_SKILL_Alchemy,
	EQNET_SKILL_Baking,
	EQNET_SKILL_Tailoring,
	EQNET_SKILL_SenseTraps,
	EQNET_SKILL_Blacksmithing,
	EQNET_SKILL_Fletching,
	EQNET_SKILL_Brewing,
	EQNET_SKILL_AlcoholTolerance,
	EQNET_SKILL_Begging,
	EQNET_SKILL_JewelryMaking,
	EQNET_SKILL_Pottery,
	EQNET_SKILL_PercussionInstruments,
	EQNET_SKILL_Intimidation,
	EQNET_SKILL_Berserking,
	EQNET_SKILL_Taunt,
	EQNET_SKILL_Frenzy,
	EQNET_SKILL_MAX_COUNT
};
#define EQNET_SKILL_TailRake EQNET_SKILL_DragonPunch
#define EQNET_SKILL_Slam EQNET_SKILL_Bash

enum EQNet_ChatChannel
{
	EQNET_CHAT_Guild,
	EQNET_CHAT_Group = 2,
	EQNET_CHAT_Shout,
	EQNET_CHAT_Auction,
	EQNET_CHAT_OutOfCharacter,
	EQNET_CHAT_Broadcast,
	EQNET_CHAT_Tell,
	EQNET_CHAT_Say,
	EQNET_CHAT_GmSay = 11,
	EQNET_CHAT_Raid = 15,
	EQNET_CHAT_Emote = 22
};

enum EQNet_Slot
{
	EQNET_SLOT_Head,
	EQNET_SLOT_Chest,
	EQNET_SLOT_Primary,
	EQNET_SLOT_Secondary,
	EQNET_SLOT_Range
};

enum EQNet_FactionCon
{
	EQNET_CON_Scowls,
	EQNET_CON_Threateningly,
	EQNET_CON_Dubious,
	EQNET_CON_Apprehensive,
	EQNET_CON_Indifferent,
	EQNET_CON_Amiable,
	EQNET_CON_Warmly,
	EQNET_CON_Ally
};

enum EQNet_LevelCon
{
	EQNET_CON_Grey,
	EQNET_CON_Green,
	EQNET_CON_LightBlue,
	EQNET_CON_Blue,
	EQNET_CON_White,
	EQNET_CON_Yellow,
	EQNET_CON_Red
};

#endif/*EQNET_ENUMS_H_*/
