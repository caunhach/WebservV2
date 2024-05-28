#ifndef SERVERMANAGER_HPP
# define SERVERMANAGER_HPP

#include "../../includes/webserv.hpp"
#include "Server.hpp"
#include "../Config/Config.hpp"

class ServerManager {
	public:
		ServerManager(void);
		~ServerManager(void);
		void SetupServers(Config &config);
		void RunServers(void);
		void HandleSelectError(void);
		void HandleTimeout(void);
		void printfdset(fd_set *set);
		void addfdToset(const int i, fd_set &set);
		void deletefdFromset(const int i, fd_set &set);
		void closeConnection(int i);
		void acceptClientConnection(int i);
		void recvRequest(int i);
	private:
		int _max_fd;
		fd_set	_fd_recv;
		fd_set _fd_write;
		std::vector<Server> _servers;
		std::unordered_map<int, Server> _servers_map;
		std::unordered_map<int, Client> _clients_map;
};

#endif