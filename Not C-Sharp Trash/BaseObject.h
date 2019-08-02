#pragma once
#include "Includes.h"
#include "GameObject.h"

class BaseObject
{
public:
	uint64_t Address;

	BaseObject(uint64_t Addr)
	{
		Address = Addr;
	}

	GameObject GetGameObject()
	{
		return GameObject(EscapeFromTarkov.ReadMemory<uint64_t>(Address + 0x10));
	}

	BaseObject GetNextBaseObject()
	{
		return BaseObject(EscapeFromTarkov.ReadMemory<uint64_t>(Address + 0x8));
	}

};