#ifndef SERVER_HPP
# define SERVER_HPP

#include "../../includes/webserv.hpp"
#include "../Config/Config.hpp"
#include "Client.hpp"

class Client;

class Server {
	public:
		Server(void);
		Server(const t_listen &listen);
		~Server(void);
		void			setupServer();
		void			sendResponse(long socket);
		void			closeSocket(long socket);
		void			handleerror(void);
		long 			getfd(void);
	private:
		std::map<long, std::string>	_requests;
		long			_sock_fd;
		struct sockaddr_in _sock_addr;
	class ServerErrorException : public std::exception {
		private:
			std::map<long, std::string>	_requests;
			std::string errorMessage;
		public:
			ServerErrorException(const std::string& message) : errorMessage(message) { }
			virtual const char *what() const throw() override {
				return errorMessage.c_str();
			}
	};
};

#endif