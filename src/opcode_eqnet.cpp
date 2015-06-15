
#include "stdafx.h"

static uint16_t findOpcodeFromServer(uint16_t opcodeIn, const OpCodeTranslation* opTbl, int count)
{
	for (int i = 0; i < count; ++i)
	{
		if (opTbl[i].from == opcodeIn)
			return opTbl[i].to;
	}

	return EQNET_OP_NONE;
}

static uint16_t findOpcodeToServer(uint16_t opcodeIn, const OpCodeTranslation* opTbl, int count)
{
	for (int i = 0; i < count; ++i)
	{
		if (opTbl[i].to == opcodeIn)
			return opTbl[i].from;
	}

	return EQNET_OP_NONE;
}

uint16_t translateOpcodeFromServer(EQNet* net, uint16_t opcodeIn)
{
	switch (net->clientVersion)
	{
	case EQNET_CLIENT_TITANIUM:
		return findOpcodeFromServer(opcodeIn, Titanium::toCanonical,
			sizeof(Titanium::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_SECRETS_OF_FAYDWER:
		return findOpcodeFromServer(opcodeIn, SoF::toCanonical,
			sizeof(SoF::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_SEEDS_OF_DESTRUCTION:
		return findOpcodeFromServer(opcodeIn, SoD::toCanonical,
			sizeof(SoD::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_UNDERFOOT:
		return findOpcodeFromServer(opcodeIn, Underfoot::toCanonical,
			sizeof(Underfoot::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_REIGN_OF_FEAR:
		return findOpcodeFromServer(opcodeIn, RoF::toCanonical,
			sizeof(RoF::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_REIGN_OF_FEAR2:
		return findOpcodeFromServer(opcodeIn, RoF2::toCanonical,
			sizeof(RoF2::toCanonical) / sizeof(OpCodeTranslation));
	}

	return EQNET_OP_NONE;
}

uint16_t translateOpcodeToServer(EQNet* net, uint16_t opcodeIn)
{
	switch (net->clientVersion)
	{
	case EQNET_CLIENT_TITANIUM:
		return findOpcodeToServer(opcodeIn, Titanium::toCanonical,
			sizeof(Titanium::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_SECRETS_OF_FAYDWER:
		return findOpcodeToServer(opcodeIn, SoF::toCanonical,
			sizeof(SoF::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_SEEDS_OF_DESTRUCTION:
		return findOpcodeToServer(opcodeIn, SoD::toCanonical,
			sizeof(SoD::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_UNDERFOOT:
		return findOpcodeToServer(opcodeIn, Underfoot::toCanonical,
			sizeof(Underfoot::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_REIGN_OF_FEAR:
		return findOpcodeToServer(opcodeIn, RoF::toCanonical,
			sizeof(RoF::toCanonical) / sizeof(OpCodeTranslation));
	case EQNET_CLIENT_REIGN_OF_FEAR2:
		return findOpcodeToServer(opcodeIn, RoF2::toCanonical,
			sizeof(RoF2::toCanonical) / sizeof(OpCodeTranslation));
	}

	return EQNET_OP_NONE;
}
