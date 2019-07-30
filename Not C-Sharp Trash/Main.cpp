#include "EscapeFromTarkov.h"

int main()
{
	Process EscapeFromTarkov(L"EscapeFromTarkov.exe", "EscapeFromTarkov.exe");

	printf("PID: %i\n", EscapeFromTarkov.PID);
	printf("Handle: %i\n", (uint32_t)EscapeFromTarkov.hAccess);
	printf("Base Address: %p\n", EscapeFromTarkov.BaseAddress);

	uint64_t GOM = EscapeFromTarkov.ReadMemory<uint64_t>(EscapeFromTarkov.BaseAddress + 0x1432840);

	printf("GOM: %p\n", GOM);

	system("pause");
}