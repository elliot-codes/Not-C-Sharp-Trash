#pragma once
#include "Includes.h"
#include "GameWorld.h"

class GameObject
{
public:
	uint64_t Address;

	GameObject(uint64_t Addr)
	{
		Address = Addr;
	}

	std::string GetGameObjectName()
	{
		std::string result;
		uint64_t GameObjectNameAddr = EscapeFromTarkov.ReadMemory<uint64_t>(Address + 0x60);
		for (int i = 0; i <= 100; i++)
		{
			char CurrentChar = EscapeFromTarkov.ReadMemory<char>(GameObjectNameAddr + i);
			result.push_back(CurrentChar);
		}
		return result;
	}

	uint64_t GetGameComponent()
	{
		uint64_t ObjectClass = EscapeFromTarkov.ReadMemory<uint64_t>(Address + 0x30);
		uint64_t Entity = EscapeFromTarkov.ReadMemory<uint64_t>(ObjectClass + 0x18);
		uint64_t BaseEntity = EscapeFromTarkov.ReadMemory<uint64_t>(Entity + 0x28);
		return BaseEntity;
	}

	GameWorld GetLocalGameWorld()
	{
		return GameWorld(GetGameComponent());
	}

};