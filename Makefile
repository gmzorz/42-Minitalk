# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: goosterl <goosterl@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/10 12:53:09 by goosterl      #+#    #+#                  #
#    Updated: 2021/11/18 11:47:31 by goosterl      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	minitalk
CLIENT			=	client
SERVER			=	server

CC				=	gcc
CFLAGS			=	-g -Wall -Wextra -Werror -Ofast -fsanitize=address
HEADERS			=	./inc/
SERVER_SRC		=	src/server.c			\
					src/decode.c			\
					src/redirect_server.c	\
					src/error.c				\
					src/utils.c				\
					src/writing.c

CLIENT_SRC		=	src/client.c			\
					src/encode.c			\
					src/redirect_client.c	\
					src/error.c				\
					src/utils.c				\
					src/writing.c

SERVER_OBJ		=	$(SERVER_SRC:.c=.o)
CLIENT_OBJ		=	$(CLIENT_SRC:.c=.o)

COLOR_RESET		=	"\\033[0m"
COLOR_ORANGE	=	"\\033[33m"
COLOR_GREEN		=	"\\033[32m"
COLOR_RED		=	"\\033[31m"

$(NAME):	$(CLIENT) $(SERVER)

$(CLIENT):	$(CLIENT_OBJ)
			@echo "$(COLOR_ORANGE) 	✓ $(COLOR_RESET) Compiled client\n"
			@$(CC) $(CFLAGS) $(CLIENT_OBJ) -o client

$(SERVER):	$(SERVER_OBJ)
			@echo "$(COLOR_ORANGE) 	✓ $(COLOR_RESET) Compiled server\n"
			@$(CC) $(CFLAGS) $(SERVER_OBJ) -o server

%.o:		%.c
			@$(CC) -I $(HEADERS) $(CFLAGS) -c -o $@ $<
			@echo  "$(COLOR_GREEN) + $(COLOR_RESET) Updated $@"

all:		$(NAME)

re:			fclean all

clean:
			@rm -rf $(CLIENT_OBJ) $(SERVER_OBJ)
			@echo "$(COLOR_RED) - $(COLOR_RESET) Removed object files."

fclean:		clean
			@echo "$(COLOR_RED) - $(COLOR_RESET) Removed binaries."
			@rm -rf client server
			@rm -f .bonus

bonus:		fclean all

.PHONY:		all re clean fclean bonus
