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
	static bool c_isnumber(const std::string& s);
	static CL c_error(std::string error);
	static std::vector<std::string> split(std::string s, ...);
};

#endif
