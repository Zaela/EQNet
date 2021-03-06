
#ifndef _EQNET_OPCODES_SOF_H_
#define _EQNET_OPCODES_SOF_H_

#include <cstdint>
#include "opcode_eqnet.h"

namespace SoF
{
	static const OpCodeTranslation toCanonical[] = {
		{ 0x6c3c, EQNET_OP_SendLoginInfo },
		{ 0x7fc0, EQNET_OP_ApproveWorld },
		{ 0x129a, EQNET_OP_LogServer },
		{ 0x6040, EQNET_OP_SendCharInfo },
		{ 0x0a1b, EQNET_OP_ExpansionInfo },
		{ 0x04fb, EQNET_OP_GuildsList },
		{ 0x1340, EQNET_OP_EnterWorld },
		{ 0x1aee, EQNET_OP_PostEnterWorld },
		{ 0x22cf, EQNET_OP_SendSpellChecksum },
		{ 0x43ba, EQNET_OP_SendSkillCapsChecksum },
		{ 0x789f, EQNET_OP_DeleteCharacter },
		{ 0x7e32, EQNET_OP_CharacterCreateRequest },
		{ 0x009b, EQNET_OP_CharacterCreate },
		{ 0x0149a, EQNET_OP_RandomNameGenerator },
		{ 0x2037, EQNET_OP_ApproveName },
		{ 0x5711, EQNET_OP_MessageOfTheDay },
		{ 0x71b8, EQNET_OP_SetChatServer },
		{ 0x32cc, EQNET_OP_SetChatServer2 },
		{ 0x18b1, EQNET_OP_ZoneServerInfo },
		{ 0x2486, EQNET_OP_WorldComplete },
		{ 0x7930, EQNET_OP_WorldUnknown001 },
		{ 0x6177, EQNET_OP_FloatListThing },
		{ 0x07a2, EQNET_OP_ZoneUnavailable },
		{ 0x2ebd, EQNET_OP_WorldClientReady },
		{ 0x4d38, EQNET_OP_AckPacket },
		{ 0x737e, EQNET_OP_PlayerSpawn },
		{ 0x5417, EQNET_OP_ReqNewZone },
		{ 0x5d22, EQNET_OP_ZoneData },
		{ 0x5af2, EQNET_OP_ZoneSpawns },
		{ 0x0feb, EQNET_OP_PlayerProfile },
		{ 0x7274, EQNET_OP_TimeUpdate },
		{ 0x1036, EQNET_OP_LevelUpdate },
		{ 0x7120, EQNET_OP_HungerThirstUpdate },
		{ 0x7899, EQNET_OP_RequestClientZoneChange },
		{ 0x201e, EQNET_OP_ZoneChange },
		{ 0x50ec, EQNET_OP_SpawnAppearance },
		{ 0x71fb, EQNET_OP_TributeUpdate },
		{ 0x2871, EQNET_OP_TributeTimer },
		{ 0x0af9, EQNET_OP_TaskDescription },
		{ 0x2e60, EQNET_OP_TaskActivity },
		{ 0x75ac, EQNET_OP_CompletedTasks },
		{ 0x70a5, EQNET_OP_WeatherUpdate },
		{ 0x6f05, EQNET_OP_SendAATable },
		{ 0x71b9, EQNET_OP_ClearAA },
		{ 0x74e5, EQNET_OP_ClearLeadershipAbilities },
		{ 0x45d2, EQNET_OP_UpdateAA },
		{ 0x4426, EQNET_OP_RespondAA },
		{ 0x014c, EQNET_OP_ReqClientSpawn },
		{ 0x68c8, EQNET_OP_DoorSpawn },
		{ 0x30da, EQNET_OP_GroundSpawn },
		{ 0x2992, EQNET_OP_SendZonepoints },
		{ 0x60db, EQNET_OP_SendAAStats },
		{ 0x3703, EQNET_OP_WorldObjectsSent },
		{ 0x39c4, EQNET_OP_BlockedBuffs },
		{ 0x125e, EQNET_OP_RemoveBlockedBuffs },
		{ 0x2f8b, EQNET_OP_ClearBlockedBuffs },
		{ 0x1fa1, EQNET_OP_SetExperience },
		{ 0x6764, EQNET_OP_SendTributes },
		{ 0x68c2, EQNET_OP_TributeInfo },
		{ 0x3f33, EQNET_OP_SendGuildTributes },
		{ 0x3518, EQNET_OP_AAExpUpdate },
		{ 0x6d0b, EQNET_OP_ExperienceUpdate },
		{ 0x62f6, EQNET_OP_HpUpdateExact },
		{ 0x0659, EQNET_OP_ManaEnduranceUpdate },
		{ 0x0137, EQNET_OP_TGB },
		{ 0x1126, EQNET_OP_SpecialMesg },
		{ 0x317c, EQNET_OP_GuildMemberList },
		{ 0x3309, EQNET_OP_GuildMOTD },
		{ 0x08a3, EQNET_OP_CharInventory },
		{ 0x25f0, EQNET_OP_WearChange },
		{ 0x5cf3, EQNET_OP_ClientUpdate },
		{ 0x2854, EQNET_OP_ClientReady },
		{ 0x7038, EQNET_OP_SetServerFilter },
		{ 0x0b50, EQNET_OP_GetGuildMOTD },
		{ 0x4289, EQNET_OP_GetGuildMOTDReply },
		{ 0x71d1, EQNET_OP_GuildMemberUpdate },
		{ 0x430f, EQNET_OP_GuildInvite },
		{ 0x7149, EQNET_OP_GuildRemove },
		{ 0x1b42, EQNET_OP_GuildPeace },
		{ 0x273f, EQNET_OP_SetGuildMOTD },
		{ 0x04fb, EQNET_OP_GuildList },
		{ 0x5f91, EQNET_OP_GuildWar },
		{ 0x7703, EQNET_OP_GuildLeader },
		{ 0x0b9a, EQNET_OP_GuildDelete },
		{ 0x110f, EQNET_OP_GuildInviteAccept },
		{ 0x2cdf, EQNET_OP_GuildDemote },
		{ 0x28a9, EQNET_OP_GuildPublicNote },
		{ 0x899b, EQNET_OP_GuildManageBanker },
		{ 0x43ff, EQNET_OP_GuildBank },
		{ 0x4914, EQNET_OP_SetGuildRank },
		{ 0x60a5, EQNET_OP_GuildUpdateURLAndChannel },
		{ 0x3563, EQNET_OP_LFGuild },
		{ 0x1f23, EQNET_OP_GMServers },
		{ 0x42fa, EQNET_OP_GMBecomeNPC },
		{ 0x7678, EQNET_OP_GMZoneRequest },
		{ 0x6833, EQNET_OP_GMZoneRequest2 },
		{ 0x1e2c, EQNET_OP_GMGoto },
		{ 0x5f15, EQNET_OP_GMSearchCorpse },
		{ 0x2e3c, EQNET_OP_GMHideMe },
		{ 0x79df, EQNET_OP_GMDelCorpse },
		{ 0x5546, EQNET_OP_GMApproval },
		{ 0x7ab6, EQNET_OP_GMToggle },
		{ 0x3235, EQNET_OP_GMSummon },
		{ 0x26cc, EQNET_OP_GMEmoteZone },
		{ 0x6256, EQNET_OP_GMEmoteWorld },
		{ 0x24d8, EQNET_OP_GMFind },
		{ 0x7a92, EQNET_OP_GMKick },
		{ 0x7b6b, EQNET_OP_GMKill },
		{ 0x74b5, EQNET_OP_GMNameChange },
		{ 0x0375, EQNET_OP_GMLastName },
		{ 0x084f, EQNET_OP_InspectAnswer },
		{ 0x0ef2, EQNET_OP_Action2 },
		{ 0x5a50, EQNET_OP_BeginCast },
		{ 0x3bc7, EQNET_OP_ColoredText },
		{ 0x4d30, EQNET_OP_ConsentResponse },
		{ 0x6a93, EQNET_OP_MemorizeSpell },
		{ 0x1418, EQNET_OP_SwapSpell },
		{ 0x7f5d, EQNET_OP_CastSpell },
		{ 0x32e1, EQNET_OP_Consider },
		{ 0x5b9e, EQNET_OP_ChatMessageEQStr },
		{ 0x553e, EQNET_OP_SimpleMessage },
		{ 0x7bd6, EQNET_OP_Buff },
		{ 0x7f86, EQNET_OP_Illusion },
		{ 0x51c9, EQNET_OP_MoneyOnCorpse },
		{ 0x649c, EQNET_OP_RandomReply },
		{ 0x607e, EQNET_OP_DenyResponse },
		{ 0x29e0, EQNET_OP_SkillUpdate },
		{ 0x33a3, EQNET_OP_GMTrainSkillConfirm },
		{ 0x4e2d, EQNET_OP_RandomReq },
		{ 0x596f, EQNET_OP_Death },
		{ 0x0362, EQNET_OP_GMTraining },
		{ 0x6768, EQNET_OP_GMEndTraining },
		{ 0x7498, EQNET_OP_GMTrainSkill },
		{ 0x13a1, EQNET_OP_Animation },
		{ 0x7ae0, EQNET_OP_Begging },
		{ 0x0fb9, EQNET_OP_Consent },
		{ 0x79d7, EQNET_OP_ConsentDeny },
		{ 0x1486, EQNET_OP_AutoFire },
		{ 0x573a, EQNET_OP_PetCommands },
		{ 0x6d7e, EQNET_OP_DeleteSpell },
		{ 0x683e, EQNET_OP_Surname },
		{ 0x2613, EQNET_OP_ClearSurname },
		{ 0x482d, EQNET_OP_FaceChange },
		{ 0x1237, EQNET_OP_SenseHeading },
		{ 0x5285, EQNET_OP_Action },
		{ 0x4cbb, EQNET_OP_ConsiderCorpse },
		{ 0x51e1, EQNET_OP_CorpseDrag },
		{ 0x77a6, EQNET_OP_CorpseDrop },
		{ 0x1cf0, EQNET_OP_Bug },
		{ 0x216c, EQNET_OP_Feedback },
		{ 0x5bd9, EQNET_OP_Report },
		{ 0x0ef2, EQNET_OP_Damage },
		{ 0x3c7d, EQNET_OP_ChatMessage },
		{ 0x15a4, EQNET_OP_Assist },
		{ 0x03ce, EQNET_OP_AssistGroup },
		{ 0x1d9d, EQNET_OP_MoveCoin },
		{ 0x6542, EQNET_OP_ZonePlayerToBind },
		{ 0x2f10, EQNET_OP_KeyRing },
		{ 0x34d4, EQNET_OP_WhoAllRequest },
		{ 0x3817, EQNET_OP_WhoAllResponse },
		{ 0x237b, EQNET_OP_FriendsWho },
		{ 0x79a5, EQNET_OP_ConfirmDelete },
		{ 0x3874, EQNET_OP_Logout },
		{ 0x428f, EQNET_OP_Rewind },
		{ 0x2da9, EQNET_OP_TargetCommand },
		{ 0x5a79, EQNET_OP_InspectRequest },
		{ 0x65ff, EQNET_OP_Hide },
		{ 0x7871, EQNET_OP_Jump },
		{ 0x6807, EQNET_OP_Camp },
		{ 0x5f4d, EQNET_OP_Emote },
		{ 0x2716, EQNET_OP_SetRunMode },
		{ 0x03dd, EQNET_OP_BankerChange },
		{ 0x311a, EQNET_OP_HpUpdatePercent },
		{ 0x23f1, EQNET_OP_InitialMobHealth },
		{ 0x1306, EQNET_OP_TargetsTarget },
		{ 0x15da, EQNET_OP_Despawn },
		{ 0x7647, EQNET_OP_PositionUpdate },
		{ 0x3427, EQNET_OP_AutoAttack },
		{ 0x729a, EQNET_OP_Consume },
		{ 0x14b3, EQNET_OP_MoveItem },
		{ 0x7dd4, EQNET_OP_DeleteItem },
		{ 0x32e2, EQNET_OP_DeleteCharge },
		{ 0x78cd, EQNET_OP_ItemPacket },
		{ 0x31e4, EQNET_OP_ItemLinkResponse },
		{ 0x2de4, EQNET_OP_ItemLinkClick },
		{ 0x581a, EQNET_OP_Spawn },
		{ 0x060a, EQNET_OP_Track },
		{ 0x21e8, EQNET_OP_TrackTarget },
		{ 0x6a70, EQNET_OP_TrackUnknown },
		{ 0x5ac1, EQNET_OP_ClickDoor },
		{ 0x61df, EQNET_OP_MoveDoor },
		{ 0x69d8, EQNET_OP_RemoveAllDoors },
		{ 0x20e7, EQNET_OP_EnvDamage },
		{ 0x54a7, EQNET_OP_BoardBoat },
		{ 0x54c5, EQNET_OP_Forage },
		{ 0x56a2, EQNET_OP_LeaveBoat },
		{ 0x4ce7, EQNET_OP_ControlBoat },
		{ 0x1584, EQNET_OP_SafeFallSuccess },
		{ 0x4b0d, EQNET_OP_RezzComplete },
		{ 0x2bb7, EQNET_OP_RezzRequest },
		{ 0x076d, EQNET_OP_RezzAnswer },
		{ 0x0829, EQNET_OP_Shielding },
		{ 0x3a2b, EQNET_OP_RequestDuel },
		{ 0x6be5, EQNET_OP_MobRename },
		{ 0x172a, EQNET_OP_AugmentItem },
		{ 0x7260, EQNET_OP_WeaponEquip1 },
		{ 0x5c2f, EQNET_OP_PlayerStateAdd },
		{ 0x6213, EQNET_OP_PlayerStateRemove },
		{ 0x4543, EQNET_OP_ApplyPoison },
		{ 0x72f2, EQNET_OP_Save },
		{ 0x07bf, EQNET_OP_TestBuff },
		{ 0x2e8f, EQNET_OP_CustomTitles },
		{ 0x198e, EQNET_OP_Split },
		{ 0x4f4a, EQNET_OP_YellForHelp },
		{ 0x05b5, EQNET_OP_LoadSpellSet },
		{ 0x3fd4, EQNET_OP_Bandolier },
		{ 0x16f3, EQNET_OP_PotionBelt },
		{ 0x5e59, EQNET_OP_DuelResponse },
		{ 0x1103, EQNET_OP_SaveOnZoneReq },
		{ 0x424a, EQNET_OP_ReadBook },
		{ 0x3611, EQNET_OP_Dye },
		{ 0x51f6, EQNET_OP_InterruptCast },
		{ 0x0a4f, EQNET_OP_AAAction },
		{ 0x24d4, EQNET_OP_LeadershipExpToggle },
		{ 0x58b6, EQNET_OP_LeadershipExpUpdate },
		{ 0x1408, EQNET_OP_PurchaseLeadershipAA },
		{ 0x7abf, EQNET_OP_UpdateLeadershipAA },
		{ 0x4697, EQNET_OP_MarkNPC },
		{ 0x00c6, EQNET_OP_MarkRaidNPC },
		{ 0x2ff2, EQNET_OP_ClearNPCMarks },
		{ 0x56a9, EQNET_OP_ClearRaidNPCMarks },
		{ 0x5a64, EQNET_OP_DoGroupLeadershipAbility },
		{ 0x57e3, EQNET_OP_DelegateAbility },
		{ 0x1651, EQNET_OP_SetGroupTarget },
		{ 0x2a85, EQNET_OP_DuelResponse2 },
		{ 0x2f32, EQNET_OP_Charm },
		{ 0x55bf, EQNET_OP_Stun },
		{ 0x07f0, EQNET_OP_FindPersonRequest },
		{ 0x7770, EQNET_OP_FindPersonReply },
		{ 0x2b02, EQNET_OP_Sound },
		{ 0x124a, EQNET_OP_PetBuffWindow },
		{ 0x3ec8, EQNET_OP_LevelAppearance },
		{ 0x1f0f, EQNET_OP_Translocate },
		{ 0x55c9, EQNET_OP_Sacrifice },
		{ 0x028b, EQNET_OP_PopupResponse },
		{ 0x0332, EQNET_OP_OnLevelMessage },
		{ 0x08f8, EQNET_OP_AugmentInfo },
		{ 0x3a46, EQNET_OP_Petition },
		{ 0x08fa, EQNET_OP_SomeItemPacketMaybe },
		{ 0x6af1, EQNET_OP_PVPStats },
		{ 0x5b3b, EQNET_OP_PVPLeaderBoardRequest },
		{ 0x3a69, EQNET_OP_PVPLeaderBoardReply },
		{ 0x43b6, EQNET_OP_PVPLeaderBoardDetailsRequest },
		{ 0x680c, EQNET_OP_PVPLeaderBoardDetailsReply },
		{ 0x116e, EQNET_OP_RestState },
		{ 0x7bf6, EQNET_OP_RespawnWindow },
		{ 0x53c5, EQNET_OP_DisciplineTimer },
		{ 0x7eac, EQNET_OP_LDoNButton },
		{ 0x7e91, EQNET_OP_SetStartCity },
		{ 0x6276, EQNET_OP_VoiceMacroIn },
		{ 0x30d2, EQNET_OP_VoiceMacroOut },
		{ 0x20e8, EQNET_OP_DisciplineUpdate },
		{ 0x23f9, EQNET_OP_CameraEffect },
		{ 0x3e90, EQNET_OP_SpellEffect },
		{ 0x0f05, EQNET_OP_AltCurrency },
		{ 0x433f, EQNET_OP_AltCurrencyMerchantRequest },
		{ 0x7b20, EQNET_OP_AltCurrencyMerchantReply },
		{ 0x3994, EQNET_OP_AltCurrencyPurchase },
		{ 0x2ac3, EQNET_OP_AltCurrencySell },
		{ 0x7d00, EQNET_OP_AltCurrencySellSelection },
		{ 0x1996, EQNET_OP_AltCurrencyReclaim },
		{ 0x5872, EQNET_OP_RemoveNimbusEffect },
		{ 0x67e9, EQNET_OP_InspectMessageUpdate },
		{ 0x66c8, EQNET_OP_OpenInventory },
		{ 0x10e3, EQNET_OP_OpenContainer },
		{ 0x2f75, EQNET_OP_Marquee },
		{ 0x3e36, EQNET_OP_Untargetable },
		{ 0x20d6, EQNET_OP_DzQuit },
		{ 0x4e4b, EQNET_OP_DzListTimers },
		{ 0x426a, EQNET_OP_DzAddPlayer },
		{ 0x2ce8, EQNET_OP_DzRemovePlayer },
		{ 0x2c3e, EQNET_OP_DzSwapPlayer },
		{ 0x1a75, EQNET_OP_DzMakeLeader },
		{ 0x5116, EQNET_OP_DzPlayerList },
		{ 0x1793, EQNET_OP_DzJoinExpeditionConfirm },
		{ 0x7a6f, EQNET_OP_DzJoinExpeditionReply },
		{ 0x60a6, EQNET_OP_DzExpeditionInfo },
		{ 0x0516, EQNET_OP_DzMemberStatus },
		{ 0x79d3, EQNET_OP_DzLeaderStatus },
		{ 0x5153, EQNET_OP_DzExpeditionEndsWarning },
		{ 0x02ac, EQNET_OP_DzExpeditionList },
		{ 0x5e14, EQNET_OP_DzMemberList },
		{ 0x531d, EQNET_OP_DzCompass },
		{ 0x3c5b, EQNET_OP_DzChooseZone },
		{ 0x36e3, EQNET_OP_LootRequest },
		{ 0x6599, EQNET_OP_EndLootRequest },
		{ 0x3760, EQNET_OP_LootItem },
		{ 0x48f3, EQNET_OP_LootComplete },
		{ 0x14f2, EQNET_OP_BazaarSearch },
		{ 0x068d, EQNET_OP_TraderDelItem },
		{ 0x32b7, EQNET_OP_BecomeTrader },
		{ 0x1acf, EQNET_OP_TraderShop },
		{ 0x6b41, EQNET_OP_Trader },
		{ 0x7569, EQNET_OP_TraderBuy },
		{ 0x51bf, EQNET_OP_Barter },
		{ 0x180d, EQNET_OP_TradeRequest },
		{ 0x1d07, EQNET_OP_TradeAcceptClick },
		{ 0x1255, EQNET_OP_TradeRequestAck },
		{ 0x08ca, EQNET_OP_TradeCoins },
		{ 0x30b7, EQNET_OP_FinishTrade },
		{ 0x7a43, EQNET_OP_CancelTrade },
		{ 0x69e7, EQNET_OP_TradeMoneyUpdate },
		{ 0x305a, EQNET_OP_MoneyUpdate },
		{ 0x5f49, EQNET_OP_TradeBusy },
		{ 0x4919, EQNET_OP_FinishWindow },
		{ 0x1758, EQNET_OP_FinishWindow2 },
		{ 0x0cc2, EQNET_OP_ItemVerifyRequest },
		{ 0x41ee, EQNET_OP_ItemVerifyReply },
		{ 0x5a58, EQNET_OP_ShopPlayerSell },
		{ 0x5fb7, EQNET_OP_ShopRequest },
		{ 0x0bd9, EQNET_OP_ShopEnd },
		{ 0x475f, EQNET_OP_ShopEndConfirm },
		{ 0x09c4, EQNET_OP_ShopPlayerBuy },
		{ 0x068d, EQNET_OP_ShopDelItem },
		{ 0x21b3, EQNET_OP_ClickObject },
		{ 0x67c0, EQNET_OP_ClickObjectAction },
		{ 0x0e66, EQNET_OP_ClearObject },
		{ 0x0706, EQNET_OP_RecipeDetails },
		{ 0x2e2c, EQNET_OP_RecipesFavorite },
		{ 0x41a2, EQNET_OP_RecipesSearch },
		{ 0x67f5, EQNET_OP_RecipeReply },
		{ 0x0427, EQNET_OP_RecipeAutoCombine },
		{ 0x163c, EQNET_OP_TradeSkillCombine },
		{ 0x3223, EQNET_OP_OpenGuildTributeMaster },
		{ 0x5027, EQNET_OP_OpenTributeMaster },
		{ 0x1d8c, EQNET_OP_SelectTribute },
		{ 0x16d6, EQNET_OP_TributeItem },
		{ 0x65bc, EQNET_OP_TributeMoney },
		{ 0xe59f, EQNET_OP_TributeToggle },
		{ 0x656c, EQNET_OP_TributePointUpdate },
		{ 0x1342, EQNET_OP_LeaveAdventure },
		{ 0x0974, EQNET_OP_AdventureFinish },
		{ 0x6e84, EQNET_OP_AdventureInfoRequest },
		{ 0x526d, EQNET_OP_AdventureInfo },
		{ 0x4f4c, EQNET_OP_AdventureRequest },
		{ 0x7f4d, EQNET_OP_AdventureDetails },
		{ 0x10b9, EQNET_OP_AdventureData },
		{ 0x53c2, EQNET_OP_AdventureUpdate },
		{ 0x71b2, EQNET_OP_AdventureMerchantRequest },
		{ 0x40d6, EQNET_OP_AdventureMerchantResponse },
		{ 0x5488, EQNET_OP_AdventureMerchantPurchase },
		{ 0x1c26, EQNET_OP_AdventureMerchantSell },
		{ 0x6583, EQNET_OP_AdventurePointsUpdate },
		{ 0x70b2, EQNET_OP_AdventureStatsRequest },
		{ 0x5a3a, EQNET_OP_AdventureStatsReply },
		{ 0x2a28, EQNET_OP_AdventureLeaderboardRequest },
		{ 0x6555, EQNET_OP_AdventureLeaderboardReply },
		{ 0x4b26, EQNET_OP_GroupDisband },
		{ 0x6321, EQNET_OP_GroupInvite },
		{ 0x1a12, EQNET_OP_GroupFollow },
		{ 0x2e5c, EQNET_OP_GroupUpdate },
		{ 0x596c, EQNET_OP_GroupCancelInvite },
		{ 0x1306, EQNET_OP_GroupAcknowledge },
		{ 0x596c, EQNET_OP_CancelInvite },
		{ 0x59d4, EQNET_OP_GroupFollow2 },
		{ 0x07f6, EQNET_OP_GroupInvite2 },
		{ 0x9ef3, EQNET_OP_GroupMentor },
		{ 0x3547, EQNET_OP_InspectBuffs },
		{ 0x5d81, EQNET_OP_LFGCommand },
		{ 0x21e0, EQNET_OP_LFGGetMatchesRequest },
		{ 0x6dca, EQNET_OP_LFGGetMatchesResponse },
		{ 0x601a, EQNET_OP_LFPGetMatchesRequest },
		{ 0x2274, EQNET_OP_LFPGetMatchesResponse },
		{ 0x1f00, EQNET_OP_LFPCommand },
		{ 0x0e11, EQNET_OP_RaidInvite },
		{ 0x237e, EQNET_OP_RaidUpdate },
		{ 0x094d, EQNET_OP_Taunt },
		{ 0x045d, EQNET_OP_CombatAbility },
		{ 0x7466, EQNET_OP_SenseTraps },
		{ 0x768a, EQNET_OP_PickPocket },
		{ 0x19b6, EQNET_OP_Disarm },
		{ 0x17c4, EQNET_OP_Sneak },
		{ 0x73ab, EQNET_OP_Fishing },
		{ 0x6865, EQNET_OP_InstillDoubt },
		{ 0x1c68, EQNET_OP_FeignDeath },
		{ 0x7767, EQNET_OP_Mend },
		{ 0x4b92, EQNET_OP_LDoNOpen },
		{ 0x7338, EQNET_OP_TaskActivityComplete },
		{ 0x17c3, EQNET_OP_OpenNewTasksWindow },
		{ 0x5d1d, EQNET_OP_AvaliableTask },
		{ 0x66a8, EQNET_OP_AcceptNewTask },
		{ 0x3035, EQNET_OP_TaskHistoryRequest },
		{ 0x3a60, EQNET_OP_TaskHistoryReply },
		{ 0x4db6, EQNET_OP_CancelTask },
		{ 0x3713, EQNET_OP_TaskMemberList },
		{ 0x3cde, EQNET_OP_TaskMemberInvite },
		{ 0x6cab, EQNET_OP_TaskMemberInviteResponse },
		{ 0x354a, EQNET_OP_TaskMemberChange },
		{ 0x5050, EQNET_OP_TaskMakeLeader },
		{ 0x5d1d, EQNET_OP_TaskAddPlayer },
		{ 0x516f, EQNET_OP_TaskRemovePlayer },
		{ 0x0ad6, EQNET_OP_TaskPlayerList },
		{ 0x2c8c, EQNET_OP_TaskQuit },
		{ 0x179c, EQNET_OP_NewTitlesAvailable },
		{ 0x3445, EQNET_OP_RequestTitles },
		{ 0x3754, EQNET_OP_SendTitleList },
		{ 0x54fe, EQNET_OP_SetTitle },
		{ 0x690b, EQNET_OP_SetTitleReply },
		{ 0x5ecb, EQNET_OP_IncreaseStats },
		{ 0x044b, EQNET_OP_VetRewardsAvaliable },
		{ 0x7503, EQNET_OP_VetClaimRequest },
		{ 0x01e1, EQNET_OP_VetClaimReply },
		{ 0x0d1c, EQNET_OP_PlayMP3 },
		{ 0x64c1, EQNET_OP_CrystalCountUpdate },
		{ 0x65e2, EQNET_OP_CrystalCreate },
		{ 0x0730, EQNET_OP_CrystalReclaim },
		{ 0x22cf, EQNET_OP_LoginUnknown1 },
		{ 0x43ba, EQNET_OP_LoginUnknown2 },
		{ 0x4db4, EQNET_OP_ItemViewUnknown },
		{ 0x0ada, EQNET_OP_ItemRecastDelay }
	};
}

#endif//_EQNET_OPCODES_SOF_H_
