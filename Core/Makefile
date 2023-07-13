##
## EPITECH PROJECT, 2023
## Arcade CORE MAKEFILE
## File description:
## compiles and builds lib and the source files runs unit tests
##

NAME	=	arcade

CC = g++

SRC	= main.cpp CoreMediator.cpp ../Utils/src/ReadDlib.cpp

CXXFLAGS = -std=c++20 -g -Wall -Wextra -Werror -I../Headers -ldl

OBJ = $(SRC:.cpp=.o)

all: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all makelib clean fclean re
