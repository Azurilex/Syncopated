/*
 *	rbxlua.cpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	Declerations of rLua C API functions, object oriented.
 */

#include "rbxlua.hpp"

rlua::rlua(int rL): interval(0)
{
	state = rL;
}

rlua::~rlua() = default;

int rlua::lua_newthread(int thread)
{
	const auto eternal = reinterpret_cast<lua::lua_newthread_def>(eternal_unprotect(RLUA_NEWTHREAD_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_newthread_def>(Bypass::retcheck_unprotect(RLUA_NEWTHREAD_ADDR));
	switch (interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(thread);
	case BRANDONBYPASS_DEF:
		return brandon(thread);
	case JBRRBYPASS_DEF:
		{
			write_instruction(RLUA_NEWTHREAD_JB, jmp);
			const int ret = lua_newthread_func(thread);
			write_instruction(RLUA_NEWTHREAD_JB, jb);
			return ret;
		}
	default:
		return lua_newthread_func(thread);
	}
}

int rlua::lua_getfield(int a2, const char* a3)
{
	const auto eternal = reinterpret_cast<lua::lua_getfield_def>(eternal_unprotect(RLUA_GETFIELD_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_getfield_def>(Bypass::retcheck_unprotect(RLUA_GETFIELD_ADDR));
	switch (interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2, a3);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2, a3);
	case JBRRBYPASS_DEF:
		{
			write_instruction(RLUA_GETFIELD_JB, jmp);
			const int ret = lua_getfield_func(state, a2, a3);
			write_instruction(RLUA_GETFIELD_JB, jb);
			return ret;
		}
	default:
		return lua_getfield_func(state, a2, a3);
	}
}

const char* rlua::lua_tolstring(int a2, size_t a3)
{
	const auto eternal = reinterpret_cast<lua::lua_tolstring_def>(eternal_unprotect(RLUA_TOLSTRING_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_tolstring_def>(Bypass::retcheck_unprotect(RLUA_TOLSTRING_ADDR));
	switch (interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2, a3);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2, a3);
	case JBRRBYPASS_DEF:
		{
			/*
			 * 2 cases in which retcheck can be called, so we jmp both
			 */
			write_instruction(RLUA_TOLSTRING_JB_1, jmp);
			write_instruction(RLUA_TOLSTRING_JB_2, jmp);
			const char* ret = lua_tolstring_func(state, a2, a3);
			write_instruction(RLUA_TOLSTRING_JB_1, jb);
			write_instruction(RLUA_TOLSTRING_JB_2, jb);
			return ret;
		}
	default:
		return lua_tolstring_func(state, a2, a3);
	}
}

int rlua::lua_pushstring(const char* a2)
{
	const auto eternal = reinterpret_cast<lua::lua_pushstring_def>(eternal_unprotect(RLUA_PUSHSTRING_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_pushstring_def>(Bypass::retcheck_unprotect(RLUA_PUSHSTRING_ADDR));
	switch (interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2);
	case JBRRBYPASS_DEF:
		{
			DWORD dw;
			if (a2 == nullptr)
			{
				dw = RLUA_PUSHSTRING_NIL_JB;
			}
			else
			{
				dw = RLUA_PUSHSTRING_JB;
			}
			
			write_instruction(dw, jmp);
			const int ret = lua_pushstring_func(state, a2);
			write_instruction(dw, jb);
			return ret;
		}
	default:
		return lua_pushstring_func(state, a2);
	}
}

int rlua::lua_pushnumber(double a2)
{
	const auto eternal = reinterpret_cast<lua::lua_pushnumber_def>(eternal_unprotect(RLUA_PUSHNUMBER_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_pushnumber_def>(Bypass::retcheck_unprotect(RLUA_PUSHNUMBER_ADDR));
	switch (interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2);
	case JBRRBYPASS_DEF:
		{
			write_instruction(RLUA_PUSHNUMBER_JB, jmp);
			const int ret = lua_pushnumber_func(state, a2);
			write_instruction(RLUA_PUSHNUMBER_JB, jb);
			return ret;
		}
	default:
		return lua_pushnumber_func(state, a2);
	}
}

int rlua::lua_pushboolean(bool a2)
{
	const auto eternal = reinterpret_cast<lua::lua_pushboolean_def>(eternal_unprotect(RLUA_PUSHBOOLEAN_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_pushboolean_def>(Bypass::retcheck_unprotect(RLUA_PUSHBOOLEAN_ADDR));
	switch (interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2);
	case JBRRBYPASS_DEF:
		{
			write_instruction(RLUA_PUSHBOOLEAN_JB, jmp);
			const int ret = lua_pushboolean_func(state, a2);
			write_instruction(RLUA_PUSHBOOLEAN_JB, jb);
			return ret;
		}
	default:
		return lua_pushboolean_func(state, a2);
	}
}

int rlua::lua_pcall(int a2, int a3, int a4)
{
	const auto eternal = reinterpret_cast<lua::lua_pcall_def>(eternal_unprotect(RLUA_PCALL_ADDR));
	const auto brandon = reinterpret_cast<lua::lua_pcall_def>(Bypass::retcheck_unprotect(RLUA_PCALL_ADDR));
	switch (interval)
	{
	case ETERNALBYPASS_DEF:
		return eternal(state, a2, a3, a4);
	case BRANDONBYPASS_DEF:
		return brandon(state, a2, a3, a4);
	case JBRRBYPASS_DEF:
		{
			write_instruction(RLUA_PCALL_JB, jmp);
			const int ret = lua_pcall_func(state, a2, a3, a4);
			write_instruction(RLUA_PCALL_JB, jb);
			return ret;
		}
	default:
		return lua_pcall_func(state, a2, a3, a4);
	}
}

int rlua::get_bypass()
{
	return interval;
}

void rlua::set_bypass(int i)
{
	interval = i;
}

int rlua::get_state()
{
	return state;
}

std::string get_localplayer(rlua entity)
{
	entity.lua_getfield(-10002, "game");
	entity.lua_getfield(-1, "Players");
	entity.lua_getfield(-1, "LocalPlayer");
	entity.lua_getfield(-1, "Name");
	return entity.lua_tolstring(-1, NULL);
}
