
#include "stdafx.h"

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

	case EQNET_CLIENT_UNDERFOOT:
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
