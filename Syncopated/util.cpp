/*
 *	util.cpp
 *	Isabelle
 *
 *	Created by Azurilex on 04/27/2019
 *	Last edited by Azurilex on 04/27/2019
 *	Copyright © 2019 Azurilex. All rights reserved.
 *	Copyright © 2019 Ice Bear. All rights reserved.
 *	A few misc. utility functions that are used all around the solution.
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

void WriteReturn(DWORD addr)
{
	DWORD oldP;
	VirtualProtect(reinterpret_cast<PVOID>(addr), 1, 0x40, &oldP);
	memset(reinterpret_cast<PVOID>(addr), ret, 1);
	VirtualProtect(reinterpret_cast<PVOID>(addr), 1, oldP, &oldP);
}

void StartConsole(const char* Title)
{
	WriteReturn(reinterpret_cast<DWORD>(FreeConsole));
	AllocConsole();
	SetConsoleTitle(Title);

	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);

	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 900, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void SubTitle(const char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("%s", Message);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
