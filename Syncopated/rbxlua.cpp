#include "rbxlua.hpp"

int rlua::state;

rlua::rlua(int rL)
{
	state = rL;
}

rlua::~rlua() = default;

int rlua::lua_newthread(int thread)
{
	int ret;
	auto lua_newthread_func_eternal = reinterpret_cast<lua::lua_newthread_def>(eternal_unprotect(RLUA_NEWTHREAD_ADDR));
	auto lua_newthread_func_brandon = reinterpret_cast<lua::lua_newthread_def>(brandon_retcheck::retcheckunprotect(RLUA_NEWTHREAD_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = lua_newthread_func_eternal(thread);
		break;
	case BRANDONBYPASS_DEF:
		ret = lua_newthread_func_brandon(thread);
		break;
	case JBRRBYPASS_DEF:
		instruction_jmp(RLUA_NEWTHREAD_JB);
		ret = lua_newthread_func(thread);
		instruction_jb(RLUA_NEWTHREAD_JB);
		break;
	case 4:
	default:
		ret = lua_newthread_func(thread);
		break;
	}
	return ret;
}

int rlua::lua_getfield(int a2, const char* a3)
{
	int ret;
	auto lua_getfield_func_eternal = reinterpret_cast<lua::lua_getfield_def>(eternal_unprotect(RLUA_GETFIELD_ADDR));
	auto lua_getfield_func_brandon = reinterpret_cast<lua::lua_getfield_def>(brandon_retcheck::retcheckunprotect(RLUA_GETFIELD_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = lua_getfield_func_eternal(state, a2, a3);
		break;
	case BRANDONBYPASS_DEF:
		ret = lua_getfield_func_brandon(state, a2, a3);
		break;
	case JBRRBYPASS_DEF:
		instruction_jmp(RLUA_GETFIELD_JB);
		ret = lua_getfield_func(state, a2, a3);
		instruction_jb(RLUA_GETFIELD_JB);
		break;
	default:
		ret = lua_getfield_func(state, a2, a3);
		break;
	}
	return ret;
}

int rlua::lua_pushstring(const char* a2)
{
	int ret;
	auto lua_pushstring_func_eternal = reinterpret_cast<lua::lua_pushstring_def>(eternal_unprotect(RLUA_PUSHSTRING_ADDR));
	auto lua_pushstring_func_brandon = reinterpret_cast<lua::lua_pushstring_def>(brandon_retcheck::retcheckunprotect(RLUA_PUSHSTRING_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = lua_pushstring_func_eternal(state, a2);
		break;
	case BRANDONBYPASS_DEF:
		ret = lua_pushstring_func_brandon(state, a2);
		break;
	case JBRRBYPASS_DEF:
		//instruction_jmp(RLUA_PUSHSTRING_NIL_JB);
		instruction_jmp(RLUA_PUSHSTRING_JB);
		ret = lua_pushstring_func(state, a2);
		//instruction_jb(RLUA_PUSHSTRING_NIL_JB);
		instruction_jb(RLUA_PUSHSTRING_JB);
		break;
	default:
		ret = lua_pushstring_func(state, a2);
		break;
	}
	return ret;
}

int rlua::lua_pushnumber(double a2)
{
	int ret;
	auto lua_pushnumber_func_eternal = reinterpret_cast<lua::lua_pushnumber_def>(eternal_unprotect(RLUA_PUSHNUMBER_ADDR));
	auto lua_pushnumber_func_brandon = reinterpret_cast<lua::lua_pushnumber_def>(brandon_retcheck::retcheckunprotect(RLUA_PUSHNUMBER_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = lua_pushnumber_func_eternal(state, a2);
		break;
	case BRANDONBYPASS_DEF:
		ret = lua_pushnumber_func_brandon(state, a2);
		break;
	case JBRRBYPASS_DEF:
		instruction_jmp(RLUA_PUSHNUMBER_JB);
		ret = lua_pushnumber_func(state, a2);
		instruction_jb(RLUA_PUSHNUMBER_JB);
		break;
	default:
		ret = lua_pushnumber_func(state, a2);
		break;
	}
	return ret;
}

int rlua::lua_pushboolean(bool a2)
{
	int ret;
	auto lua_pushboolean_func_eternal = reinterpret_cast<lua::lua_pushboolean_def>(eternal_unprotect(RLUA_PUSHBOOLEAN_ADDR));
	auto lua_pushboolean_func_brandon = reinterpret_cast<lua::lua_pushboolean_def>(brandon_retcheck::retcheckunprotect(RLUA_PUSHBOOLEAN_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = lua_pushboolean_func_eternal(state, a2);
		break;
	case BRANDONBYPASS_DEF:
		ret = lua_pushboolean_func_brandon(state, a2);
		break;
	case JBRRBYPASS_DEF:
		instruction_jmp(RLUA_PUSHBOOLEAN_JB);
		ret = lua_pushboolean_func(state, a2);
		instruction_jb(RLUA_PUSHBOOLEAN_JB);
		break;
	default:
		ret = lua_pushboolean_func(state, a2);
		break;
	}
	return ret;
}

int rlua::lua_pcall(int a2, int a3, int a4)
{
	int ret;
	auto lua_pcall_func_eternal = reinterpret_cast<lua::lua_pcall_def>(eternal_unprotect(RLUA_PCALL_ADDR));
	auto lua_pcall_func_brandon = reinterpret_cast<lua::lua_pcall_def>(brandon_retcheck::retcheckunprotect(RLUA_PCALL_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = lua_pcall_func_eternal(state, a2, a3, a4);
		break;
	case BRANDONBYPASS_DEF:
		ret = lua_pcall_func_brandon(state, a2, a3, a4);
		break;
	case JBRRBYPASS_DEF:
		instruction_jmp(RLUA_PCALL_JB);
		ret = lua_pcall_func(state, a2, a3, a4);
		instruction_jb(RLUA_PCALL_JB);
		break;
	default:
		ret = lua_pcall_func(state, a2, a3, a4);
		break;
	}
	return ret;
}
