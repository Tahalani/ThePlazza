##
## EPITECH PROJECT, 2023
## teckspice
## File description:
## Makefile
##

NAME	=	plazza

SRC 	=	src/client/parsing/parsing.cpp \
		src/client/client.cpp \
		src/server/server.cpp \
		src/server/kitchen.cpp	\
		src/restaurant.cpp \
		src/main.cpp \

CXXFLAGS	= -Wall -Wextra -I./include/

OBJ	=	$(SRC:.cpp=.o)

all:	$(NAME)
$(NAME): $(OBJ)
	g++ $(CXXFLAGS)	-o $(NAME)	$(OBJ)

clean:
	rm -f *.gcda *.gcno

fclean:	clean
	rm -f $(NAME)
	rm -f $(OBJ)

re:	fclean all

.PHONY:	all clean fclean re
