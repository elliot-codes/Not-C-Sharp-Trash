#include "Includes.h"
#include "BaseObject.h"

class GameObjectManager
{
public:
	uint64_t Address;

	GameObjectManager(uint64_t Addr)
	{
		Address = Addr;
	}

	BaseObject GetLastTaggedObject()
	{
		return EscapeFromTarkov.ReadMemory<uint64_t>(Address);
	}

	BaseObject GetFirstTaggedObject()
	{
		return EscapeFromTarkov.ReadMemory<uint64_t>(Address + 0x8);
	}

	BaseObject GetLastActiveObject()
	{
		return EscapeFromTarkov.ReadMemory<uint64_t>(Address + 0x10);
	}

	BaseObject GetFirstActiveObject()
	{
		return EscapeFromTarkov.ReadMemory<uint64_t>(Address + 0x18);
	}
};