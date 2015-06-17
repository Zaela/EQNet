
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

// some packets reuse the native representation as the "translated" representation
// these must not be deleted

// use 1 bit per opcode for fast lookups and low space usage
#define NO_DELETE_LEN (EQNET_OP_INTERNAL_MAX_COUNT / 32 + 1)

static uint32_t noDeleteOpcodes[NO_DELETE_LEN];

#define OpIndex(op) (op / 32)
#define OpBit(op) ((uint32_t)(1 << (op % 32)))
#define OpName(op) EQNET_OP_##op
#define SET(op) noDeleteOpcodes[OpIndex(OpName(op))] |= OpBit(OpName(op))

void initNoDeleteOpcodes()
{
	memset(noDeleteOpcodes, 0, sizeof(uint32_t) * NO_DELETE_LEN);

	SET(Despawn);
	SET(MessageOfTheDay);
	SET(TimeUpdate);
}

uint32_t isNoDeleteOpcode(uint16_t opcode)
{
	return noDeleteOpcodes[OpIndex(opcode)] & OpBit(opcode);
}

#undef NO_DELETE_LEN
#undef OpIndex
#undef OpBit
#undef set

void checkSpecialDestructor(EQNet_Packet& p)
{
	switch (p.opcode)
	{

	}
}
