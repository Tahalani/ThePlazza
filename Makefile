##
## EPITECH PROJECT, 2023
## teckspice
## File description:
## Makefile
##

SRC			=	src/kitchen/Kitchen.cpp \
				src/reception/Communication.cpp \
				src/reception/Reception.cpp \
				src/reception/Shell.cpp \
				src/Configuration.cpp \
				src/Main.cpp

OBJ			=	$(SRC:.cpp=.o)

NAME		=	plazza

CPPFLAGS	=	-iquote include/ -iquote src/ \
				-iquote src/kitchen -iquote src/reception
CXXFLAGS	=	-Wall -Wextra -pthread -std=c++17

all:	$(NAME)

$(NAME): $(OBJ)
	g++ $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f *.gcda *.gcno

debug: CXXFLAGS += -g3
debug: re

fclean:	clean
	rm -f $(NAME)
	rm -f $(OBJ)

re:	fclean all

.PHONY:	all clean fclean re
