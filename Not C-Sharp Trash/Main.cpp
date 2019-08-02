#include "EscapeFromTarkov.h"
#include "GameObjectManager.h"

namespace Objects
{
	GameObjectManager GOM{ 0x0 };
	GameWorld LocalGameWorld{0x0};
}

GameWorld FindLocalGameWorld()
{
	for (BaseObject ActiveObject = Objects::GOM.GetFirstActiveObject(); ActiveObject.Address != Objects::GOM.GetLastActiveObject().Address; ActiveObject = ActiveObject.GetNextBaseObject())
	{
		std::string ActiveObjectName = ActiveObject.GetGameObject().GetGameObjectName();
		if (ActiveObjectName.find("GameWorld") != std::string::npos)
		{
			return ActiveObject.GetGameObject().GetLocalGameWorld();
		}
	}
}

int main()
{
	printf("PID: %i\n", EscapeFromTarkov.PID);
	printf("Handle: %i\n", (uint32_t)EscapeFromTarkov.hAccess);
	printf("Base Address: %p\n", EscapeFromTarkov.BaseAddress);

	Objects::GOM = EscapeFromTarkov.ReadMemory<uint64_t>(EscapeFromTarkov.BaseAddress + 0x1432840);
	printf("GOM: %p\n", Objects::GOM.Address);

	Objects::LocalGameWorld = FindLocalGameWorld();
	printf("Local Game World: %p\n", Objects::LocalGameWorld.Address);

	system("pause");
}