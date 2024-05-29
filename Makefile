NAME = webserv
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = srcs/main.cpp \
	   srcs/Config/Config.cpp \
	   srcs/Server/Server.cpp \
	   srcs/Server/ServerManager.cpp \
	   srcs/Server/Client.cpp \
	   srcs/Request/Request.cpp
OBJS = $(SRCS:.cpp=.o)

RM = rm -f

all: $(NAME)

$(OBJS): %.o: %.cpp $(HEADERS)
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
    ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean