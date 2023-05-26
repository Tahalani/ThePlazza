##
## EPITECH PROJECT, 2023
## teckspice
## File description:
## Makefile
##

SRC			=	src/kitchen/Kitchen.cpp \
				src/kitchen/ThreadPool.cpp \
				src/reception/PizzaOrder.cpp \
				src/reception/Reception.cpp \
				src/reception/ReceptionIPC.cpp \
				src/reception/Shell.cpp \
				src/util/Communication.cpp \
				src/util/Logger.cpp \
				src/util/PlazzaIPC.cpp \
				src/Configuration.cpp \
				src/PizzaRecipe.cpp \
				src/Main.cpp

OBJ			=	$(SRC:.cpp=.o)

NAME		=	plazza

CPPFLAGS	=	-iquote include/ -iquote src/ \
				-iquote src/kitchen -iquote src/reception -iquote src/util
CXXFLAGS	=	-Wall -Wextra -std=c++17
LDLIBS		=	-lpthread

all:	$(NAME)

$(NAME): $(OBJ)
	g++ $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

clean:
	rm -f *.gcda *.gcno

debug: CXXFLAGS += -g3
debug: re

fclean:	clean
	rm -f $(NAME)
	rm -f $(OBJ)

re:	fclean all

.PHONY:	all clean fclean re
