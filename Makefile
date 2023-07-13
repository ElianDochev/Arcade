##
## EPITECH PROJECT, 2023
## Arcade MAKEFILE
## File description:
## by Eliyan Dochev, mikhail Sazonov and vasiliy novikov
##

MAKE_GAME	= -C Games
MAKE_CORE	= -C Core
MAKE_GRAPH	= -C Graphicals

RM		=	clean
FRM		=	fclean

DEBUG	= 	debug

###
###	release
###

all : core games graphicals

core:
		@$(MAKE) $(MAKE_CORE)
		@mv ./Core/arcade ./

games:
		@$(MAKE) $(MAKE_GAME)

graphicals:
		@$(MAKE) $(MAKE_GRAPH)

###
###	debug
###

debug: core_debug games_debug graphicals_debug

core_debug:
		@$(MAKE) $(DEBUG) $(MAKE_CORE)
		@mv ./Core/arcade ./

games_debug:
		@$(MAKE) $(DEBUG) $(MAKE_GAME)

graphicals_debug:
		@$(MAKE) $(DEBUG) $(MAKE_GRAPH)

###
###	clean/fclean
###

clean:
		@$(MAKE) $(RM) $(MAKE_CORE)
		@$(MAKE) $(RM) $(MAKE_GAME)
		@$(MAKE) $(RM) $(MAKE_GRAPH)

fclean:
		@$(MAKE) $(FRM) $(MAKE_CORE)
		@$(MAKE) $(FRM) $(MAKE_GAME)
		@$(MAKE) $(FRM) $(MAKE_GRAPH)
		@rm -f arcade
		@rm -f ./lib/*

re: fclean all

.PHONY: all core games graphicals clean fclean re
