/*
 *	rbxlua.cpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	Declerations of rLua C API functions, object oriented.
 */

#include "rbxlua.hpp"

int rlua::state;

rlua::rlua(int rL)
{
	state = rL;
}

rlua::~rlua() = default;

int rlua::lua_newthread(int thread)
{
	const auto eternal = reinterpret_cast<lua::lua_newthread_def>(eternal_unprotect(RLUA_NEWTHREAD_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_newthread_def>(brandon_retcheck::retcheckunprotect(RLUA_NEWTHREAD_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(thread);
	case BRANDONBYPASS_DEF:
		return brandon(thread);
	case JBRRBYPASS_DEF:
	{
		instruction_jmp(RLUA_NEWTHREAD_JB);
		const int ret = lua_newthread_func(thread);
		instruction_jb(RLUA_NEWTHREAD_JB);
		return ret;
	}
	default:
		return lua_newthread_func(thread);
	}
}

int rlua::lua_getfield(int a2, const char* a3)
{
	const auto eternal = reinterpret_cast<lua::lua_getfield_def>(eternal_unprotect(RLUA_GETFIELD_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_getfield_def>(brandon_retcheck::retcheckunprotect(RLUA_GETFIELD_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2, a3);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2, a3);
	case JBRRBYPASS_DEF:
	{
		instruction_jmp(RLUA_GETFIELD_JB);
		const int ret = lua_getfield_func(state, a2, a3);
		instruction_jb(RLUA_GETFIELD_JB);
		return ret;
	}
	default:
		return lua_getfield_func(state, a2, a3);
	}
}

int rlua::lua_pushstring(const char* a2)
{
	const auto eternal = reinterpret_cast<lua::lua_pushstring_def>(eternal_unprotect(RLUA_PUSHSTRING_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_pushstring_def>(brandon_retcheck::retcheckunprotect(RLUA_PUSHSTRING_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2);
	case JBRRBYPASS_DEF:
	{
		//instruction_jmp(RLUA_PUSHSTRING_NIL_JB);
		instruction_jmp(RLUA_PUSHSTRING_JB);
		const int ret = lua_pushstring_func(state, a2);
		//instruction_jb(RLUA_PUSHSTRING_NIL_JB);
		instruction_jb(RLUA_PUSHSTRING_JB);
		return ret;
	}
	default:
		return lua_pushstring_func(state, a2);
	}
}

int rlua::lua_pushnumber(double a2)
{
	const auto eternal = reinterpret_cast<lua::lua_pushnumber_def>(eternal_unprotect(RLUA_PUSHNUMBER_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_pushnumber_def>(brandon_retcheck::retcheckunprotect(RLUA_PUSHNUMBER_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2);
	case JBRRBYPASS_DEF:
	{
		instruction_jmp(RLUA_PUSHNUMBER_JB);
		const int ret = lua_pushnumber_func(state, a2);
		instruction_jb(RLUA_PUSHNUMBER_JB);
		return ret;
	}
	default:
		return lua_pushnumber_func(state, a2);
	}
}

int rlua::lua_pushboolean(bool a2)
{
	const auto eternal = reinterpret_cast<lua::lua_pushboolean_def>(eternal_unprotect(RLUA_PUSHBOOLEAN_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_pushboolean_def>(brandon_retcheck::retcheckunprotect(RLUA_PUSHBOOLEAN_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2);
	case JBRRBYPASS_DEF:
	{
		instruction_jmp(RLUA_PUSHBOOLEAN_JB);
		const int ret = lua_pushboolean_func(state, a2);
		instruction_jb(RLUA_PUSHBOOLEAN_JB);
		return ret;
	}
	default:
		return lua_pushboolean_func(state, a2);
	}
}

int rlua::lua_pcall(int a2, int a3, int a4)
{
	const auto eternal = reinterpret_cast<lua::lua_pcall_def>(eternal_unprotect(RLUA_PCALL_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_pcall_def>(brandon_retcheck::retcheckunprotect(RLUA_PCALL_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2, a3, a4);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2, a3, a4);
	case JBRRBYPASS_DEF:
	{
		instruction_jmp(RLUA_PCALL_JB);
		const int ret = lua_pcall_func(state, a2, a3, a4);
		instruction_jb(RLUA_PCALL_JB);
		return ret;
	}
	default:
		return lua_pcall_func(state, a2, a3, a4);
	}
}
