##
## EPITECH PROJECT, 2023
## Arcade GAMES MAKEFILE
## File description:
## compiles and builds lib and the source files runs unit tests
##

TARGETS = MainMenu \
		  Snake		\
		  Nibbler	\

# all: $(TARGETS)

# $(TARGETS):
# 	@$(MAKE) -C $@

all:
	@$(foreach dir, $(TARGETS), $(MAKE) all -C $(dir) ;)

debug:
	@$(foreach dir, $(TARGETS), $(MAKE) debug -C $(dir) ;)

clean:
	@$(foreach dir, $(TARGETS), $(MAKE) -C $(dir) clean;)

fclean:
	@$(foreach dir, $(TARGETS), $(MAKE) -C $(dir) fclean;)

re: fclean all

.PHONY: all clean fclean re
