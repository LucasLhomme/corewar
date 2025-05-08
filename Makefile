##
## EPITECH PROJECT, 2025
## B-CPE-200-LIL-2-1-robotfactory-lucas.lhomme
## File description:
## Makefile
##

# Variables
NAME = corewar
CFLAGS = -I./include -I ./B-CPE-200_op/
FLAGS = -Wall -Wextra -W
SRC_PATH = ./src
SRC =	$(SRC_PATH)/main.c \

OBJ = $(SRC:.c=.o)
LIBMY = lib/libmy.a

# Default target
all: $(LIBMY) $(NAME)

# Compilation de l'exécutable principal
$(NAME): $(OBJ)
	gcc $(FLAGS) $(CFLAGS) -o $@ $^ -L./lib -lmy

# Compilation of object files
%.o: %.c
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

# Compilation of the library
$(LIBMY):
	$(MAKE) -C lib/my all

# Clean up object files and executables
clean:
	$(MAKE) -C lib/my/ clean
	rm -f $(OBJ)

# Full clean up
fclean: clean
	rm -f $(NAME)
	rm -f lib/libmy.a

# Rebuild everything
re: fclean all

# Debug mode
debug: CFLAGS += -g
debug: $(NAME)

# Rebuild in debug mode
redebug: fclean debug

# Phony targets
.PHONY: all clean fclean re debug redebug
