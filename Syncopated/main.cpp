/*
 *	main.cpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	Initializes exploit after being attached to a process
 */

#include "util.hpp"
#include "memory.hpp"
#include <WinTrust.h>
#include <algorithm>
#pragma comment(lib, "Wintrust.lib")
#include "c_execution.hpp"
#include "Libraries/MinHook/MinHook.hpp"
#pragma comment(lib, "Libraries/MinHook/libMinHook.x86.lib")

namespace lsh
{
	static int rbx_L_orgiginal = 0;
	static int* gettop_hook = reinterpret_cast<int*>(RLUA_GETTOP_ADDR);

	int gettop_detour(int rState)
	{
		rbx_L_orgiginal = rState;
		return (*reinterpret_cast<DWORD*>(rState + 24) - *reinterpret_cast<DWORD*>(rState + 20)) >> 4;
	}

	void hook()
	{
		MH_Initialize();
		void* oldhook = reinterpret_cast<void*>(MH_CreateHook(gettop_hook, &gettop_detour, nullptr));
		MH_CreateHook(gettop_hook, &gettop_detour, static_cast<void**>(oldhook));
		MH_EnableHook(gettop_hook);
		MH_DisableHook(gettop_hook);

		if (rbx_L_orgiginal == 0)
		{
			oldhook = reinterpret_cast<void*>(MH_CreateHook(gettop_hook, &gettop_detour, nullptr));
			MH_CreateHook(gettop_hook, &gettop_detour, static_cast<void**>(oldhook));
			MH_EnableHook(gettop_hook);
			while (rbx_L_orgiginal == 0) { Sleep(1); }
			MH_DisableHook(gettop_hook);
		}
	}
}

int __stdcall main_entry()
{
	StartConsole("Syncopated");
	SubTitle("Syncopated - Debug Console\n");

	std::cout << termcolor::white << std::endl << "hey mom, looK! the boys are back in town!!" << std::endl << std::endl;

	writeshell(reinterpret_cast<PBYTE>(WinVerifyTrust), {0x31, 0xC0, 0xC3});

	std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: " << "RLUASTATE EXPLOIT SELECTION" << termcolor::white << std::endl;
	std::cout << "[" << termcolor::yellow << "1" << termcolor::white << "]: RUN GLOBALSTATE ENCRYPTION (LEGACY) (BROKEN)" << std::endl;
	std::cout << "[" << termcolor::yellow << "2" << termcolor::white << "]: LUA_GETTOP LUA STATE HOOK (MODERN)" << std::endl;
	std::cout << "[" << termcolor::yellow << "3" << termcolor::white << "]: NONE (BRAINDEAD)" << std::endl;
	int s;
	int temporary_state;
	std::cout << R"(Please select "1" / "2" / "3": )";
	std::cin >> s;

	switch (s)
	{
	case 1:
		//LEGACY SCANNING METHOD
		/*std::cout << std::endl << "[" << termcolor::magenta << "#" << termcolor::white << "]: SEARCHING FOR DATAMODEL..." << std::endl;
		DataModel = Memory::getdm();
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: FOUND DATAMODEL (" << DataModel << "). SEARCHING FOR SCRIPTCONTEXT..." << std::endl;
		ScriptContext = reinterpret_cast<PDWORD>(Memory::findfirstclass(DataModel, "ScriptContext"));
		//ScriptContext = reinterpret_cast<PDWORD>(Memory::findPattern(PAGE_READWRITE, reinterpret_cast<char*>(&script_context_bytes), const_cast<char*>("xxxx")));
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: FOUND SCRIPTCONTEXT (" << ScriptContext << "). RUNNING GLOBALSTATE ENCRYPTION..." << std::endl;
		temporary_state = static_cast<int>(ScriptContext[41] - reinterpret_cast<DWORD>(&ScriptContext[41]));
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: FOUND A TEMPORARY LUASTATE (" << temporary_state << ")." << std::endl;*/
		//break;
	case 2:
		//HOOKING METHOD
		std::cout << std::endl << "[" << termcolor::magenta << "#" << termcolor::white << "]: STARTING HOOK ON LUA_GETTOP..." << std::endl;
		lsh::hook();
		temporary_state = lsh::rbx_L_orgiginal;
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: DETACHED HOOK, FOUND A TEMPORARY LUASTATE (" << temporary_state << ")." << std::endl;

		break;
	case 3:
		temporary_state = NULL;
		std::cout << std::endl << "[" << termcolor::magenta << "#" << termcolor::white << "]: TEMPORARY LUASTATE HAS BEEN SET TO \"NULL\" PER THE USER'S REQUEST. YOU ARE GOING TO CRASH AFTER CHOOSING A RETCHECK BYPASS DUE TO NO LUASTATE TO RUN ON" << std::endl;
		break;
	default:
		//HOOKING METHOD
		std::cout << std::endl << "ur fuckin braindead and can't type 1 or 2 properly, but we'll just run the hooking method instead of crashing" << std::endl;
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: STARTING HOOK ON LUA_GETTOP..." << std::endl;
		lsh::hook();
		temporary_state = lsh::rbx_L_orgiginal;
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: DETACHED HOOK, FOUND A TEMPORARY LUASTATE (" << temporary_state << ")." << std::endl;
		break;
	}

RERUN:
	s = 0;
	std::cout << std::endl;
	std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]:" << " RETURN CHECK BYPASS SELECTION" << termcolor::white << std::endl;
	std::cout << "[" << termcolor::yellow << "1" << termcolor::white << "]: ETERNAL'S BYPASS" << std::endl;
	std::cout << "[" << termcolor::yellow << "2" << termcolor::white << "]: BRANDON'S BYPASS" << std::endl;
	std::cout << "[" << termcolor::yellow << "3" << termcolor::white << "]: JBRR BYPASS" << std::endl;
	std::cout << "[" << termcolor::yellow << "4" << termcolor::white << "]: NONE" << std::endl;
	std::cout << "[" << termcolor::yellow << "0" << termcolor::white << "]: MORE INFORMATION REGARDING EACH BYPASS" << std::endl;
	std::cout << R"(Please select "1" / "2" / "3" / "4": )";
	std::cin >> s;

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//by the way, i use switch cases whenever possible instead of if, else if, else - because i'm not a homosexual!!
	switch (s)
	{
	case 1:
		retcheck_bypass_interval = ETERNALBYPASS_DEF;
		break;
	case 2:
		retcheck_bypass_interval = BRANDONBYPASS_DEF;
		break;
	case 3:
		retcheck_bypass_interval = JBRRBYPASS_DEF;
		break;
	case 4:
		retcheck_bypass_interval = NULL;
		break;
	case 0:
		std::cout << std::endl;
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: ETERNAL'S BYPASS -> Based off of Brandon's bypass, this bypass was released in 2017 by Eternal. It works by copying the function to a seperate, un-hashed, portion of memory then proceeds to alter the flow of the check, preventing a shutdown. (https://github.com/EternalV3/Retcheck)" << std::endl;
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: BRANDON'S BYPASS -> Written by Brandon/Chirality. Works extremely similarily to Eternal's bypass, hell, Eternal's bypass was completely based off of this one. This bypass has been found to be the most efficient of the two though, however, it isn't as light-weight as Eternal's." << std::endl;
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: JBRR BYPASS -> This method was widly used in 2016 to bypass retcheck. When an rLua C function is run, before the actual execution of the function, we switch the check's conditional jump, to a jump that goes over the flag. Then the function runs, and switch it back immediately after to avoid being flagged by ROBLOX's memory check. In the end, this method bypasses ROBLOX's memory check with simplicity, and ease - however, it is not as efficient as other methods." << std::endl;
		std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: NONE -> No retcheck bypass will be used, this causes a shutdown following the execution of an rLua C API function. However, this will not effect the RESULT, the game will still shutdown, but the code will continue to run and execute properly." << std::endl;
		goto RERUN; //yes i used a fucking label, i'm sorry.
	default:
		retcheck_bypass_interval = ETERNALBYPASS_DEF;
		break;
	}

	std::cout << std::endl << "[" << termcolor::magenta << "#" << termcolor::white << "]: CREATING NEW THREAD OFF OF TEMPORARY STATE" << std::endl;

	rlua* temp = new rlua(temporary_state);
	rlua main(temp->lua_newthread());
	delete temp;

	std::cout << "[" << termcolor::magenta << "#" << termcolor::white << "]: MAIN THREAD CREATED (" << ")" << std::endl << std::endl;
	main.lua_getfield(-10002, "print");
	main.lua_pushstring("lua c test");
	main.lua_pcall(1, 0, 0);

	CL result;
	lc_parser parser;
	
	while (true)
	{
		std::cout << termcolor::magenta << "> " << termcolor::white;
		std::string str;
		getline(std::cin, str);
		std::vector<std::string> arguments = split(str, ' ');
		//std::cout << arguments.at(0) << arguments.at(1) << std::endl;
		result = parser.do_string(arguments, main);

		//rlua_pushstring(rbx_L, "done lol");
		//rlua_pcall(reinterpret_cast<DWORD*>(rbx_L), 1, 0, 0);

		if (result.errors == 1)
		{
			std::cout << "[" << termcolor::red << "ERROR" << termcolor::white << "]: " << result.error.c_str() <<
				std::endl;
		}
	}

	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(main_entry), hModule, NULL, nullptr);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
