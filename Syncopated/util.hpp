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
#include <vector>
#include <sstream>
#include "globals.hpp"

std::vector<std::string> split(std::string s, ...);
void write_return(DWORD addr);
void start_console(const char* Title);
void subtitle(const char* Message);
#endif