##
## EPITECH PROJECT, 2023
## Arcade Name of the LIB MAKEFILE
## File description:
## compiles and builds lib and the source files runs unit tests
##

NAME = MainMenu.so

CC	=	g++

CXXFLAGS	=	-std=c++20 -Wall -Wextra -Werror -shared -g -fPIC -I../../Headers

CXXFLAGS += -L../../Utils

SRC	=	src/MainMenu.cpp	\
		../../Utils/src/FileReader.cpp

RM = rm -f

OBJ	= $(SRC:.cpp=.o)

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)
	mkdir -p ../../lib
	mv $(NAME) ../../lib

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
