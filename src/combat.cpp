
#include "stdafx.h"

void EQNet_SetTarget(EQNet* net, EQNet_Id target)
{
	// TargetCommand and TargetMouse are treated equivalently by the EQEmu server
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

	default:
	{
		// combat ability
		Packet* packet = new Packet(net, sizeof(Titanium::CombatAbility_Struct), EQNET_OP_CombatAbility);
		Titanium::CombatAbility_Struct* ca = (Titanium::CombatAbility_Struct*)packet->getDataBuffer();

		ca->m_target = target;
		ca->m_skill = skill; // fix skills enum to match server

		packet->queue(net);
		break;
	}
	} // switch
}
