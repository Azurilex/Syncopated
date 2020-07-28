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

#define RLUA_TNONE (-1)

namespace lua
{
	enum thread_status
	{
		success,
		yield,
		errrun,
		errsyntax,
		errmem,
		errerr
	};

	typedef int(__cdecl* rlua_newthread_def)(int);
	typedef char(__stdcall* rlua_getfield_def)(int, int, const char*);
	typedef char(__fastcall* rlua_pushstring_def)(int, const char*);
	typedef int(__cdecl* rlua_pcall_def)(int, int, int, int);
}

//ok so ur probably wondering why im using namespaces, because this shit is gay - I KNOW
//but it's the only way i could think of to incoorporate variable's bypass without making the code even more gay
//so this is the LEAST gay way to do this. variable's bypass is gay, so this is the least amount of gay it can be



static lua::rlua_newthread_def rlua_newthread_func = reinterpret_cast<lua::rlua_newthread_def>(RLUA_NEWTHREAD_ADDR);
int rlua_newthread(int a1);
static lua::rlua_getfield_def rlua_getfield_func = reinterpret_cast<lua::rlua_getfield_def>(RLUA_GETFIELD_ADDR);
char rlua_getfield(int a1, int a2, const char* a3);
static lua::rlua_pushstring_def rlua_pushstring_func = reinterpret_cast<lua::rlua_pushstring_def>(RLUA_PUSHSTRING_ADDR);
char rlua_pushstring(int a1, const char* a2);
static lua::rlua_pcall_def rlua_pcall_func = reinterpret_cast<lua::rlua_pcall_def>(RLUA_PCALL_ADDR);
int rlua_pcall(int a1, int a2, int a3, int a4);

#endif