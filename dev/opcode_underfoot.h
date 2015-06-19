
#ifndef _EQNET_OPCODES_UNDERFOOT_H_
#define _EQNET_OPCODES_UNDERFOOT_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace Underfoot
{
	static const OpCodeTranslation toCanonical[] = {
		{ 0x13da, EQNET_OP_SendLoginInfo },
		{ 0x86c7, EQNET_OP_ApproveWorld },
		{ 0x6f79, EQNET_OP_LogServer },
		{ 0x4200, EQNET_OP_SendCharInfo },
		{ 0x7e4d, EQNET_OP_ExpansionInfo },
		{ 0x5b0b, EQNET_OP_GuildsList },
		{ 0x51b9, EQNET_OP_EnterWorld },
		{ 0x5d32, EQNET_OP_PostEnterWorld },
		{ 0x46d3, EQNET_OP_SendSpellChecksum },
		{ 0x040b, EQNET_OP_SendSkillCapsChecksum },
		{ 0x5ca5, EQNET_OP_DeleteCharacter },
		{ 0x53a3, EQNET_OP_CharacterCreateRequest },
		{ 0x1b85, EQNET_OP_CharacterCreate },
		{ 0x647a, EQNET_OP_RandomNameGenerator },
		{ 0x4f1f, EQNET_OP_ApproveName },
		{ 0x7629, EQNET_OP_MessageOfTheDay },
		{ 0x7d90, EQNET_OP_SetChatServer },
		{ 0x158f, EQNET_OP_SetChatServer2 },
		{ 0x1190, EQNET_OP_ZoneServerInfo },
		{ 0x441c, EQNET_OP_WorldComplete },
		{ 0x6f9d, EQNET_OP_WorldUnknown001 },
		{ 0x61ba, EQNET_OP_FloatListThing },
		{ 0x3288, EQNET_OP_ZoneUnavailable },
		{ 0x7d05, EQNET_OP_WorldClientReady },
		{ 0x3594, EQNET_OP_AckPacket },
		{ 0x4b61, EQNET_OP_PlayerSpawn },
		{ 0x4118, EQNET_OP_ReqNewZone },
		{ 0x43ac, EQNET_OP_ZoneData },
		{ 0x7114, EQNET_OP_ZoneSpawns },
		{ 0x6022, EQNET_OP_PlayerProfile },
		{ 0x6015, EQNET_OP_TimeUpdate },
		{ 0x6a99, EQNET_OP_LevelUpdate },
		{ 0x3d86, EQNET_OP_HungerThirstUpdate },
		{ 0x18ea, EQNET_OP_RequestClientZoneChange },
		{ 0x6d37, EQNET_OP_ZoneChange },
		{ 0x3e17, EQNET_OP_SpawnAppearance },
		{ 0x6942, EQNET_OP_ChangeSize },
		{ 0x684c, EQNET_OP_TributeUpdate },
		{ 0x4895, EQNET_OP_TributeTimer },
		{ 0x156c, EQNET_OP_TaskDescription },
		{ 0x31f3, EQNET_OP_TaskActivity },
		{ 0x687f, EQNET_OP_CompletedTasks },
		{ 0x4658, EQNET_OP_WeatherUpdate },
		{ 0x6ef9, EQNET_OP_SendAATable },
		{ 0x2cd4, EQNET_OP_ClearAA },
		{ 0x7b77, EQNET_OP_ClearLeadershipAbilities },
		{ 0x7bf6, EQNET_OP_UpdateAA },
		{ 0x1fbd, EQNET_OP_RespondAA },
		{ 0x69cd, EQNET_OP_ReqClientSpawn },
		{ 0x6f2b, EQNET_OP_DoorSpawn },
		{ 0x5c85, EQNET_OP_GroundSpawn },
		{ 0x2370, EQNET_OP_SendZonepoints },
		{ 0x78b9, EQNET_OP_SendAAStats },
		{ 0x7b73, EQNET_OP_WorldObjectsSent },
		{ 0x05d5, EQNET_OP_BlockedBuffs },
		{ 0x37c1, EQNET_OP_RemoveBlockedBuffs },
		{ 0x5570, EQNET_OP_ClearBlockedBuffs },
		{ 0x47e7, EQNET_OP_SetExperience },
		{ 0x6bfb, EQNET_OP_SendTributes },
		{ 0x5a67, EQNET_OP_TributeInfo },
		{ 0x4df0, EQNET_OP_SendGuildTributes },
		{ 0x4aa2, EQNET_OP_AAExpUpdate },
		{ 0x0555, EQNET_OP_ExperienceUpdate },
		{ 0x6145, EQNET_OP_HpUpdateExact },
		{ 0x569a, EQNET_OP_ManaEnduranceUpdate },
		{ 0x42ef, EQNET_OP_TGB },
		{ 0x016c, EQNET_OP_SpecialMesg },
		{ 0x51bc, EQNET_OP_GuildMemberList },
		{ 0x5658, EQNET_OP_GuildMOTD },
		{ 0x47ae, EQNET_OP_CharInventory },
		{ 0x0400, EQNET_OP_WearChange },
		{ 0x7062, EQNET_OP_ClientUpdate },
		{ 0x6cdc, EQNET_OP_ClientReady },
		{ 0x2d74, EQNET_OP_SetServerFilter },
		{ 0x1899, EQNET_OP_GetGuildMOTD },
		{ 0x4a5c, EQNET_OP_GetGuildMOTDReply },
		{ 0x0a53, EQNET_OP_GuildMemberUpdate },
		{ 0x1a58, EQNET_OP_GuildInvite },
		{ 0x3c02, EQNET_OP_GuildRemove },
		{ 0x2bff, EQNET_OP_GuildPeace },
		{ 0x053a, EQNET_OP_SetGuildMOTD },
		{ 0x5b0b, EQNET_OP_GuildList },
		{ 0x5408, EQNET_OP_GuildWar },
		{ 0x0598, EQNET_OP_GuildLeader },
		{ 0x3f55, EQNET_OP_GuildDelete },
		{ 0x7b64, EQNET_OP_GuildInviteAccept },
		{ 0x457d, EQNET_OP_GuildDemote },
		{ 0x2dbd, EQNET_OP_GuildPublicNote },
		{ 0x1e4c, EQNET_OP_GuildManageBanker },
		{ 0x0d8a, EQNET_OP_GuildBank },
		{ 0x4ffe, EQNET_OP_SetGuildRank },
		{ 0x5232, EQNET_OP_GuildUpdateURLAndChannel },
		{ 0x28c8, EQNET_OP_GuildStatus },
		{ 0x192d, EQNET_OP_GuildCreate },
		{ 0x7e23, EQNET_OP_LFGuild },
		{ 0x6989, EQNET_OP_GMServers },
		{ 0x56e7, EQNET_OP_GMBecomeNPC },
		{ 0x3fd2, EQNET_OP_GMZoneRequest },
		{ 0x538f, EQNET_OP_GMZoneRequest2 },
		{ 0x5ebc, EQNET_OP_GMGoto },
		{ 0x5a81, EQNET_OP_GMSearchCorpse },
		{ 0x28ef, EQNET_OP_GMHideMe },
		{ 0x655c, EQNET_OP_GMDelCorpse },
		{ 0x7312, EQNET_OP_GMApproval },
		{ 0x097f, EQNET_OP_GMToggle },
		{ 0x712b, EQNET_OP_GMSummon },
		{ 0x1ac1, EQNET_OP_GMEmoteZone },
		{ 0x2444, EQNET_OP_GMEmoteWorld },
		{ 0x6e27, EQNET_OP_GMFind },
		{ 0x0402, EQNET_OP_GMKick },
		{ 0x799c, EQNET_OP_GMKill },
		{ 0x0f48, EQNET_OP_GMNameChange },
		{ 0x7bfb, EQNET_OP_GMLastName },
		{ 0x0c2b, EQNET_OP_InspectAnswer },
		{ 0x0d5a, EQNET_OP_BeginCast },
		{ 0x71bf, EQNET_OP_ColoredText },
		{ 0x0e87, EQNET_OP_ConsentResponse },
		{ 0x3887, EQNET_OP_MemorizeSpell },
		{ 0x5805, EQNET_OP_SwapSpell },
		{ 0x50c2, EQNET_OP_CastSpell },
		{ 0x3c2d, EQNET_OP_Consider },
		{ 0x3b52, EQNET_OP_FormattedMessage },
		{ 0x1f4d, EQNET_OP_SimpleMessage },
		{ 0x0d1d, EQNET_OP_Buff },
		{ 0x231f, EQNET_OP_Illusion },
		{ 0x4a83, EQNET_OP_MoneyOnCorpse },
		{ 0x6d5d, EQNET_OP_RandomReply },
		{ 0x6129, EQNET_OP_DenyResponse },
		{ 0x7f01, EQNET_OP_SkillUpdate },
		{ 0x3190, EQNET_OP_GMTrainSkillConfirm },
		{ 0x139d, EQNET_OP_RandomReq },
		{ 0x7f9e, EQNET_OP_Death },
		{ 0x51fa, EQNET_OP_GMTraining },
		{ 0x5479, EQNET_OP_GMEndTraining },
		{ 0x2257, EQNET_OP_GMTrainSkill },
		{ 0x4a61, EQNET_OP_Animation },
		{ 0x53f9, EQNET_OP_Begging },
		{ 0x6bb9, EQNET_OP_Consent },
		{ 0x4cd1, EQNET_OP_ConsentDeny },
		{ 0x5db5, EQNET_OP_AutoFire },
		{ 0x7706, EQNET_OP_PetCommands },
		{ 0x2528, EQNET_OP_PetHoTT },
		{ 0x0698, EQNET_OP_DeleteSpell },
		{ 0x44ae, EQNET_OP_Surname },
		{ 0x6705, EQNET_OP_ClearSurname },
		{ 0x37a7, EQNET_OP_FaceChange },
		{ 0x1b8a, EQNET_OP_SenseHeading },
		{ 0x0f14, EQNET_OP_Action },
		{ 0x0a18, EQNET_OP_ConsiderCorpse },
		{ 0x2d08, EQNET_OP_HideCorpse },
		{ 0x3331, EQNET_OP_CorpseDrag },
		{ 0x2e70, EQNET_OP_CorpseDrop },
		{ 0x2369, EQNET_OP_Bug },
		{ 0x7705, EQNET_OP_Feedback },
		{ 0x50d0, EQNET_OP_Report },
		{ 0x631a, EQNET_OP_Damage },
		{ 0x2e79, EQNET_OP_ChannelMessage },
		{ 0x35b1, EQNET_OP_Assist },
		{ 0x194f, EQNET_OP_AssistGroup },
		{ 0x6024, EQNET_OP_MoveCoin },
		{ 0x382c, EQNET_OP_ZonePlayerToBind },
		{ 0x5c06, EQNET_OP_KeyRing },
		{ 0x177a, EQNET_OP_WhoAllRequest },
		{ 0x6ffa, EQNET_OP_WhoAllResponse },
		{ 0x6275, EQNET_OP_FriendsWho },
		{ 0x3edc, EQNET_OP_ConfirmDelete },
		{ 0x224f, EQNET_OP_Logout },
		{ 0x7d63, EQNET_OP_Rewind },
		{ 0x756c, EQNET_OP_TargetCommand },
		{ 0x7c94, EQNET_OP_InspectRequest },
		{ 0x3497, EQNET_OP_Hide },
		{ 0x083b, EQNET_OP_Jump },
		{ 0x5f85, EQNET_OP_Camp },
		{ 0x3164, EQNET_OP_Emote },
		{ 0x3d06, EQNET_OP_SetRunMode },
		{ 0x300a, EQNET_OP_BankerChange },
		{ 0x15de, EQNET_OP_HpUpdatePercent },
		{ 0x5cb0, EQNET_OP_InitialMobHealth },
		{ 0x790c, EQNET_OP_TargetsTarget },
		{ 0x6eb5, EQNET_OP_XTargetResponse },
		{ 0x4750, EQNET_OP_XTargetRequest },
		{ 0x1a28, EQNET_OP_XTargetAutoAddHaters },
		{ 0x3f24, EQNET_OP_TargetBuffs },
		{ 0x2121, EQNET_OP_BuffCreate },
		{ 0x4065, EQNET_OP_BuffRemoveRequest },
		{ 0x58c5, EQNET_OP_Despawn },
		{ 0x1df9, EQNET_OP_AutoAttack },
		{ 0x24c5, EQNET_OP_Consume },
		{ 0x2641, EQNET_OP_MoveItem },
		{ 0x66e0, EQNET_OP_DeleteItem },
		{ 0x4ca1, EQNET_OP_DeleteCharge },
		{ 0x7b6e, EQNET_OP_ItemPacket },
		{ 0x695c, EQNET_OP_ItemLinkResponse },
		{ 0x3c66, EQNET_OP_ItemLinkClick },
		{ 0x429b, EQNET_OP_Spawn },
		{ 0x709d, EQNET_OP_Track },
		{ 0x3f49, EQNET_OP_TrackTarget },
		{ 0x03e7, EQNET_OP_TrackUnknown },
		{ 0x6e97, EQNET_OP_ClickDoor },
		{ 0x3154, EQNET_OP_MoveDoor },
		{ 0x6215, EQNET_OP_RemoveAllDoors },
		{ 0x2730, EQNET_OP_EnvDamage },
		{ 0x7554, EQNET_OP_BoardBoat },
		{ 0x739b, EQNET_OP_Forage },
		{ 0x7286, EQNET_OP_LeaveBoat },
		{ 0x7ea8, EQNET_OP_ControlBoat },
		{ 0x6df7, EQNET_OP_SafeFallSuccess },
		{ 0x30a4, EQNET_OP_RezzComplete },
		{ 0x32af, EQNET_OP_RezzRequest },
		{ 0x2d41, EQNET_OP_RezzAnswer },
		{ 0x4675, EQNET_OP_Shielding },
		{ 0x6cfe, EQNET_OP_RequestDuel },
		{ 0x0507, EQNET_OP_MobRename },
		{ 0x7c87, EQNET_OP_AugmentItem },
		{ 0x4572, EQNET_OP_WeaponEquip1 },
		{ 0x399b, EQNET_OP_PlayerStateAdd },
		{ 0x416b, EQNET_OP_PlayerStateRemove },
		{ 0x5cd3, EQNET_OP_ApplyPoison },
		{ 0x6618, EQNET_OP_Save },
		{ 0x3415, EQNET_OP_TestBuff },
		{ 0x6a7e, EQNET_OP_CustomTitles },
		{ 0x1418, EQNET_OP_Split },
		{ 0x55a8, EQNET_OP_YellForHelp },
		{ 0x6617, EQNET_OP_LoadSpellSet },
		{ 0x510c, EQNET_OP_Bandolier },
		{ 0x0651, EQNET_OP_PotionBelt },
		{ 0x41a6, EQNET_OP_DuelResponse },
		{ 0x6d60, EQNET_OP_DuelResponse2 },
		{ 0x2913, EQNET_OP_SaveOnZoneReq },
		{ 0x465e, EQNET_OP_ReadBook },
		{ 0x2137, EQNET_OP_Dye },
		{ 0x7566, EQNET_OP_InterruptCast },
		{ 0x2bad, EQNET_OP_AAAction },
		{ 0x5033, EQNET_OP_LeadershipExpToggle },
		{ 0x074f, EQNET_OP_LeadershipExpUpdate },
		{ 0x5f55, EQNET_OP_PurchaseLeadershipAA },
		{ 0x77ed, EQNET_OP_UpdateLeadershipAA },
		{ 0x66bf, EQNET_OP_MarkNPC },
		{ 0x3ec7, EQNET_OP_MarkRaidNPC },
		{ 0x5c29, EQNET_OP_ClearNPCMarks },
		{ 0x2af4, EQNET_OP_ClearRaidNPCMarks },
		{ 0x0068, EQNET_OP_DoGroupLeadershipAbility },
		{ 0x167b, EQNET_OP_GroupLeadershipAAUpdate },
		{ 0x6e58, EQNET_OP_DelegateAbility },
		{ 0x6b9e, EQNET_OP_SetGroupTarget },
		{ 0x1fd5, EQNET_OP_Charm },
		{ 0x3d00, EQNET_OP_Stun },
		{ 0x6193, EQNET_OP_SendFindableNPCs },
		{ 0x1e04, EQNET_OP_FindPersonRequest },
		{ 0x7cae, EQNET_OP_FindPersonReply },
		{ 0x737a, EQNET_OP_Sound },
		{ 0x7b87, EQNET_OP_PetBuffWindow },
		{ 0x1bd4, EQNET_OP_LevelAppearance },
		{ 0x3d9c, EQNET_OP_Translocate },
		{ 0x301b, EQNET_OP_Sacrifice },
		{ 0x6d27, EQNET_OP_PopupResponse },
		{ 0x24cb, EQNET_OP_OnLevelMessage },
		{ 0x31b1, EQNET_OP_AugmentInfo },
		{ 0x31d1, EQNET_OP_Petition },
		{ 0x2c27, EQNET_OP_SomeItemPacketMaybe },
		{ 0x5272, EQNET_OP_PVPStats },
		{ 0x4973, EQNET_OP_PVPLeaderBoardRequest },
		{ 0x3842, EQNET_OP_PVPLeaderBoardReply },
		{ 0x6c75, EQNET_OP_PVPLeaderBoardDetailsRequest },
		{ 0x7fd7, EQNET_OP_PVPLeaderBoardDetailsReply },
		{ 0x5d24, EQNET_OP_RestState },
		{ 0x107f, EQNET_OP_RespawnWindow },
		{ 0x047c, EQNET_OP_DisciplineTimer },
		{ 0x1031, EQNET_OP_LDoNButton },
		{ 0x68f0, EQNET_OP_SetStartCity },
		{ 0x1524, EQNET_OP_VoiceMacroIn },
		{ 0x1d99, EQNET_OP_VoiceMacroOut },
		{ 0x4eb3, EQNET_OP_ItemViewUnknown },
		{ 0x0baa, EQNET_OP_VetRewardsAvaliable },
		{ 0x34f8, EQNET_OP_VetClaimRequest },
		{ 0x6a5d, EQNET_OP_VetClaimReply },
		{ 0x3fc8, EQNET_OP_CrystalCountUpdate },
		{ 0x6ed3, EQNET_OP_DisciplineUpdate },
		{ 0x4656, EQNET_OP_PositionUpdate },
		{ 0x0f3e, EQNET_OP_NPCMoveUpdate },
		{ 0x6b0e, EQNET_OP_CameraEffect },
		{ 0x57a3, EQNET_OP_SpellEffect },
		{ 0x2c77, EQNET_OP_RemoveNimbusEffect },
		{ 0x659e, EQNET_OP_AltCurrency },
		{ 0x214c, EQNET_OP_AltCurrencyMerchantRequest },
		{ 0x4348, EQNET_OP_AltCurrencyMerchantReply },
		{ 0x4ad7, EQNET_OP_AltCurrencyPurchase },
		{ 0x14cf, EQNET_OP_AltCurrencySell },
		{ 0x322a, EQNET_OP_AltCurrencySellSelection },
		{ 0x365d, EQNET_OP_AltCurrencyReclaim },
		{ 0x726e, EQNET_OP_CrystalReclaim },
		{ 0x12f3, EQNET_OP_CrystalCreate },
		{ 0x301d, EQNET_OP_Untargetable },
		{ 0x4acf, EQNET_OP_IncreaseStats },
		{ 0x6840, EQNET_OP_Weblink },
		{ 0x7fa1, EQNET_OP_InspectMessageUpdate },
		{ 0x041a, EQNET_OP_OpenContainer },
		{ 0x3675, EQNET_OP_Marquee },
		{ 0x1539, EQNET_OP_DzQuit },
		{ 0x21e9, EQNET_OP_DzListTimers },
		{ 0x3657, EQNET_OP_DzAddPlayer },
		{ 0x054e, EQNET_OP_DzRemovePlayer },
		{ 0x4661, EQNET_OP_DzSwapPlayer },
		{ 0x226f, EQNET_OP_DzMakeLeader },
		{ 0x74e4, EQNET_OP_DzPlayerList },
		{ 0x3c5e, EQNET_OP_DzJoinExpeditionConfirm },
		{ 0x1154, EQNET_OP_DzJoinExpeditionReply },
		{ 0x1150, EQNET_OP_DzExpeditionInfo },
		{ 0x2d17, EQNET_OP_DzMemberStatus },
		{ 0x2caf, EQNET_OP_DzLeaderStatus },
		{ 0x6ac2, EQNET_OP_DzExpeditionEndsWarning },
		{ 0x70d8, EQNET_OP_DzExpeditionList },
		{ 0x15c4, EQNET_OP_DzMemberList },
		{ 0x01cb, EQNET_OP_DzCompass },
		{ 0x65e1, EQNET_OP_DzChooseZone },
		{ 0x72ad, EQNET_OP_ShroudSelectionWindow },
		{ 0x488b, EQNET_OP_ShroudRequestStats },
		{ 0x1910, EQNET_OP_ShroudRespondStats },
		{ 0x45d7, EQNET_OP_ShroudSelect },
		{ 0x666d, EQNET_OP_ShroudSelectCancel },
		{ 0x6016, EQNET_OP_ShroudProgress },
		{ 0x66b4, EQNET_OP_ShroudProgress2 },
		{ 0x1643, EQNET_OP_Shroud },
		{ 0x4656, EQNET_OP_SpawnPositionUpdate },
		{ 0x0433, EQNET_OP_ManaUpdate },
		{ 0x6b76, EQNET_OP_EnduranceUpdate },
		{ 0x7901, EQNET_OP_MobManaUpdate },
		{ 0x1912, EQNET_OP_MobEnduranceUpdate },
		{ 0x6ad7, EQNET_OP_LootRequest },
		{ 0x6546, EQNET_OP_EndLootRequest },
		{ 0x5960, EQNET_OP_LootItem },
		{ 0x604d, EQNET_OP_LootComplete },
		{ 0x550f, EQNET_OP_BazaarSearch },
		{ 0x63c8, EQNET_OP_TraderDelItem },
		{ 0x0a1d, EQNET_OP_BecomeTrader },
		{ 0x2881, EQNET_OP_TraderShop },
		{ 0x0c08, EQNET_OP_Trader },
		{ 0x3672, EQNET_OP_TraderBuy },
		{ 0x6db5, EQNET_OP_Barter },
		{ 0x7113, EQNET_OP_TradeRequest },
		{ 0x064a, EQNET_OP_TradeAcceptClick },
		{ 0x606a, EQNET_OP_TradeRequestAck },
		{ 0x0149, EQNET_OP_TradeCoins },
		{ 0x3ff6, EQNET_OP_FinishTrade },
		{ 0x527e, EQNET_OP_CancelTrade },
		{ 0x2a6d, EQNET_OP_TradeMoneyUpdate },
		{ 0xd677, EQNET_OP_MoneyUpdate },
		{ 0x5ed3, EQNET_OP_TradeBusy },
		{ 0x3c27, EQNET_OP_FinishWindow },
		{ 0x6759, EQNET_OP_FinishWindow2 },
		{ 0x101e, EQNET_OP_ItemVerifyRequest },
		{ 0x21c7, EQNET_OP_ItemVerifyReply },
		{ 0x0b27, EQNET_OP_ShopPlayerSell },
		{ 0x442a, EQNET_OP_ShopRequest },
		{ 0x3753, EQNET_OP_ShopEnd },
		{ 0x4578, EQNET_OP_ShopEndConfirm },
		{ 0x436a, EQNET_OP_ShopPlayerBuy },
		{ 0x63c8, EQNET_OP_ShopDelItem },
		{ 0x33e5, EQNET_OP_ClickObject },
		{ 0x41b5, EQNET_OP_ClickObjectAction },
		{ 0x71d1, EQNET_OP_ClearObject },
		{ 0x58d9, EQNET_OP_RecipeDetails },
		{ 0x7770, EQNET_OP_RecipesFavorite },
		{ 0x6948, EQNET_OP_RecipesSearch },
		{ 0x521c, EQNET_OP_RecipeReply },
		{ 0x0322, EQNET_OP_RecipeAutoCombine },
		{ 0x4212, EQNET_OP_TradeSkillCombine },
		{ 0x5e79, EQNET_OP_OpenGuildTributeMaster },
		{ 0x7c24, EQNET_OP_OpenTributeMaster },
		{ 0x0c98, EQNET_OP_SelectTribute },
		{ 0x0b89, EQNET_OP_TributeItem },
		{ 0x314f, EQNET_OP_TributeMoney },
		{ 0x6dc3, EQNET_OP_TributeToggle },
		{ 0x15a7, EQNET_OP_TributePointUpdate },
		{ 0x3ed4, EQNET_OP_LeaveAdventure },
		{ 0x6acc, EQNET_OP_AdventureFinish },
		{ 0x3541, EQNET_OP_AdventureInfoRequest },
		{ 0x5cea, EQNET_OP_AdventureInfo },
		{ 0x2c03, EQNET_OP_AdventureRequest },
		{ 0x1d40, EQNET_OP_AdventureDetails },
		{ 0x34f2, EQNET_OP_AdventureData },
		{ 0x771f, EQNET_OP_AdventureUpdate },
		{ 0x4e22, EQNET_OP_AdventureMerchantRequest },
		{ 0x4dd5, EQNET_OP_AdventureMerchantResponse },
		{ 0x7b7f, EQNET_OP_AdventureMerchantPurchase },
		{ 0x179d, EQNET_OP_AdventureMerchantSell },
		{ 0x7537, EQNET_OP_AdventurePointsUpdate },
		{ 0x4786, EQNET_OP_AdventureStatsRequest },
		{ 0x38b0, EQNET_OP_AdventureStatsReply },
		{ 0x4cc6, EQNET_OP_AdventureLeaderboardRequest },
		{ 0x4423, EQNET_OP_AdventureLeaderboardReply },
		{ 0x54e8, EQNET_OP_GroupDisband },
		{ 0x4f60, EQNET_OP_GroupInvite },
		{ 0x7f2b, EQNET_OP_GroupFollow },
		{ 0x5331, EQNET_OP_GroupUpdate },
		{ 0x0786, EQNET_OP_GroupUpdateB },
		{ 0x2736, EQNET_OP_GroupCancelInvite },
		{ 0x3e22, EQNET_OP_GroupAcknowledge },
		{ 0x58e6, EQNET_OP_GroupDelete },
		{ 0x2736, EQNET_OP_CancelInvite },
		{ 0x6c16, EQNET_OP_GroupFollow2 },
		{ 0x5251, EQNET_OP_GroupInvite2 },
		{ 0x0bd0, EQNET_OP_GroupDisbandYou },
		{ 0x49f6, EQNET_OP_GroupDisbandOther },
		{ 0x0c33, EQNET_OP_GroupLeaderChange },
		{ 0x116d, EQNET_OP_GroupRoles },
		{ 0x5851, EQNET_OP_GroupMakeLeader },
		{ 0x292f, EQNET_OP_GroupMentor },
		{ 0x105b, EQNET_OP_InspectBuffs },
		{ 0x2c38, EQNET_OP_LFGCommand },
		{ 0x28d4, EQNET_OP_LFGGetMatchesRequest },
		{ 0x7a16, EQNET_OP_LFGGetMatchesResponse },
		{ 0x189e, EQNET_OP_LFPGetMatchesRequest },
		{ 0x589f, EQNET_OP_LFPGetMatchesResponse },
		{ 0x7429, EQNET_OP_LFPCommand },
		{ 0x60b5, EQNET_OP_RaidInvite },
		{ 0x4d8b, EQNET_OP_RaidUpdate },
		{ 0x30e2, EQNET_OP_Taunt },
		{ 0x36f8, EQNET_OP_CombatAbility },
		{ 0x7e45, EQNET_OP_SenseTraps },
		{ 0x5821, EQNET_OP_PickPocket },
		{ 0x6def, EQNET_OP_Disarm },
		{ 0x1d22, EQNET_OP_Sneak },
		{ 0x7093, EQNET_OP_Fishing },
		{ 0x221a, EQNET_OP_InstillDoubt },
		{ 0x002b, EQNET_OP_FeignDeath },
		{ 0x10a6, EQNET_OP_Mend },
		{ 0x032b, EQNET_OP_LDoNOpen },
		{ 0x5832, EQNET_OP_TaskActivityComplete },
		{ 0x66ba, EQNET_OP_TaskMemberList },
		{ 0x98f6, EQNET_OP_OpenNewTasksWindow },
		{ 0x6255, EQNET_OP_AvaliableTask },
		{ 0x17d5, EQNET_OP_AcceptNewTask },
		{ 0x547c, EQNET_OP_TaskHistoryRequest },
		{ 0x4524, EQNET_OP_TaskHistoryReply },
		{ 0x3bf5, EQNET_OP_CancelTask },
		{ 0x4b49, EQNET_OP_NewTitlesAvailable },
		{ 0x4d3e, EQNET_OP_RequestTitles },
		{ 0x0d96, EQNET_OP_SendTitleList },
		{ 0x675c, EQNET_OP_SetTitle },
		{ 0x75f5, EQNET_OP_SetTitleReply },
		{ 0x3015, EQNET_OP_MercenaryDataRequest },
		{ 0x0eaa, EQNET_OP_MercenaryDataResponse },
		{ 0x099e, EQNET_OP_MercenaryHire },
		{ 0x0cae, EQNET_OP_MercenaryTimer },
		{ 0x2538, EQNET_OP_MercenaryAssign },
		{ 0x367f, EQNET_OP_MercenaryUnknown1 },
		{ 0x57f2, EQNET_OP_MercenaryDataUpdate },
		{ 0x50c1, EQNET_OP_MercenaryCommand },
		{ 0x3c58, EQNET_OP_MercenarySuspendRequest },
		{ 0x4b82, EQNET_OP_MercenarySuspendResponse },
		{ 0x5fe3, EQNET_OP_MercenaryUnsuspendResponse },
		{ 0x05f1, EQNET_OP_MercenaryDataUpdateRequest },
		{ 0x319a, EQNET_OP_MercenaryDismiss },
		{ 0x184e, EQNET_OP_MercenaryTimerRequest },
		{ 0x7f72, EQNET_OP_PlayMP3 },
		{ 0x82d7, EQNET_OP_ItemRecastDelay },
		{ 0x23a1, EQNET_OP_ShieldGroup }
	};
}

#endif//_EQNET_OPCODES_UNDERFOOT_H_
