/*
 *	util.cpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	Miscellaneous functions used throughout the source
 */

#include "util.hpp"

std::vector<std::string> split(std::string s, ...)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}

void write_return(DWORD addr)
{
	DWORD oldP;
	VirtualProtect(reinterpret_cast<PVOID>(addr), 1, 0x40, &oldP);
	memset(reinterpret_cast<PVOID>(addr), ret, 1);
	VirtualProtect(reinterpret_cast<PVOID>(addr), 1, oldP, &oldP);
}

void start_console(const char* Title)
{
	write_return(reinterpret_cast<DWORD>(FreeConsole));
	AllocConsole();
	SetConsoleTitle(Title);
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);

	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 900, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void subtitle(const char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("%s", Message);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
