/*
 *	memory.hpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	Copyright © 2020 Louka. All rights reserved.
 *	Functions used to scan Roblox's memory
 */

#ifndef MEMORY_HPP
#define MEMORY_HPP

#pragma once
#include "globals.hpp"
#include <vector>

/* - Memory Definitions - */

class Memory
{
	struct Memdata
	{
		DWORD addr;
		BYTE* backup;
		int len;
	};

	static std::vector<Memdata> data;
	static bool write_memory(void* address, const void* patch, size_t sz);
	static void write_bytes(DWORD addr, BYTE* bytes, int len);
	static bool compare_bytes(const BYTE* pData, const BYTE* bMask, const char* szMask);
	static DWORD compare_pattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask);

public:
	static DWORD find_pattern(DWORD mode, char* content, char* mask);
	static DWORD scan_signature(char* content, char* mask);
};

#endif
