#include "ServerManager.hpp"

ServerManager::ServerManager(void) {
}

ServerManager::~ServerManager(void) {}

void ServerManager::SetupServers(Config &config)
{
	std::vector<t_listen> listens = config.getAllListens();
	bool isDuplicate = false;
	FD_ZERO(&_fd_recv);

	_max_fd = 0;
	for (std::vector<t_listen>::iterator it = listens.begin(); it != listens.end(); it++)
	{
		isDuplicate = false;
		for (std::vector<t_listen>::iterator it2 = listens.begin(); it2 != it; it2++)
		{
			if ((*it).host == (*it2).host && (*it).port == (*it2).port) {
				isDuplicate = true;
				break;
			}
		}
		if (!isDuplicate)
		{
			Server server(*it);
			long fd;

			server.setupServer();
			fd = server.getfd();			
			std::cout << "ServerManager: setting up server on fd " << fd << std::endl;
			FD_SET(fd, &_fd_recv);
			//if parsing config this line may not use
			_servers.push_back(server);
			_servers_map.insert(std::make_pair(fd, server));

			if (fd > _max_fd)
				_max_fd = fd;
		}
	}

	// above is just mock
	std::cout << "ServerManager: setting up servers" << std::endl;
}

void ServerManager::RunServers(void)
{
	std::cout << "ServerManager: running servers" << std::endl;

	struct timeval timeout;
	int	rc;
	int desc_ready;
	fd_set _fd_recv_cpy;
	fd_set _fd_write_cpy;
	
	// printfdset(&_fd_recv);
	timeout.tv_sec = 60;
	timeout.tv_usec = 0;
	FD_ZERO(&_fd_write);
	while (true)
	{
		// _fd_recv_cpy = _fd_recv;
		// _fd_write_cpy = _fd_write;

		rc = select(_max_fd + 1, &_fd_recv, &_fd_write, NULL, &timeout);

		if (rc < 0)
		{
			perror(" select() failed");
			break;
		}
		else if ( rc == 0)
		{
			std::cout << " select() timed out. End program.\n";
			break;
		}
		desc_ready = rc;
		// std::cout << desc_ready << std::endl;
		// std::cout << _max_fd << std::endl;
		for (int i = 0; i <= _max_fd; ++i)
		{
			std::cout << "i: " << i << std::endl;
			// std::cout << "seg: " << i << std::endl;
			// std::cout << desc_ready << std::endl;
			if (FD_ISSET(i, &_fd_recv) && _servers_map.count(i)) {
				// std::cout << i << std::endl;
				// std::cout << desc_ready << std::endl;
				acceptClientConnection(i);
				desc_ready--;
				// std::cout << desc_ready << std::endl;
			}
			else if (FD_ISSET(i, &_fd_recv) && _clients_map.count(i)) {
				std::cout << "recv request" << std::endl;
				recvRequest(i);
				desc_ready--;
			}
		}
		std::cout << "end" << std::endl;
	}
	// printfdset(&_fd_write_cpy);
}

void ServerManager::HandleSelectError(void) {
	std::cerr << "ServerManager: select error" << std::endl;
	exit(1);
}

void ServerManager::HandleTimeout(void) {
	std::cout << "ServerManager: select timeout" << std::endl;
	exit(0);
}

void ServerManager::printfdset(fd_set *set) {
	std::cout << "fd_set: " << set << std::endl;
	for (int fd = 0; fd < FD_SETSIZE; fd++)
		if (FD_ISSET(fd, set))
			std::cout << "fd: " << fd << std::endl;
}

void ServerManager::addfdToset(const int i, fd_set &set)
{
	std::cout << "add: " << i << std::endl;
	FD_SET(i, &set);
	if (i > _max_fd)
		_max_fd = i;
	std::cout << "_max_fd: " << _max_fd << std::endl;
}

void ServerManager::deletefdFromset(const int i, fd_set &set)
{
	FD_CLR(i, &set);
	if (i == _max_fd)
		_max_fd--;
}

void ServerManager::closeConnection(int i)
{
	if (FD_ISSET(i, &_fd_write))
		deletefdFromset(i, _fd_write);
	if (FD_ISSET(i, &_fd_recv))
		deletefdFromset(i, _fd_recv);
	close(i);
	_clients_map.erase(i);
}

void ServerManager::acceptClientConnection(int i) {
	struct sockaddr_in client_address;
	long client_address_size = sizeof(client_address);
	long client_sock;
	Client client(_servers_map[i]);

	// std::cout << i << std::endl;
	if ((client_sock = accept(i, (struct sockaddr *)&client_address, (socklen_t*)&client_address_size)) == -1)
	{
		std::cout << "ServerManager: accept error" << std::endl;
		return;
	}
	// std::cout << client_sock << std::endl;
	addfdToset(client_sock, _fd_recv);
	// std::cout << "end" << std::endl;
	if (fcntl(client_sock,  F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "ServerManager: fcntl error" << std::endl;
		deletefdFromset(client_sock, _fd_recv);
		close(client_sock);
		return;
	}
	client.setSocket(static_cast<int>(client_sock));
	if (_clients_map.count(client_sock) != 0)
		_clients_map.erase(client_sock);
	_clients_map.insert(std::make_pair(client_sock, client));
	if (_clients_map.count(client_sock))
		std::cout << "client sock: " << client_sock << std::endl;
	// std::cout << "end" << std::endl;
}

void ServerManager::recvRequest(int i) {
	char	buffer[RECV_SIZE] = {0};
	int		bytes;

	bytes = read(i, buffer, RECV_SIZE - 1);

	std::cout << "read: " << i << std::endl;
	// if (bytes < 0)
	// {
	// 	std::cout << "SercerManager: read error" << std::endl;
	// 	closeConnection(i);
	// 	return;
	// }
	// else if (bytes == 0)
	// {
	// 	std::cout << "ServerManager: connection was closed by client" << std::endl;
	// 	closeConnection(i);
	// 	return;
	// }
	// else if (bytes != 0)
	// {
	// 	std::cout << "come here";
	// }
}