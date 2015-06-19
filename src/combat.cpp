
#include "stdafx.h"

void EQNet_SetTarget(EQNet* net, EQNet_Id target)
{
	// TargetCommand and TargetMouse are treated equivalently by the EQEmu server (mostly - command does more validity checks)
	Packet::queueFourByte(net, EQNET_OP_TargetCommand, target);
}

void EQNet_SetAutoAttacking(EQNet* net, int setting)
{
	// 4-byte bool
	Packet::queueFourByte(net, EQNET_OP_AutoAttack, setting ? 1 : 0);
}

void EQNet_SetAutoFiring(EQNet* net, int setting)
{
	// 1-byte bool
	Packet* packet = new Packet(net, sizeof(bool), EQNET_OP_AutoFire);
	*(bool*)packet->getDataBuffer() = (setting != 0);
	packet->queue(net);
}

void EQNet_Assist(EQNet* net, EQNet_Id target)
{
	Packet::queueFourByte(net, EQNET_OP_Assist, target);
}

void EQNet_UseSkill(EQNet* net, EQNet_Skill skill, EQNet_Id target)
{
	switch (skill)
	{
	case EQNET_SKILL_FeignDeath:
		Packet::queueZeroLength(net, EQNET_OP_FeignDeath);
		break;

	case EQNET_SKILL_Hide:
		Packet::queueZeroLength(net, EQNET_OP_Hide);
		break;

	case EQNET_SKILL_Sneak:
		Packet::queueZeroLength(net, EQNET_OP_Sneak);
		break;

	case EQNET_SKILL_Forage:
		Packet::queueZeroLength(net, EQNET_OP_Forage);
		break;

	case EQNET_SKILL_Begging:
		Packet::queueZeroLength(net, EQNET_OP_Begging);
		break;

	case EQNET_SKILL_Taunt:
		Packet::queueFourByte(net, EQNET_OP_Taunt, target);
		break;

	case EQNET_SKILL_SenseHeading:
		Packet::queueZeroLength(net, EQNET_OP_SenseHeading);
		break;

	case EQNET_SKILL_SenseTraps:
		Packet::queueZeroLength(net, EQNET_OP_SenseTraps);
		break;

	case EQNET_SKILL_DisarmTraps:
		Packet::queueZeroLength(net, EQNET_OP_DisarmTraps);
		break;

	case EQNET_SKILL_Fishing:
		Packet::queueZeroLength(net, EQNET_OP_Fishing);
		break;

	case EQNET_SKILL_Archery:
	case EQNET_SKILL_Backstab:
	case EQNET_SKILL_Bash: // also covers slam
	case EQNET_SKILL_DragonPunch: // also covers tail rake
	case EQNET_SKILL_EagleStrike:
	case EQNET_SKILL_FlyingKick:
	case EQNET_SKILL_RoundKick:
	case EQNET_SKILL_TigerClaw:
	{
		// combat ability
		Packet* packet = new Packet(net, sizeof(Titanium::CombatAbility_Struct), EQNET_OP_CombatAbility);
		Titanium::CombatAbility_Struct* ca = (Titanium::CombatAbility_Struct*)packet->getDataBuffer();

		ca->m_target = target;
		ca->m_skill = skill;

		switch (skill)
		{
		case EQNET_SKILL_Archery:
		case EQNET_SKILL_Throwing:
			ca->m_atk = EQNET_SLOT_Range;
			break;
		default:
			ca->m_atk = 100;
			break;
		}

		packet->queue(net);
		break;
	}
	} // switch
}
