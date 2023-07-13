##
## EPITECH PROJECT, 2023
## Arcade Name of the LIB MAKEFILE
## File description:
## compiles and builds lib and the source files runs unit tests
##

NAME	=	##.so

CXXFLAGS	=	-std=c++20 -Wall -Wextra -Werror -fPIC -I../../Headers

CXXFLAGS += -L../../Utils -lmy

CC	=	g++

SRC	=	##

RM = rm -f

MAKELIB = make -C ../../Utils

OBJ	= $(SRC:.cpp=.o)

all: $(MAKELIB) $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)
	mkdir -p ../lib
	mv $(NAME) ../lib

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
