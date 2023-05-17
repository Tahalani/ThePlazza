##
## EPITECH PROJECT, 2023
## teckspice
## File description:
## Makefile
##

SRC			=	src/client/parsing/parsing.cpp \
				src/client/client.cpp \
				src/server/server.cpp \
				src/server/kitchen.cpp \
				src/Configuration.cpp \
				src/Main.cpp \
				src/Restaurant.cpp

OBJ			=	$(SRC:.cpp=.o)

NAME		=	plazza

CXXFLAGS	=	-Wall -Wextra -I./include/

all:	$(NAME)

$(NAME): $(OBJ)
	g++ $(CXXFLAGS)	-o $(NAME) $(OBJ)

clean:
	rm -f *.gcda *.gcno

debug: CXXFLAGS += -g3
debug: re

fclean:	clean
	rm -f $(NAME)
	rm -f $(OBJ)

re:	fclean all

.PHONY:	all clean fclean re
