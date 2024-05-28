#include "Client.hpp"

Client::Client(void)
{
	_last_msg_time = time(NULL);
}

Client::Client(const Server &server)
{

	_last_msg_time = time(NULL);
	// std::cout << server;
}

Client::~Client(void) { }

const long	&Client::getSocket() const
{
	return (_Client_socket);
}

const struct sockaddr_in	&Client::getAddress() const
{
	return (_Client_address);
}

const time_t	&Client::getLastTime() const
{
	return (_last_msg_time);
}

void	Client::setSocket(const int &sock)
{
	_Client_socket = sock;
}

void	Client::setAddress(sockaddr_in &addr)
{
	_Client_address = addr;
}

