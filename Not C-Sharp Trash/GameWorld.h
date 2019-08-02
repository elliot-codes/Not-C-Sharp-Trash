#pragma once
#include "Includes.h"

class GameWorld
{
public:
	uint64_t Address;

	GameWorld(uint64_t Addr)
	{
		Address = Addr;
	}
};