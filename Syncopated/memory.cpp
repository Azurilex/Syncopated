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