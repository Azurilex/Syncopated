/*
* memory.cpp
* Isabelle
*
* Created by Azurilex on 02 / 27 / 2017
* Last edited by Azurilex on 04 / 08 / 2019
* Copyright © 2019 Azurilex.All rights reserved.
* Functions that hacks / scans Roblox's memory.
*/

#include "memory.hpp"

/* - Scan Address / Scan Signature - */

std::vector<Memory::memdata> Memory::data;

bool Memory::writeMemory(void* address, const void* patch, size_t sz)
{
	DWORD protect;

	if (!VirtualProtect(address, sz, PAGE_EXECUTE_READWRITE, &protect)) return false;
	memcpy(address, patch, sz);
	return VirtualProtect(address, sz, protect, static_cast<PDWORD>(&protect)) != 0;
}

void* Memory::hook(void* object, int index, void* targetf)
{
	int* vftable = *static_cast<int**>(object);
	auto* previous = reinterpret_cast<void*>(vftable[index]);

	writeMemory(vftable + index, &targetf, sizeof(void*));

	return previous;
}

void Memory::writeBytes(DWORD addr, BYTE* bytes, int len)
{
	auto* backup = new BYTE[len + 32];
	memcpy(backup, reinterpret_cast<void*>(addr - 16), len + 32);
	data.push_back({ addr - 16, backup, len });

	DWORD oldProt;
	VirtualProtect(reinterpret_cast<void*>(addr), len, PAGE_EXECUTE_READWRITE, &oldProt);
	memcpy(reinterpret_cast<void*>(addr), bytes, len);
	VirtualProtect(reinterpret_cast<void*>(addr), len, oldProt, &oldProt);
}

bool Memory::compareBytes(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask) return false;
	return *szMask == NULL;
}


DWORD Memory::comparePattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask)
{
	for (int i = 0; i < static_cast<int>(dwLen); i++)
		if (compareBytes(reinterpret_cast<BYTE*>(dwAddress + static_cast<int>(i)), bMask, szMask))
			return
			static_cast<int>(dwAddress + i);
	return 0;
}

const char* Memory::getclass(int self)
{
	return (const char*)(*(int(**)(void))(*(int*)self + 16))();
}

int Memory::findfirstclass(int Instance, const char* Name)
{
	DWORD StartOfChildren = *reinterpret_cast<DWORD*>(Instance + 0x2C);
	DWORD EndOfChildren = *reinterpret_cast<DWORD*>(StartOfChildren + 4);

	for (int i = *(int*)StartOfChildren; i != EndOfChildren; i += 8)
	{
		if (memcmp(getclass(*reinterpret_cast<int*>(i)), Name, strlen(Name)) == 0)
		{
			return *reinterpret_cast<int*>(i);
		}
	}
	return 0;
}

int Memory::getdm()
{
	int datamodel[] = { 0,0 };
	((int(__stdcall*)(int*))SCANADDRESS(0xE3C3B0))(datamodel);
	return datamodel[0] + 68;
}

void* Memory::placeHook(DWORD address, void* hook, bool revert)
{
	DWORD oldprot;
	if (!revert) {
		void* oldmem = new void*;
		void* result = new void*;
		memcpy(oldmem, reinterpret_cast<void*>(address), sizeof(void*) * 4);
		VirtualProtect(reinterpret_cast<LPVOID>(address), 1, PAGE_EXECUTE_READWRITE, &oldprot);
		*reinterpret_cast<char*>(address) = 0xE9; *reinterpret_cast<DWORD*>(address + 1) = reinterpret_cast<DWORD>(hook) - address - 5;
		memcpy(result, oldmem, sizeof(void*) * 4);
		VirtualProtect(reinterpret_cast<LPVOID>(address), 1, oldprot, &oldprot);
		return result;
	}
	else {
		VirtualProtect(reinterpret_cast<LPVOID>(address), 1, PAGE_EXECUTE_READWRITE, &oldprot);
		memcpy(reinterpret_cast<void*>(address), hook, sizeof(void*) * 4);
		VirtualProtect(reinterpret_cast<LPVOID>(address), 1, oldprot, &oldprot);
		return nullptr;
	}
}

DWORD Memory::findPattern(DWORD mode, char* content, char* mask)
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	DWORD PageSize = si.dwPageSize;
	MEMORY_BASIC_INFORMATION mi;
	for (auto lpAddr = reinterpret_cast<DWORD>(GetProcessHeap()); lpAddr < 0x7FFFFFFF; lpAddr += PageSize)
	{
		DWORD vq = VirtualQuery(reinterpret_cast<void*>(lpAddr), &mi, PageSize);
		if (vq == ERROR_INVALID_PARAMETER || vq == 0) break;
		if (mi.Type == MEM_MAPPED) continue;
		if (mi.Protect == mode)
		{
			int addr = comparePattern(lpAddr, PageSize, reinterpret_cast<PBYTE>(content), mask);
			if (addr != 0)
			{
				return addr;
			}
		}
	}
	return 0;
}

DWORD Memory::scanSignature(char* content, char* mask)
{
	return comparePattern(reinterpret_cast<DWORD>(GetProcessHeap()), 0xF00000, reinterpret_cast<PBYTE>(content),
		mask);
}