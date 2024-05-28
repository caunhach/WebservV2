#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../../includes/webserv.hpp"
#include "ConfigDS.hpp"

class Config
{
	public:
		Config();
		~Config();
		int parse(const char *filename);
		std::vector<t_listen>				getAllListens() const;
};

#endif