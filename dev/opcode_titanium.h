
#ifndef _EQNET_OPCODES_TITANIUM_H_
#define _EQNET_OPCODES_TITANIUM_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace Titanium
{
	static const OpCodeTranslation toCanonical[] = {
		{ 0x3c25, EQNET_OP_ApproveWorld },
		{ 0x0fa6, EQNET_OP_LogServer },
		{ 0x024d, EQNET_OP_MessageOfTheDay },
		{ 0x4dd0, EQNET_OP_SendLoginInfo },
		{ 0x26c9, EQNET_OP_DeleteCharacter },
		{ 0x4513, EQNET_OP_SendCharInfo },
		{ 0x04ec, EQNET_OP_ExpansionInfo },
		{ 0x10b2, EQNET_OP_CharacterCreate },
		{ 0x23d4, EQNET_OP_RandomNameGenerator },
		{ 0x6957, EQNET_OP_GuildsList },
		{ 0x3ea6, EQNET_OP_ApproveName },
		{ 0x7cba, EQNET_OP_EnterWorld },
		{ 0x52a4, EQNET_OP_PostEnterWorld },
		{ 0x00d7, EQNET_OP_SetChatServer },
		{ 0x6536, EQNET_OP_SetChatServer2 },
		{ 0x61b6, EQNET_OP_ZoneServerInfo },
		{ 0x509d, EQNET_OP_WorldComplete },
		{ 0x407c, EQNET_OP_ZoneUnavailable },
		{ 0x5e99, EQNET_OP_WorldClientReady },
		{ 0x60fa, EQNET_OP_CharacterStillInZone },
		{ 0x7d37, EQNET_OP_WorldChecksumFailure },
		{ 0x8da7, EQNET_OP_WorldLoginFailed },
		{ 0x7718, EQNET_OP_WorldLogout },
		{ 0x583b, EQNET_OP_WorldLevelTooHigh },
		{ 0x436a, EQNET_OP_CharInacessable },
		{ 0x7213, EQNET_OP_PlayerSpawn },
		{ 0x7752, EQNET_OP_AckPacket },
		{ 0x0920, EQNET_OP_ZoneData },
		{ 0x0322, EQNET_OP_ReqClientSpawn },
		{ 0x2e78, EQNET_OP_ZoneSpawns },
		{ 0x5394, EQNET_OP_CharInventory },
		{ 0x6563, EQNET_OP_SetServerFilter },
		{ 0x7f63, EQNET_OP_LockoutTimerInfo },
		{ 0x3eba, EQNET_OP_SendZonepoints },
		{ 0x4c24, EQNET_OP_DoorSpawn },
		{ 0x7ac5, EQNET_OP_ReqNewZone },
		{ 0x75df, EQNET_OP_PlayerProfile },
		{ 0x1580, EQNET_OP_TimeUpdate },
		{ 0x61ff, EQNET_OP_Logout },
		{ 0x3cdc, EQNET_OP_LogoutReply },
		{ 0x711e, EQNET_OP_PreLogoutReply },
		{ 0x6d44, EQNET_OP_LevelUpdate },
		{ 0x7a83, EQNET_OP_HungerThirstUpdate },
		{ 0x251f, EQNET_OP_Petition },
		{ 0x33c3, EQNET_OP_PetitionQue },
		{ 0x5692, EQNET_OP_PetitionDelete },
		{ 0x6957, EQNET_OP_ZoneGuildList },
		{ 0x7fec, EQNET_OP_GetGuildMOTD },
		{ 0x3246, EQNET_OP_GetGuildMOTDReply },
		{ 0x147d, EQNET_OP_GuildMemberList },
		{ 0x0f4d, EQNET_OP_GuildMemberUpdate },
		{ 0x0179, EQNET_OP_GuildRemove },
		{ 0x215a, EQNET_OP_GuildPeace },
		{ 0x0c81, EQNET_OP_GuildWar },
		{ 0x12b1, EQNET_OP_GuildLeader },
		{ 0x4eb9, EQNET_OP_GuildDemote },
		{ 0x475a, EQNET_OP_GuildMOTD },
		{ 0x591c, EQNET_OP_SetGuildMOTD },
		{ 0x18b7, EQNET_OP_GuildInvite },
		{ 0x17a2, EQNET_OP_GuildPublicNote },
		{ 0x6cce, EQNET_OP_GuildDelete },
		{ 0x61d0, EQNET_OP_GuildInviteAccept },
		{ 0x3d1e, EQNET_OP_GuildManageBanker },
		{ 0xb4ab, EQNET_OP_GuildBank },
		{ 0x6966, EQNET_OP_SetGuildRank },
		{ 0x1858, EQNET_OP_LFGuild },
		{ 0x3387, EQNET_OP_GMServers },
		{ 0x7864, EQNET_OP_GMBecomeNPC },
		{ 0x1306, EQNET_OP_GMZoneRequest },
		{ 0x3c32, EQNET_OP_GMSearchCorpse },
		{ 0x15b2, EQNET_OP_GMHideMe },
		{ 0x1cee, EQNET_OP_GMGoto },
		{ 0x0b2f, EQNET_OP_GMDelCorpse },
		{ 0x0c0f, EQNET_OP_GMApproval },
		{ 0x7fea, EQNET_OP_GMToggle },
		{ 0x244c, EQNET_OP_GMZoneRequest2 },
		{ 0x1edc, EQNET_OP_GMSummon },
		{ 0x39f2, EQNET_OP_GMEmoteZone },
		{ 0x3383, EQNET_OP_GMEmoteWorld },
		{ 0x5930, EQNET_OP_GMFind },
		{ 0x692c, EQNET_OP_GMKick },
		{ 0x238f, EQNET_OP_GMTraining },
		{ 0x613d, EQNET_OP_GMEndTraining },
		{ 0x11d2, EQNET_OP_GMTrainSkill },
		{ 0x2acf, EQNET_OP_Animation },
		{ 0x1e51, EQNET_OP_Stun },
		{ 0x267c, EQNET_OP_MoneyUpdate },
		{ 0x0587, EQNET_OP_SetExperience },
		{ 0x5b7b, EQNET_OP_IncreaseStats },
		{ 0x7825, EQNET_OP_CrashDump },
		{ 0x1496, EQNET_OP_ReadBook },
		{ 0x00dd, EQNET_OP_Dye },
		{ 0x77d6, EQNET_OP_Consume },
		{ 0x13e7, EQNET_OP_Begging },
		{ 0x775d, EQNET_OP_InspectRequest },
		{ 0x2403, EQNET_OP_InspectAnswer },
		{ 0x3990, EQNET_OP_BeginCast },
		{ 0x0b2d, EQNET_OP_ColoredText },
		{ 0x1081, EQNET_OP_Consent },
		{ 0x4e8c, EQNET_OP_ConsentDeny },
		{ 0x6380, EQNET_OP_ConsentResponse },
		{ 0x68ac, EQNET_OP_LFGCommand },
		{ 0x022f, EQNET_OP_LFGGetMatchesRequest },
		{ 0x1a85, EQNET_OP_LFGAppearance },
		{ 0x45d0, EQNET_OP_LFGGetMatchesResponse },
		{ 0x7081, EQNET_OP_LootItem },
		{ 0x7ac2, EQNET_OP_Bug },
		{ 0x4298, EQNET_OP_BoardBoat },
		{ 0x736b, EQNET_OP_Save },
		{ 0x78c1, EQNET_OP_Camp },
		{ 0x2316, EQNET_OP_EndLootRequest },
		{ 0x308e, EQNET_OP_MemorizeSpell },
		{ 0x2126, EQNET_OP_SwapSpell },
		{ 0x304b, EQNET_OP_CastSpell },
		{ 0x4f37, EQNET_OP_DeleteSpell },
		{ 0x403e, EQNET_OP_LoadSpellSet },
		{ 0x5e55, EQNET_OP_AutoAttack },
		{ 0x6c53, EQNET_OP_AutoFire },
		{ 0x65ca, EQNET_OP_Consider },
		{ 0x547a, EQNET_OP_Emote },
		{ 0x10a1, EQNET_OP_PetCommands },
		{ 0x4e31, EQNET_OP_PetBuffWindow },
		{ 0x7c32, EQNET_OP_SpawnAppearance },
		{ 0x55bc, EQNET_OP_Despawn },
		{ 0x5a48, EQNET_OP_ChatMessageEQStr },
		{ 0x5cdd, EQNET_OP_WhoAllRequest },
		{ 0x757b, EQNET_OP_WhoAllResponse },
		{ 0x4aba, EQNET_OP_SetRunMode },
		{ 0x673c, EQNET_OP_SimpleMessage },
		{ 0x1540, EQNET_OP_SaveOnZoneReq },
		{ 0x05ac, EQNET_OP_SenseHeading },
		{ 0x6a53, EQNET_OP_Buff },
		{ 0x0a94, EQNET_OP_LootComplete },
		{ 0x31b3, EQNET_OP_EnvDamage },
		{ 0x4848, EQNET_OP_Split },
		{ 0x4668, EQNET_OP_Surname },
		{ 0x6cdb, EQNET_OP_ClearSurname },
		{ 0x420f, EQNET_OP_MoveItem },
		{ 0x0f8e, EQNET_OP_FaceChange },
		{ 0x3397, EQNET_OP_ItemPacket },
		{ 0x667c, EQNET_OP_ItemLinkResponse },
		{ 0x5e20, EQNET_OP_ClientReady },
		{ 0x5dd8, EQNET_OP_ZoneChange },
		{ 0x53e5, EQNET_OP_ItemLinkClick },
		{ 0x4796, EQNET_OP_Forage },
		{ 0x1ee9, EQNET_OP_BazaarSearch },
		{ 0x1860, EQNET_OP_Spawn },
		{ 0x7441, EQNET_OP_WearChange },
		{ 0x497c, EQNET_OP_Action },
		{ 0x2372, EQNET_OP_SpecialMesg },
		{ 0x67c9, EQNET_OP_LeaveBoat },
		{ 0x254d, EQNET_OP_WeatherUpdate },
		{ 0x35a6, EQNET_OP_LFPGetMatchesRequest },
		{ 0x448d, EQNET_OP_Illusion },
		{ 0x1477, EQNET_OP_TargetCommand },
		{ 0x6a12, EQNET_OP_TargetsTarget },
		{ 0x6980, EQNET_OP_GMKill },
		{ 0x7fe4, EQNET_OP_MoneyOnCorpse },
		{ 0x043b, EQNET_OP_ClickDoor },
		{ 0x700d, EQNET_OP_MoveDoor },
		{ 0x77d0, EQNET_OP_RemoveAllDoors },
		{ 0x6f90, EQNET_OP_LootRequest },
		{ 0x61ef, EQNET_OP_YellForHelp },
		{ 0x4839, EQNET_OP_ManaEnduranceUpdate },
		{ 0x6f82, EQNET_OP_LFPCommand },
		{ 0x6cd5, EQNET_OP_RandomReply },
		{ 0x7c66, EQNET_OP_DenyResponse },
		{ 0x773f, EQNET_OP_ConsiderCorpse },
		{ 0x50c0, EQNET_OP_CorpseDrag },
		{ 0x7c7c, EQNET_OP_CorpseDrop },
		{ 0x3838, EQNET_OP_ConfirmDelete },
		{ 0x0695, EQNET_OP_HpUpdatePercent },
		{ 0x6a93, EQNET_OP_SkillUpdate },
		{ 0x5534, EQNET_OP_RandomReq },
		{ 0x14cb, EQNET_OP_ClientUpdate },
		{ 0x7f9d, EQNET_OP_Report },
		{ 0x0f47, EQNET_OP_GroundSpawn },
		{ 0x06c5, EQNET_OP_LFPGetMatchesResponse },
		{ 0x0797, EQNET_OP_Jump },
		{ 0x5ecd, EQNET_OP_ExperienceUpdate },
		{ 0x6160, EQNET_OP_Death },
		{ 0x4dbc, EQNET_OP_BecomeCorpse },
		{ 0x23a1, EQNET_OP_GMLastName },
		{ 0x3d2d, EQNET_OP_InitialMobHealth },
		{ 0x14ef, EQNET_OP_Mend },
		{ 0x5306, EQNET_OP_Feedback },
		{ 0x0c11, EQNET_OP_TGB },
		{ 0x0b97, EQNET_OP_InterruptCast },
		{ 0x5c78, EQNET_OP_Damage },
		{ 0x1004, EQNET_OP_ChatMessage },
		{ 0x358e, EQNET_OP_LevelAppearance },
		{ 0x12e5, EQNET_OP_Charm },
		{ 0x7709, EQNET_OP_Assist },
		{ 0x5104, EQNET_OP_AssistGroup },
		{ 0x539b, EQNET_OP_AugmentItem },
		{ 0x4d81, EQNET_OP_DeleteItem },
		{ 0x1c4a, EQNET_OP_DeleteCharge },
		{ 0x2c81, EQNET_OP_ControlBoat },
		{ 0x7489, EQNET_OP_FeignDeath },
		{ 0x13c8, EQNET_OP_LDoNButton },
		{ 0x7657, EQNET_OP_MoveCoin },
		{ 0x385e, EQNET_OP_ZonePlayerToBind },
		{ 0x4cfa, EQNET_OP_Rewind },
		{ 0x8258, EQNET_OP_Translocate },
		{ 0x727a, EQNET_OP_Sacrifice },
		{ 0x68c4, EQNET_OP_KeyRing },
		{ 0x0c2c, EQNET_OP_ApplyPoison },
		{ 0x45ff, EQNET_OP_AugmentInfo },
		{ 0x41dc, EQNET_OP_SetStartCity },
		{ 0x22c5, EQNET_OP_SpellEffect },
		{ 0x7cfe, EQNET_OP_CrystalReclaim },
		{ 0x62c3, EQNET_OP_CrystalCreate },
		{ 0x1d4d, EQNET_OP_Marquee },
		{ 0x486d, EQNET_OP_DzQuit },
		{ 0x39aa, EQNET_OP_DzListTimers },
		{ 0x7fba, EQNET_OP_DzAddPlayer },
		{ 0x540b, EQNET_OP_DzRemovePlayer },
		{ 0x794a, EQNET_OP_DzSwapPlayer },
		{ 0x0ce9, EQNET_OP_DzMakeLeader },
		{ 0xada0, EQNET_OP_DzPlayerList },
		{ 0x3817, EQNET_OP_DzJoinExpeditionConfirm },
		{ 0x5da9, EQNET_OP_DzJoinExpeditionReply },
		{ 0x098e, EQNET_OP_DzExpeditionInfo },
		{ 0x1826, EQNET_OP_DzMemberStatus },
		{ 0x7abc, EQNET_OP_DzLeaderStatus },
		{ 0x1c3f, EQNET_OP_DzExpeditionEndsWarning },
		{ 0x7c12, EQNET_OP_DzExpeditionList },
		{ 0x09b6, EQNET_OP_DzMemberList },
		{ 0x28aa, EQNET_OP_DzCompass },
		{ 0x1022, EQNET_OP_DzChooseZone },
		{ 0x0da9, EQNET_OP_TraderDelItem },
		{ 0x2844, EQNET_OP_BecomeTrader },
		{ 0x35e8, EQNET_OP_TraderShop },
		{ 0x524e, EQNET_OP_Trader },
		{ 0x6dd8, EQNET_OP_TraderBuy },
		{ 0x7460, EQNET_OP_Barter },
		{ 0x372f, EQNET_OP_TradeRequest },
		{ 0x0065, EQNET_OP_TradeAcceptClick },
		{ 0x4048, EQNET_OP_TradeRequestAck },
		{ 0x34c1, EQNET_OP_TradeCoins },
		{ 0x6014, EQNET_OP_FinishTrade },
		{ 0x2dc1, EQNET_OP_CancelTrade },
		{ 0x6839, EQNET_OP_TradeBusy },
		{ 0x0e13, EQNET_OP_ShopPlayerSell },
		{ 0x7e03, EQNET_OP_ShopEnd },
		{ 0x20b2, EQNET_OP_ShopEndConfirm },
		{ 0x221e, EQNET_OP_ShopPlayerBuy },
		{ 0x45f9, EQNET_OP_ShopRequest },
		{ 0x0da9, EQNET_OP_ShopDelItem },
		{ 0x3bc2, EQNET_OP_ClickObject },
		{ 0x6937, EQNET_OP_ClickObjectAction },
		{ 0x21ed, EQNET_OP_ClearObject },
		{ 0x4ea2, EQNET_OP_RecipeDetails },
		{ 0x23f0, EQNET_OP_RecipesFavorite },
		{ 0x164d, EQNET_OP_RecipesSearch },
		{ 0x31f8, EQNET_OP_RecipeReply },
		{ 0x0353, EQNET_OP_RecipeAutoCombine },
		{ 0x0b40, EQNET_OP_TradeSkillCombine },
		{ 0x28e1, EQNET_OP_RequestDuel },
		{ 0x3bad, EQNET_OP_DuelResponse },
		{ 0x1b09, EQNET_OP_DuelResponse2 },
		{ 0x4b05, EQNET_OP_RezzComplete },
		{ 0x1035, EQNET_OP_RezzRequest },
		{ 0x6219, EQNET_OP_RezzAnswer },
		{ 0x3b21, EQNET_OP_SafeFallSuccess },
		{ 0x3fe6, EQNET_OP_Shielding },
		{ 0x6ab0, EQNET_OP_TestBuff },
		{ 0x5d11, EQNET_OP_Track },
		{ 0x7085, EQNET_OP_TrackTarget },
		{ 0x6177, EQNET_OP_TrackUnknown },
		{ 0x512e, EQNET_OP_OpenTributeMaster },
		{ 0x27b3, EQNET_OP_OpenTributeReply },
		{ 0x625d, EQNET_OP_SelectTribute },
		{ 0x6f6c, EQNET_OP_TributeItem },
		{ 0x27b3, EQNET_OP_TributeMoney },
		{ 0x7f25, EQNET_OP_TributeNPC },
		{ 0x2688, EQNET_OP_TributeToggle },
		{ 0x4665, EQNET_OP_TributeTimer },
		{ 0x6463, EQNET_OP_TributePointUpdate },
		{ 0x5639, EQNET_OP_TributeUpdate },
		{ 0x5e3d, EQNET_OP_GuildTributeInfo },
		{ 0x152d, EQNET_OP_TributeInfo },
		{ 0x5e3a, EQNET_OP_SendGuildTributes },
		{ 0x067a, EQNET_OP_SendTributes },
		{ 0x0c0d, EQNET_OP_LeaveAdventure },
		{ 0x3906, EQNET_OP_AdventureFinish },
		{ 0x2aaf, EQNET_OP_AdventureInfoRequest },
		{ 0x1db5, EQNET_OP_AdventureInfo },
		{ 0x43fd, EQNET_OP_AdventureRequest },
		{ 0x3f26, EQNET_OP_AdventureDetails },
		{ 0x0677, EQNET_OP_AdventureData },
		{ 0x64ac, EQNET_OP_AdventureUpdate },
		{ 0x0950, EQNET_OP_AdventureMerchantRequest },
		{ 0x4416, EQNET_OP_AdventureMerchantResponse },
		{ 0x413d, EQNET_OP_AdventureMerchantPurchase },
		{ 0x0097, EQNET_OP_AdventureMerchantSell },
		{ 0x420a, EQNET_OP_AdventurePointsUpdate },
		{ 0x5fc7, EQNET_OP_AdventureStatsRequest },
		{ 0x56cd, EQNET_OP_AdventureStatsReply },
		{ 0x230a, EQNET_OP_AdventureLeaderboardRequest },
		{ 0x0d0f, EQNET_OP_AdventureLeaderboardReply },
		{ 0x0e76, EQNET_OP_GroupDisband },
		{ 0x1b48, EQNET_OP_GroupInvite },
		{ 0x7bc7, EQNET_OP_GroupFollow },
		{ 0x2dd6, EQNET_OP_GroupUpdate },
		{ 0x1f27, EQNET_OP_GroupCancelInvite },
		{ 0x12d6, EQNET_OP_GroupInvite2 },
		{ 0x1f21, EQNET_OP_RaidJoin },
		{ 0x5891, EQNET_OP_RaidInvite },
		{ 0x1f21, EQNET_OP_RaidUpdate },
		{ 0x4fb6, EQNET_OP_InspectBuffs },
		{ 0x7180, EQNET_OP_DisciplineUpdate },
		{ 0x53df, EQNET_OP_DisciplineTimer },
		{ 0x3c41, EQNET_OP_FindPersonRequest },
		{ 0x5711, EQNET_OP_FindPersonReply },
		{ 0x541e, EQNET_OP_Sound },
		{ 0x0498, EQNET_OP_MobRename },
		{ 0x6a5b, EQNET_OP_BankerChange },
		{ 0x5e48, EQNET_OP_Taunt },
		{ 0x5ee8, EQNET_OP_CombatAbility },
		{ 0x5666, EQNET_OP_SenseTraps },
		{ 0x2ad8, EQNET_OP_PickPocket },
		{ 0x1241, EQNET_OP_DisarmTraps },
		{ 0x17d9, EQNET_OP_Disarm },
		{ 0x4312, EQNET_OP_Hide },
		{ 0x74e1, EQNET_OP_Sneak },
		{ 0x0b36, EQNET_OP_Fishing },
		{ 0x389e, EQNET_OP_InstillDoubt },
		{ 0x083b, EQNET_OP_LDoNOpen },
		{ 0x54eb, EQNET_OP_TaskActivityComplete },
		{ 0x76a2, EQNET_OP_CompletedTasks },
		{ 0x5ef7, EQNET_OP_TaskDescription },
		{ 0x682d, EQNET_OP_TaskActivity },
		{ 0x722f, EQNET_OP_TaskMemberList },
		{ 0x5e7c, EQNET_OP_OpenNewTasksWindow },
		{ 0x207f, EQNET_OP_AcceptNewTask },
		{ 0x5df4, EQNET_OP_TaskHistoryRequest },
		{ 0x397d, EQNET_OP_TaskHistoryReply },
		{ 0x3ba8, EQNET_OP_CancelTask },
		{ 0x79b4, EQNET_OP_TaskMemberInvite },
		{ 0x0358, EQNET_OP_TaskMemberInviteResponse },
		{ 0x5886, EQNET_OP_TaskMemberChange },
		{ 0x1b25, EQNET_OP_TaskMakeLeader },
		{ 0x6bc4, EQNET_OP_TaskAddPlayer },
		{ 0x37b9, EQNET_OP_TaskRemovePlayer },
		{ 0x3961, EQNET_OP_TaskPlayerList },
		{ 0x35dd, EQNET_OP_TaskQuit },
		{ 0x7834, EQNET_OP_RequestClientZoneChange },
		{ 0x367d, EQNET_OP_SendAATable },
		{ 0x5966, EQNET_OP_UpdateAA },
		{ 0x3af4, EQNET_OP_RespondAA },
		{ 0x5996, EQNET_OP_SendAAStats },
		{ 0x0681, EQNET_OP_AAAction },
		{ 0x5f58, EQNET_OP_AAExpUpdate },
		{ 0x17bf, EQNET_OP_PurchaseLeadershipAA },
		{ 0x07f1, EQNET_OP_UpdateLeadershipAA },
		{ 0x596e, EQNET_OP_LeadershipExpUpdate },
		{ 0x5b37, EQNET_OP_LeadershipExpToggle },
		{ 0x5483, EQNET_OP_MarkNPC },
		{ 0x3ef6, EQNET_OP_ClearNPCMarks },
		{ 0x569e, EQNET_OP_DoGroupLeadershipAbility },
		{ 0x10f4, EQNET_OP_DelegateAbility },
		{ 0x3eec, EQNET_OP_SetGroupTarget },
		{ 0x26ab, EQNET_OP_PlayMP3 },
		{ 0x48fe, EQNET_OP_FriendsWho },
		{ 0x7510, EQNET_OP_MoveLogRequest },
		{ 0x7cfe, EQNET_OP_ReclaimCrystals },
		{ 0x0ce3, EQNET_OP_CrystalCountUpdate },
		{ 0x2a28, EQNET_OP_CustomTitles },
		{ 0x4eca, EQNET_OP_NewTitlesAvailable },
		{ 0x5eba, EQNET_OP_RequestTitles },
		{ 0x3e89, EQNET_OP_SendTitleList },
		{ 0x1f22, EQNET_OP_SetTitle },
		{ 0x5eab, EQNET_OP_SetTitleReply },
		{ 0x6f0c, EQNET_OP_Bandolier },
		{ 0x0719, EQNET_OP_PotionBelt },
		{ 0x1dde, EQNET_OP_OnLevelMessage },
		{ 0x3816, EQNET_OP_PopupResponse },
		{ 0x571a, EQNET_OP_SlashAdventure },
		{ 0x0557, EQNET_OP_VetRewardsAvaliable },
		{ 0x6ba0, EQNET_OP_VetClaimRequest },
		{ 0x407e, EQNET_OP_VetClaimReply },
		{ 0x36b2, EQNET_OP_BecomePVPPrompt },
		{ 0x5cc0, EQNET_OP_PVPStats },
		{ 0x61d2, EQNET_OP_PVPLeaderBoardRequest },
		{ 0x1a59, EQNET_OP_PVPLeaderBoardReply },
		{ 0x06a2, EQNET_OP_PVPLeaderBoardDetailsRequest },
		{ 0x246a, EQNET_OP_PVPLeaderBoardDetailsReply },
		{ 0x40e7, EQNET_OP_PickLockSuccess },
		{ 0x6c5e, EQNET_OP_WeaponEquip1 },
		{ 0x63da, EQNET_OP_PlayerStateAdd },
		{ 0x381d, EQNET_OP_PlayerStateRemove },
		{ 0x2866, EQNET_OP_VoiceMacroIn },
		{ 0x2ec6, EQNET_OP_VoiceMacroOut },
		{ 0x0937, EQNET_OP_CameraEffect },
		{ 0x729c, EQNET_OP_AnnoyingZoneUnknown },
		{ 0x4033, EQNET_OP_SomeItemPacketMaybe },
		{ 0x1974, EQNET_OP_QueryResponseThing },
		{ 0x6a1b, EQNET_OP_FloatListThing },
		{ 0x0695, EQNET_OP_HpUpdatePercent },
		{ 0x3bcf, EQNET_OP_HpUpdateExact }
	};
}

#endif//_EQNET_OPCODES_TITANIUM_H_
