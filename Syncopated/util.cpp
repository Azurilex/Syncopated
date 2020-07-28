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

#define _CRT_SECURE_NO_WARNINGS
#include "util.hpp"

namespace GlobalFunctions
{
	bool to_bool(std::string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		std::istringstream is(str);
		bool b;
		is >> std::boolalpha >> b;
		return b;
	}

	std::string replaceAll(std::string subject, const std::string& search, const std::string& replace)
	{
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos)
		{
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	std::vector<std::string> splitString(std::string str, char delimiter)
	{
		std::vector<std::string> tokens;
		std::stringstream ss(str);
		std::string tok;

		while (getline(ss, tok, delimiter))
			tokens.push_back(tok);
		return tokens;
	}

	size_t write_data(void* buffer, size_t size, size_t nmemb, void* param)
	{
		std::string& text = *static_cast<std::string*>(param);
		size_t totalsize = size * nmemb;
		text.append(static_cast<char*>(buffer), totalsize);
		return totalsize;
	}
}

DWORD rbx_GetParent(DWORD Instance)
{
	__asm {
		mov ecx, Instance
		mov eax, [ecx + PARENT_OFF]
	}
}

void WriteReturn(DWORD addr)
{
	DWORD oldP;
	VirtualProtect(reinterpret_cast<PVOID>(addr), 1, 0x40, &oldP);
	memset(reinterpret_cast<PVOID>(addr), 0xC3, 1);
	VirtualProtect(reinterpret_cast<PVOID>(addr), 1, oldP, &oldP);
}

void StartConsole(const char* Title)
{
	WriteReturn(reinterpret_cast<DWORD>(FreeConsole));
	AllocConsole();
	SetConsoleTitle(Title);
	freopen("conout$", "w", stdout);
	freopen("conin$", "r", stdin);
	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 900, 0, 0,
		SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void SubTitle(const char* Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("%s", Message);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}