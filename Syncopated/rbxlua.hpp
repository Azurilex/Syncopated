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
	typedef int (__cdecl* rlua_newthread_def)(int);
	typedef int(__cdecl* rlua_gettop_def)(int);
	
	// PUSH ON STACK
	typedef int(__stdcall* rlua_pushstring_def)(int, const char*);
	typedef int(__cdecl* rlua_pushnumber_def)(int, double);
	typedef int(__cdecl* rlua_pushboolean_def)(int, bool);
	
	// EX.
	typedef int (__cdecl* rlua_getfield_def)(int, int, const char*);
	typedef int (__cdecl* rlua_pcall_def)(DWORD *, int, int, int);
	
}

//ok so ur probably wondering why im using namespaces, because this shit is gay - I KNOW
//but it's the only way i could think of to incoorporate variable's bypass without making the code even more gay
//so this is the LEAST gay way to do this. variable's bypass is gay, so this is the least amount of gay it can be


// THREAD RELATED
static lua::rlua_newthread_def rlua_newthread_func = reinterpret_cast<lua::rlua_newthread_def>(RLUA_NEWTHREAD_ADDR);
int rlua_newthread(int a1);

static lua::rlua_gettop_def rlua_gettop = reinterpret_cast<lua::rlua_gettop_def>(RLUA_GETTOP_ADDR);


// PUSH ON STACK
static lua::rlua_pushstring_def rlua_pushstring_func = reinterpret_cast<lua::rlua_pushstring_def>(RLUA_PUSHSTRING_ADDR);
int rlua_pushstring(int a1, const char* a2);

static lua::rlua_pushnumber_def rlua_pushnumber_func = reinterpret_cast<lua::rlua_pushnumber_def>(RLUA_PUSHNUMBER_ADDR);
int rlua_pushnumber(int a1, double a2);

static lua::rlua_pushboolean_def rlua_pushboolean_func = reinterpret_cast<lua::rlua_pushboolean_def>(RLUA_PUSHBOOLEAN_ADDR);
int rlua_pushboolean(int a1, bool a2);


// EX.
static lua::rlua_getfield_def rlua_getfield_func = reinterpret_cast<lua::rlua_getfield_def>(RLUA_GETFIELD_ADDR);
int rlua_getfield(int a1, int a2, const char* a3);

static lua::rlua_pcall_def rlua_pcall_func = reinterpret_cast<lua::rlua_pcall_def>(RLUA_PCALL_ADDR);
int rlua_pcall(DWORD *a1, int a2, int a3, int a4);



#endif