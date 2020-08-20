/*
 *	rbxlua.hpp
 *	Isabelle
 *
 *	Created by Azurilex on 07/19/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	Initializes roblox's lua c functions
 */

#ifndef RBXLUA_HPP
#define RBXLUA_HPP

#pragma once
#include "bypasses.hpp"

namespace lua
{
	// THREAD RELATED
	typedef int (__cdecl* lua_newthread_def)(int);
	typedef int(__cdecl* lua_gettop_def)(int);
	
	// PUSH ON STACK
	typedef int(__stdcall* lua_pushstring_def)(int, const char*);
	typedef int(__stdcall* lua_pushnumber_def)(int, double);
	typedef int(__cdecl* lua_pushboolean_def)(int, bool);
	
	// EX.
	typedef int (__fastcall* lua_getfield_def)(int, int, const char*);
	typedef int (__cdecl* lua_pcall_def)(int, int, int, int);
	
}

class rlua {
	static int state;
public:
	//CONSTRUCTOR
	explicit rlua(int rL);
	//DECONSTRUCTOR
	~rlua();

	
	// THREAD RELATED
	const lua::lua_newthread_def lua_newthread_func = reinterpret_cast<lua::lua_newthread_def>(RLUA_NEWTHREAD_ADDR);
	int lua_newthread(int thread = state);

	const lua::lua_gettop_def lua_gettop = reinterpret_cast<lua::lua_gettop_def>(RLUA_GETTOP_ADDR);

	
	// PUSH ON STACK
	const lua::lua_pushstring_def lua_pushstring_func = reinterpret_cast<lua::lua_pushstring_def>(RLUA_PUSHSTRING_ADDR);
	int lua_pushstring(const char* a2);

	const lua::lua_pushnumber_def lua_pushnumber_func = reinterpret_cast<lua::lua_pushnumber_def>(RLUA_PUSHNUMBER_ADDR);
	int lua_pushnumber(double a2);

	const lua::lua_pushboolean_def lua_pushboolean_func = reinterpret_cast<lua::lua_pushboolean_def>(RLUA_PUSHBOOLEAN_ADDR);
	int lua_pushboolean(bool a2);


	// EX.
	const lua::lua_getfield_def lua_getfield_func = reinterpret_cast<lua::lua_getfield_def>(RLUA_GETFIELD_ADDR);
	int lua_getfield(int a2, const char* a3);

	const lua::lua_pcall_def lua_pcall_func = reinterpret_cast<lua::lua_pcall_def>(RLUA_PCALL_ADDR);
	int lua_pcall(int a2, int a3, int a4);

};



#endif