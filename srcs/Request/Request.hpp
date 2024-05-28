#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "../../includes/webserv.hpp"

enum HttpMethod {
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE
};

class Request {
	private:
		HttpMethod	_method;
		std::string	_url;
		std::string _protocol_version;
		std::map<std::string, std::string> _headers;
};

#endif