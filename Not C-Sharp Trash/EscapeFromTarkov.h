#pragma once
#include "Includes.h"

#pragma warning (disable: 4996)

class Process
{
	uint32_t FindByProcessName(const wchar_t* processName)
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (snapshot == INVALID_HANDLE_VALUE) return 0U;

		PROCESSENTRY32W processEntry;
		processEntry.dwSize = sizeof(PROCESSENTRY32W);

		DWORD PID = 0U;

		if (Process32FirstW(snapshot, &processEntry))
		{
			do
			{
				if (lstrcmpiW(processEntry.szExeFile, processName) == 0)
				{
					PID = processEntry.th32ProcessID;
					break;
				}
			} while (Process32NextW(snapshot, &processEntry));
		}

		CloseHandle(snapshot);

		return PID;
	}

	uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName)
	{
		uintptr_t modBaseAddr = 0;
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
		if (hSnap != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 modEntry;
			modEntry.dwSize = sizeof(modEntry);
			if (Module32First(hSnap, &modEntry))
			{
				do
				{
					if (!strcmp(modEntry.szModule, modName))
					{
						modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
						break;
					}
				} while (Module32Next(hSnap, &modEntry));
			}
		}
		CloseHandle(hSnap);
		return modBaseAddr;
	}

public:
	HANDLE hAccess;
	uint32_t PID = 0;
	uint64_t BaseAddress;

	Process(const wchar_t* chProcessNameW, const char* chProcessName)
	{
		PID = FindByProcessName(chProcessNameW);
		hAccess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
		BaseAddress = GetModuleBaseAddress(PID, chProcessName);
	}

	bool ReadMemory(uint64_t Address, void* Buffer, const size_t Size)
	{
		SIZE_T bytesRead;
		if (ReadProcessMemory(hAccess, reinterpret_cast<LPCVOID>(Address), Buffer, Size, &bytesRead))
			return bytesRead == Size;

		return false;
	}

	template <typename T>
	T ReadMemory(uint64_t Address)
	{
		T Buffer = {};

		if (ReadMemory(Address, (void*)& Buffer, sizeof(Buffer)))
			return Buffer;
		else
			return {};
	}
};