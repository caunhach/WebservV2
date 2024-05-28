#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <string>
# include <cstring>
# include <cerrno>
# include <iostream>
# include <fstream>
# include <vector>
# include <map>
# include <unordered_map>
# include <set>

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netinet/in.h>

# include <sys/select.h>
# include <fcntl.h>
# include <unistd.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

# define RECV_SIZE 65536

# ifndef OUT
#  define OUT 1
# endif

#define default_config "../srcs/Config/config_files/default.conf"

#endif