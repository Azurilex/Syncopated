/*
 *	globals.hpp
 *	Isabelle
 *
 *	Created by Azurilex on 04/27/2019
 *	Copyright © 2019 Azurilex. All rights reserved.
 *	Memory scanning and locations for Roblox
 */

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#pragma once
#include <Windows.h>
#include <iostream>
#include "Libraries/termcolor/termcolor.hpp"

// GLOBAL DEFINES
#define ETERNALBYPASS_DEF 1
#define BRANDONBYPASS_DEF 2
#define JBRRBYPASS_DEF 3

// OFFSETS
#define PARENT_OFF 0x34

// ASLR MEMORY SCANNER
#define MODULEBASE reinterpret_cast<DWORD>(GetModuleHandleA(NULL))
#define IDABASE 0x400000
#define SCANADDRESS(x) (MODULEBASE + (x) - IDABASE)

// GLOBAL LUA STATE ENCRYPTION
//#define GS_ENCRYPTION(v40, v47) ((int)(v40[14 * v47 + 41] - reinterpret_cast<DWORD>(&v40[14 * v47 + 41])));

// MISC. MEMORY ADDRESSES
//#define SCRIPTCONTEXT_ADDR SCANADDRESS(0x1A97C24)
//#define DATAMODEL_ADDR SCANADDRESS(0xE3C260)

// LUA C API MEMORY ADDRESSES
// 
// THREAD RELATED
#define RLUA_NEWTHREAD_ADDR SCANADDRESS(0x11E05B0)
#define RLUA_GETTOP_ADDR SCANADDRESS(0x11E0270)

// PUSH ON STACK
#define RLUA_PUSHSTRING_ADDR SCANADDRESS(0x11E0C50)
#define RLUA_PUSHNUMBER_ADDR SCANADDRESS(0x11E0BF0)
#define RLUA_PUSHBOOLEAN_ADDR SCANADDRESS(0x11E08F0)

// EX.
#define RLUA_GETFIELD_ADDR SCANADDRESS(0x11E0080)
#define RLUA_PCALL_ADDR SCANADDRESS(0x11E0830)

// LUA C API RETURN CHECK JB INSTRUCTION MEMORY ADDRESSES
// USED IN THE JBRR RETURN CHECK BYPASS
// 
// THREAD RELATED
#define RLUA_NEWTHREAD_JB (RLUA_NEWTHREAD_ADDR + 0x4C)

// PUSH ON STACK
#define RLUA_PUSHSTRING_JB (RLUA_PUSHSTRING_ADDR + 0xB1)
#define RLUA_PUSHSTRING_NIL_JB (RLUA_PUSHSTRING_ADDR + 0x2B)
#define RLUA_PUSHNUMBER_JB (RLUA_PUSHNUMBER_ADDR + 0x37)
#define RLUA_PUSHBOOLEAN_JB (RLUA_PUSHNUMBER_ADDR + 0x2E)

// EX.
#define RLUA_GETFIELD_JB (RLUA_GETFIELD_ADDR + 0x81)
#define RLUA_PCALL_JB (RLUA_PCALL_ADDR + 0x96)

//x86 ASSEMBLY INSTRUCTION OPCODES
enum opcodes
{
	jmp = 0xEB,
	jb = 0x72,
	ret = 0xC3,
	call = 0xE8,
	mov_eax = 0xA1,
	mov_r16 = 0x8B,
	in = 0xEC,
	push = 0x55,
	
};

// PROPER C++17 GLOBAL VARIABLES
inline PDWORD ScriptContext;
inline int rbx_L;
inline int temporary_state;
inline int DataModel;
inline const char* PlayerName;
inline int retcheck_bypass_interval;

#endif