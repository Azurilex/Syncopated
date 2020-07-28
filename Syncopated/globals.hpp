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

#define ETERNALBYPASS_DEF 1
#define BRANDONBYPASS_DEF 2
#define JBRRBYPASS_DEF 3

#define PARENT_OFF 0x34

#define MODULEBASE reinterpret_cast<DWORD>(GetModuleHandleA(NULL))
#define IDABASE 0x400000
#define SCANADDRESS(x) (MODULEBASE + (x) - IDABASE)

#define GS_ENCRYPTION(v40, v47) ((int)(v40[14 * v47 + 41] - reinterpret_cast<DWORD>(&v40[14 * v47 + 41])));

#define SCRIPTCONTEXT_ADDR SCANADDRESS(0x1A97C24)
#define DATAMODEL_ADDR SCANADDRESS(0xE3C260)

#define RLUA_GETTOP_ADDR SCANADDRESS(0x11d7d80)
#define RLUA_NEWTHREAD_ADDR SCANADDRESS(0x11d80b0)
#define RLUA_GETFIELD_ADDR SCANADDRESS(0x11D7BB0)
#define RLUA_PUSHSTRING_ADDR SCANADDRESS(0x11D8770)
#define RLUA_PCALL_ADDR SCANADDRESS(0x11D8330)

#define RLUA_NEWTHREAD_JB (RLUA_NEWTHREAD_ADDR + 0x54)
#define RLUA_GETFIELD_JB (RLUA_GETFIELD_ADDR + 0x81)
#define RLUA_PUSHSTRING_JB (RLUA_PUSHSTRING_ADDR + 0x74)
#define RLUA_PCALL_JB (RLUA_PCALL_ADDR + 0x93)

inline PDWORD ScriptContext;
inline int rbx_L;
inline int temporary_state;
inline int DataModel;
inline const char* PlayerName;
inline int retcheck_bypass_interval;

#endif