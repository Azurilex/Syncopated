#include "rbxlua.hpp"

int rlua_newthread(int a1)
{
	int ret;
	auto rlua_newthread_func_eternal = reinterpret_cast<lua::rlua_newthread_def>(eternal_unprotect(RLUA_NEWTHREAD_ADDR)
	);
	auto rlua_newthread_func_brandon = reinterpret_cast<lua::rlua_newthread_def>(brandon_retcheck::retcheckunprotect(
		RLUA_NEWTHREAD_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = rlua_newthread_func_eternal(a1);
		break;
	case BRANDONBYPASS_DEF:
		ret = rlua_newthread_func_brandon(a1);
		break;
	case JBRRBYPASS_DEF:
		variable_jump(RLUA_NEWTHREAD_JB);
		ret = rlua_newthread_func(a1);
		variable_replace(RLUA_NEWTHREAD_JB);
		break;
	case 4:
	default:
		ret = rlua_newthread_func(a1);
		break;
	}
	return ret;
}

char rlua_getfield(int a1, int a2, const char* a3)
{
	char ret;
	auto rlua_getfield_func_eternal = reinterpret_cast<lua::rlua_getfield_def>(eternal_unprotect(RLUA_GETFIELD_ADDR));
	auto rlua_getfield_func_brandon = reinterpret_cast<lua::rlua_getfield_def>(brandon_retcheck::retcheckunprotect(
		RLUA_GETFIELD_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = rlua_getfield_func_eternal(a1, a2, a3);
		break;
	case BRANDONBYPASS_DEF:
		ret = rlua_getfield_func_brandon(a1, a2, a3);
		break;
	case JBRRBYPASS_DEF:
		variable_jump(RLUA_GETFIELD_JB);
		ret = rlua_getfield_func(a1, a2, a3);
		variable_replace(RLUA_GETFIELD_JB);
		break;
	default:
		ret = rlua_getfield_func(a1, a2, a3);
		break;
	}
	return ret;
}

char rlua_pushstring(int a1, const char* a2)
{
	char ret;
	auto rlua_pushstring_func_eternal = reinterpret_cast<lua::rlua_pushstring_def>(eternal_unprotect(
		RLUA_PUSHSTRING_ADDR));
	auto rlua_pushstring_func_brandon = reinterpret_cast<lua::rlua_pushstring_def>(brandon_retcheck::retcheckunprotect(
		RLUA_PUSHSTRING_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = rlua_pushstring_func_eternal(a1, a2);
		break;
	case BRANDONBYPASS_DEF:

		ret = rlua_pushstring_func_brandon(a1, a2);
		break;
	case JBRRBYPASS_DEF:
		variable_jump(RLUA_PUSHSTRING_JB);
		ret = rlua_pushstring_func(a1, a2);
		variable_replace(RLUA_PUSHSTRING_JB);
		break;
	default:
		ret = rlua_pushstring_func(a1, a2);
		break;
	}
	return ret;
}

int rlua_pcall(int a1, int a2, int a3, int a4)
{
	int ret;
	auto rlua_pcall_func_eternal = reinterpret_cast<lua::rlua_pcall_def>(eternal_unprotect(RLUA_PCALL_ADDR));
	auto rlua_pcall_func_brandon = reinterpret_cast<lua::rlua_pcall_def>(brandon_retcheck::retcheckunprotect(RLUA_PCALL_ADDR));
	switch (retcheck_bypass_interval)
	{
	case ETERNALBYPASS_DEF:
		ret = rlua_pcall_func_eternal(a1, a2, a3, a4);
		break;
	case BRANDONBYPASS_DEF:
		ret = rlua_pcall_func_brandon(a1, a2, a3, a4);
		break;
	case JBRRBYPASS_DEF:
		variable_jump(RLUA_PCALL_JB);
		ret = rlua_pcall_func(a1, a2, a3, a4);
		variable_replace(RLUA_PCALL_JB);
		break;
	default:
		ret = rlua_pcall_func(a1, a2, a3, a4);
		break;
	}
	return ret;
}
