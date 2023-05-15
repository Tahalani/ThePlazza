##
## EPITECH PROJECT, 2023
## teckspice
## File description:
## Makefile
##

NAME	=	plazza

SRC 	=	parsing/parsing.cpp \
			client/client.cpp \
			main.cpp	\

CXXFLAGS	= -g -Wall -Wextra -I./include/

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
