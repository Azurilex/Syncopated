/*
 *	util.hpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	Miscellaneous functions used throughout the source
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#pragma once

#define CURL_STATICLIB

#include <curl.h>

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "user32.lib")
#pragma comment (lib, "Gdi32.lib")

#include <vector>
#include <sstream>
#include "globals.hpp"

std::vector<std::string> split(std::string s, ...);
void write_return(DWORD addr);
void start_console(const char* Title);
void subtitle(const char* Message);
std::size_t curl_callback(
	const char* in,
	std::size_t size,
	std::size_t num,
	std::string* out);
#endif