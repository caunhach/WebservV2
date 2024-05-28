#include "Config.hpp"

Config::Config() {}

Config::~Config() {}

int     Config::parse(const char *filename) {
	std::cout << "Parsing file: " << filename << std::endl;
	return 0;
}

std::vector<t_listen>				Config::getAllListens() const {
	std::vector<t_listen>	ret;

	// Create and add the first listen
    t_listen listen1;
    listen1.host =0x0100007F; // For example, localhost IP address in hexadecimal
    listen1.port = 8080; // For example, port 8080
    ret.push_back(listen1);

    // Create and add the second listen
    t_listen listen2;
    listen2.host = 0x0100008F; // For example, another IP address in hexadecimal
    listen2.port = 9090; // For example, another port
    ret.push_back(listen2);

	// Add more listens
	t_listen listen3;
	listen3.host = 0x0100007F;
	listen3.port = 8080;
	ret.push_back(listen3);

	return ret;
}