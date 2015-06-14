
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
