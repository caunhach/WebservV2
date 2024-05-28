#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "../../includes/webserv.hpp"
#include "Server.hpp"

class Server;

class Client {
	public:
		Client(void);
		Client(const Server &server);
		~Client(void);

		const long					&getSocket() const;
		const struct sockaddr_in	&getAddress() const;
		const Server				&getServer() const;
		const time_t				&getLastTime() const;
		void						setSocket(const int &sock);
		void						setAddress(sockaddr_in &addr);

	private:
		long				_Client_socket;
		struct sockaddr_in	_Client_address;
		time_t				_last_msg_time;
};

#endif