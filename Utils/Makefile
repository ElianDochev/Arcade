##
## EPITECH PROJECT, 2023
## Makefile for lib
## File description:
## Compiles and builds mylib (called from root Makefile)
##

SCR	=	src/FileReader.cpp \
		src/ReadDlib.cpp \

OBJ	=	$(SCR:.cpp=.o)

CPPFLAGS = -I../Headers

DEBUG = -g3 -Wall -Wextra

LIB_CREATE = ar rc -o

RM = rm -f

NAME	=	libmy.a

all: $(OBJ)
	$(LIB_CREATE) $(NAME) $(OBJ)

debug:
	$(MAKE) CPPFLAGS="$(CPPFLAGS) $(DEBUG)" all

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all makelib clean fclean re
