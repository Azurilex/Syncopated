#pragma once

#ifndef C_EXECUTION_HPP
#define C_EXECUTION_HPP

#include <sstream>
#include "rbxlua.hpp"

struct CL
{
	int errors;
	std::string error;
};

class lc_parser
{
public:
	static CL do_string(std::vector<std::string> arg, rlua instance);
private:
	static bool c_isnumber(const std::string& s);
	static CL c_error(std::string error);
	static std::vector<std::string> split(std::string s, ...);
};

#endif
