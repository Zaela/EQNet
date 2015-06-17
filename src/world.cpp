
#include "stdafx.h"

static void enterWorldPacket(EQNet* net, EQNet_Character* character, bool tutorial = false, bool home = false);

int EQNet_WorldToZone(EQNet* net, EQNet_Character* character)
{
	if (net->mode != MODE_CHAR_SELECT)
		return false;

	enterWorldPacket(net, character);
	return true;
}

void enterWorldPacket(EQNet* net, EQNet_Character* character, bool tutorial, bool home)
{
	net->selectedCharacter = character;

	// struct seems the same for all client versions
	Packet* packet = new Packet(sizeof(Titanium::EnterWorld_Struct),
		translateOpcodeToServer(net, EQNET_OP_EnterWorld));

	Titanium::EnterWorld_Struct* ew = (Titanium::EnterWorld_Struct*)packet->getDataBuffer();
	Util::strcpy(ew->name, character->name, 64);

	if (tutorial)
		ew->tutorial = 1;
	else if (home)
		ew->return_home = 1;

	packet->queue(net);
}

const EQNet_Guild* EQNet_GetGuildList(EQNet* net, int* count)
{
	if (count)
		*count = net->guildListCount;
	return net->guildList;
}

const EQNet_Character* EQNet_GetCharacterList(EQNet* net, int* count)
{
	if (count)
		*count = net->charListCount;
	return net->charList;
}

const char* EQNet_GetServerShortName(EQNet* net)
{
	return net->serverShortName;
}

static EQNet_Character* allocCharList(EQNet* net, int count)
{
	EQNet_Character* list = new EQNet_Character[count];

	net->charList = list;
	net->charListCount = count;

	return list;
}

static void delCharList(EQNet* net)
{
	if (net->charList)
	{
		delete[] net->charList;
		net->charListCount = 0;
	}
}

static EQNet_Guild* allocGuildList(EQNet* net, int count)
{
	EQNet_Guild* list = new EQNet_Guild[count];
	memset(list, 0, sizeof(EQNet_Guild) * count);

	net->guildList = list;
	net->guildListCount = count;
	return list;
}

static void delGuildList(EQNet* net)
{
	if (net->guildList)
	{
		delete[] net->guildList;
		net->guildListCount = 0;
	}
}

void readGuilds(EQNet* net, byte* data, uint32_t len)
{
	switch (net->clientVersion)
	{
	case EQNET_CLIENT_TITANIUM:
	case EQNET_CLIENT_SECRETS_OF_FAYDWER:
	case EQNET_CLIENT_SEEDS_OF_DESTRUCTION:
	{
		Titanium::GuildsListEntry_Struct* guilds = (Titanium::GuildsListEntry_Struct*)data;

		delGuildList(net);

		// count the number of actual guild names represented
		int numGuilds = 0;
		Titanium::GuildsListEntry_Struct* g = guilds;
		uint32_t pos = 0;
		while (pos < len)
		{
			if (g->name[0] != 0)
				++numGuilds;
			++g;
			pos += sizeof(Titanium::GuildsListEntry_Struct);
		}

		if (numGuilds == 0)
			break;

		// copy only actual guild names
		EQNet_Guild* list = allocGuildList(net, numGuilds);

		pos = 0;
		int id = -1;
		g = guilds;
		while (pos < len)
		{
			if (g->name[0] != 0)
			{
				list->id = id;
				Util::strcpy(list->name, g->name, 64);
				++list;
			}
			++id;
			++g;
			pos += sizeof(Titanium::GuildsListEntry_Struct);
		}
		break;
	}
	case EQNET_CLIENT_UNDERFOOT:
	case EQNET_CLIENT_REIGN_OF_FEAR:
	case EQNET_CLIENT_REIGN_OF_FEAR2:
	{
		Underfoot::GuildsList_Struct* guilds = (Underfoot::GuildsList_Struct*)data;
		
		delGuildList(net);

		if (guilds->highID == 0)
			break;

		EQNet_Guild* list = allocGuildList(net, guilds->highID - 1);
		// uint32_t id + cstr name
		uint32_t pos = sizeof(Underfoot::GuildsList_Struct);
		for (uint32_t i = 1; i < guilds->highID; ++i)
		{
			list->id = *(uint32_t*)(data + pos);
			pos += sizeof(uint32_t);

			char* cstr = (char*)(data + pos);
			Util::strcpy(list->name, cstr, 64);

			++list;
			pos += strlen(cstr) + 1;
		}
		break;
	}
	} // switch
}

void readCharSelectCharacters(EQNet* net, byte* data, uint32_t len)
{
	switch (net->clientVersion)
	{
	case EQNET_CLIENT_TITANIUM:
	{
		Titanium::CharacterSelect_Struct* cs = (Titanium::CharacterSelect_Struct*)data;

		delCharList(net);

		int countChars = 0;
		for (int i = 0; i < 10; ++i)
		{
			if (cs->level[i] != 0)
				++countChars;
		}

		if (countChars > 0)
		{
			EQNet_Character* list = allocCharList(net, countChars);

			for (int i = 0; i < 10; ++i)
			{
				if (cs->level[i] == 0)
					continue;

				Util::strcpy(list->name, cs->name[i], 64);
				list->level = cs->level[i];
				list->charClass = cs->class_[i];
				list->race = cs->race[i];
				list->gender = cs->gender[i];
				list->deity = cs->deity[i];
				list->zone = cs->zone[i];

				++list;
			}
		}
		break;
	}

	case EQNET_CLIENT_SECRETS_OF_FAYDWER:
	case EQNET_CLIENT_SEEDS_OF_DESTRUCTION:
	case EQNET_CLIENT_UNDERFOOT:
	case EQNET_CLIENT_REIGN_OF_FEAR:
	case EQNET_CLIENT_REIGN_OF_FEAR2:
	{
		Underfoot::CharacterSelect_Struct* cs = (Underfoot::CharacterSelect_Struct*)data;

		delCharList(net);
		EQNet_Character* list = allocCharList(net, cs->CharCount);

		uint32_t pos = sizeof(Underfoot::CharacterSelect_Struct);

		for (uint32_t i = 0; i < cs->CharCount; ++i)
		{
			Underfoot::CharacterSelectEntryA_Struct* csa = (Underfoot::CharacterSelectEntryA_Struct*)(data + pos);
			size_t nameLen = strlen(csa->Name);

			Util::strcpy(list->name, csa->Name, 64);
			list->level = csa->Level;
			list->gender = csa->Gender;

			pos += sizeof(Underfoot::CharacterSelectEntryA_Struct) + nameLen;

			Underfoot::CharacterSelectEntryB_Struct* csb = (Underfoot::CharacterSelectEntryB_Struct*)(data + pos);

			list->charClass = csb->Class;
			list->race = csb->Race;
			list->deity = csb->Deity;
			list->zone = csb->Zone;

			pos += sizeof(Underfoot::CharacterSelectEntryB_Struct);
		}

		break;
	}
	} // switch
}
