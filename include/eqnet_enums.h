
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
	EQNET_SKILL_SenseHeading,
	EQNET_SKILL_RangedAttack,
	EQNET_SKILL_Kick,
	EQNET_SKILL_Slam,
	EQNET_SKILL_Taunt,
	EQNET_SKILL_Backstab,
	EQNET_SKILL_FeignDeath,
	EQNET_SKILL_Forage,
	EQNET_SKILL_Hide,
	EQNET_SKILL_Sneak,
	EQNET_SKILL_Mend
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
