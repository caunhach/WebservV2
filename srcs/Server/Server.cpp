#include "Server.hpp"

Server::Server(void) {}

Server::Server(const t_listen &listen) {
	_sock_addr.sin_family = AF_INET;
	_sock_addr.sin_port = htons(listen.port);
	_sock_addr.sin_addr.s_addr = htonl(listen.host);
	std::cout << "Server: listening on port " << listen.port << std::endl;
	std::cout << "Server: listening on host " << listen.host << std::endl;
}

Server::~Server(void) {}

void	Server::setupServer() {
	std::cout << "Server: setting up servers" << std::endl;
	int on=1;
	_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "_sock_fd: " << _sock_fd << std::endl;
	if (_sock_fd == -1)
		throw ServerErrorException("Failed to create socket.");

	memset(&_sock_addr, 0, sizeof(_sock_addr));

	if (setsockopt(_sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
		throw ServerErrorException("Failed to set reuse addr");

	if (fcntl(_sock_fd, F_SETFL, O_NONBLOCK) < 0)
		throw ServerErrorException("Failed to non blocking");

	if (bind(_sock_fd, (struct sockaddr *) &_sock_addr, sizeof(_sock_addr)) < 0)
		throw ServerErrorException("Failed to bind socket to port 9999.");

	if (listen(_sock_fd, 10) == -1 < 0)
		throw ServerErrorException("Failed to listen on socket.");
}

void	Server::sendResponse(long socket) {
	static std::map<long, size_t> SentSocketInfo;

	//check that socket is sent
	if (SentSocketInfo.find(socket) == SentSocketInfo.end())
		SentSocketInfo[socket] = 0;
	//logic if sent[socket] == 0
	if (SentSocketInfo[socket] == 0)
		std::cout << "logic here" << std::endl;
	
	std::string ResponseData = _requests[socket].substr(SentSocketInfo[socket], RECV_SIZE);
	//ssize_t send(int sockfd, const void *buf, size_t len, int flags);
	int BytesSent = send(socket, ResponseData.c_str(), ResponseData.size(), 0);

	if (BytesSent < 0) {
		this->closeSocket(socket);
		SentSocketInfo[socket] = 0;
		this->handleerror();
		//implement some Exception here
	}

	SentSocketInfo[socket] += BytesSent;
	if (SentSocketInfo[socket] < _requests[socket].size()) {
		//handle some error here
		return ;
	}

	_requests.erase(socket);
	SentSocketInfo[socket] = 0;
}

void	Server::closeSocket(long socket) {
	if (socket > 0)
		::close(socket);
	_requests.erase(socket);
}

void	Server::handleerror() {}

long	Server::getfd() {
	return _sock_fd;
}