/*
 *	memory.hpp
 *	Isabelle
 *
 *	Created by Azurilex on 04/27/2019
 *	Last edited by Azurilex on 04/27/2019
 *	Copyright © 2019 Azurilex. All rights reserved.
 *	Copyright © 2019 Ice Bear. All rights reserved.
 *	Copyright © 2019 Louka. All rights reserved.
 *	Precompiles functions used in memory.cpp
 */

#ifndef MEMORY_HPP
#define MEMORY_HPP

#pragma once
#include "globals.hpp"
#include <vector>

 /* - Memory Definitions - */
class Memory
{
	struct memdata
	{
		DWORD addr;
		BYTE* backup;
		int len;
	};

	static std::vector<memdata> data;
	static bool writeMemory(void* address, const void* patch, size_t sz);
	static void* hook(void* object, int index, void* targetf);
	static void writeBytes(DWORD addr, BYTE* bytes, int len);
	static bool compareBytes(const BYTE* pData, const BYTE* bMask, const char* szMask);
	static DWORD comparePattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask);
	static const char* getclass(int self);
	
public:
	static void* placeHook(DWORD address, void* hook, bool revert = false);
	static DWORD findPattern(DWORD mode, char* content, char* mask);
	static DWORD scanSignature(char* content, char* mask);
	static int findfirstclass(int Instance, const char* Name);
	static int getdm();
};

#endif
