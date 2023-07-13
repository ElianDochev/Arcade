##
## EPITECH PROJECT, 2023
## Arcade Graphicals MAKEFILE
## File description:
## compiles and builds lib and the source files runs unit tests
##

TARGETS = Ncurses \
			Vulkan \
			SFML

# $(TARGETS):
# 	@$(foreach dir, $(TARGETS), $(MAKE) all -C $(dir) ;)

all:
	@$(foreach dir, $(TARGETS), $(MAKE) all -C $(dir) ;)

debug:
	@$(foreach dir, $(TARGETS), $(MAKE) debug -C $(dir) ;)

clean:
	@$(foreach dir, $(TARGETS), $(MAKE) clean -C $(dir) ;)

fclean:
	@$(foreach dir, $(TARGETS), $(MAKE) fclean -C $(dir);)

re: fclean all

.PHONY: all clean fclean re
