##
## EPITECH PROJECT, 2023
## Arcade Name of the Ncurses
## File description:
## compiles and builds lib and the source files runs unit tests
##

NAME	=	arcade_snake.so

CXXFLAGS	=	-std=c++20 -Wall -Wextra -Werror -lncurses -ltinfo -g -fPIC -shared -I../../Headers

CXXFLAGS += -L../../Utils

CC	=	g++

SRC	=	src/Snake.cpp

RM = rm -f

OBJ	= $(SRC:.cpp=.o)

all: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME)
	mkdir -p ../../lib
	mv $(NAME) ../../lib

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
