
#ifndef _EQNET_WORLD_H_
#define _EQNET_WORLD_H_

#include <cstdint>
#include "main.h"

void readGuilds(EQNet*, byte* data, uint32_t len);
void readCharSelectCharacters(EQNet*, byte* data, uint32_t len);

#endif//_EQNET_WORLD_H_
