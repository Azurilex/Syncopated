/*
 *	c_execution.hpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	rLua C API Parser to allow the user to execute functions for the API, object oriented
 */

#pragma once

#ifndef C_EXECUTION_HPP
#define C_EXECUTION_HPP

#include <sstream>
#include "rbxlua.hpp"

struct CL
{
	int errors = 0;
	std::string error;
};

class lc_parser
{
public:
	lc_parser();
	~lc_parser();
	CL do_string(std::vector<std::string> arg, rlua instance);
private:
	static bool c_stringtobool(std::string& s);
	static bool c_isboolean(const std::string& s);
	static bool c_isnumber(const std::string& s);
	static CL c_error(std::string error);
	static std::vector<std::string> split(std::string s, ...);
};

#endif
