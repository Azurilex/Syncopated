/*
 *	c_execution.cpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	rLua C API Parser to allow the user to execute functions for the API, object oriented
 */

#include "c_execution.hpp"

#include <algorithm>

std::vector<std::string> LC_Parser::split(std::string s, ...)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}

LC_Parser::LC_Parser() = default;
LC_Parser::~LC_Parser() = default;

CL LC_Parser::do_string(std::vector<std::string> arg, rlua entity)
{	
	if (arg.at(0) == "lua_getglobal")
	{
		if (!(arg.size() == 2))
		{
			return c_error("invalid number of arguments for \"lua_getglobal\"");
		}

		std::string global = arg.at(1);

		entity.lua_getfield(-10002, global.c_str());
	}

	else if (arg.at(0) == "lua_pushstring")
	{
		if (!(arg.size() >= 2))
		{
			return c_error("invalid number of arguments for \"lua_pushstring\"");
		}

		std::string s;

		for (size_t a = 1; a < arg.size(); a++)
		{
			if (a < arg.size() - 1)
			{
				s.append(arg.at(a) + ' ');
			}
			if (a == arg.size() - 1)
			{
				s.append(arg.at(a));
			}
		}

		const char* c = s.c_str();
		if (std::strcmp(c, "nil") == 0)
		{
			c = NULL;
		}

		entity.lua_pushstring(c);
	}

	else if (arg.at(0) == "lua_pcall")
	{
		if (!(arg.size() == 4))
		{
			return c_error("invalid number of arguments for \"lua_pcall\"");
		}

		for (int i = 1; i < 4; i++)
		{
			if (!c_isnumber(arg.at(static_cast<unsigned>(i))))
			{
				return c_error("lua_pcall argument at " + std::to_string(i) + "must be an int");
			}
		}

		//std::cout << stoi(arg.at(1)) << stoi(arg.at(2)) << stoi(arg.at(3)) << std::endl;
		entity.lua_pcall(stoi(arg.at(1)), stoi(arg.at(2)), stoi(arg.at(3)));
	}
	
	else if (arg.at(0) == "lua_pushboolean")
	{
		if(!(arg.size() == 2))
		{
			return c_error("invalid number of arguments for \"lua_pushboolean\"");
		}

		if (!c_isboolean(arg.at(1)))
		{
			return c_error("lua_pushboolean argument at 1 must be a boolean");
		}

		entity.lua_pushboolean(c_stringtobool(arg.at(1)));
		
	}

	else if (arg.at(0) == "setretcheckbypass")
	{
		if (!(arg.size() >= 2))
		{
			return c_error("invalid number of arguments for \"setretcheckbypass\"");
		}

		if (!c_isnumber(arg.at(1)))
		{
			return c_error("setretcheckbypass argument at 1 must be an int");
		}

		int i = std::stoi(arg.at(1));

		if (i <= 4 && i >= 1) {

			entity.set_bypass(i);
		}
		else
		{
			return c_error("setretcheckbypass argument at 1 must be >=0 and <=3");
		}
	}
	
	else
	{
		return c_error(arg.at(0) + " is undefined, check documentation");
	}

	return CL{0, ""};
}

bool LC_Parser::c_stringtobool(std::string& s)
{
	std::transform(s.begin(), s.end(), s.begin(), std::tolower);
	std::istringstream is(s);
	bool b;
	is >> std::boolalpha >> b;
	return b;
}

bool LC_Parser::c_isboolean(const std::string& s)
{
	if (s != "true" && s != "false" && s != "1" && s != "0")
	{
		return false;
	}
	return true;
}

bool LC_Parser::c_isnumber(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

CL LC_Parser::c_error(std::string error)
{
	return CL{1, error};
}
