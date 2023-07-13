##
## EPITECH PROJECT, 2023
## Arcade Name of the SDL2 lib
## File description:
## compiles and builds lib and the source files runs unit tests
##

NAME	=	arcade_sdl2.so

CXXFLAGS	=	-std=c++20 -Wall -Wextra -Werror -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lSDL2_image -g -fPIC -shared -I../../Header

CXXFLAGS += -L../../Utils

CC	=	g++

SRC	=	src/SDLDisp.cpp	\
		src/SDLDraw.cpp	\
		src/SDLKeyboard.cpp	\
		src/SDLMouse.cpp	\
		src/SDLEvents.cpp	\

RM = rm -f

OBJ	= $(SRC:.cpp=.o)

all: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME)
	mkdir -p ../../lib
	mv $(NAME) ../../lib

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re