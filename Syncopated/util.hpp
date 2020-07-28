/*
 *	util.hpp
 *	Isabelle
 *
 *	Created by Azurilex on 04/27/2019
 *	Last edited by Azurilex on 04/27/2019
 *	Copyright © 2019 Azurilex. All rights reserved.
 *	Precompiles functions used in util.cpp
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#pragma once
#pragma comment(lib, "wininet.lib")
#include "globals.hpp"
#include <vector>
#include <sstream>
#include <algorithm>

namespace GlobalFunctions
{
    bool to_bool(std::string str);
    std::string replaceAll(std::string subject, const std::string& search, const std::string& replace);
    std::vector<std::string> splitString(std::string str, char delimiter);
    size_t write_data(void* buffer, size_t size, size_t nmemb, void* param);
}

DWORD rbx_GetParent(DWORD Instance);
void WriteReturn(DWORD addr);
void StartConsole(const char* Title);
void SubTitle(const char* Message);
#endif