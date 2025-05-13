##
## EPITECH PROJECT, 2024
## Makefile lib
## File description:
## MakeFile dans le fichier lib
##

SRC_DIR		=	.

LIB_DIR		=	../

CFLAGS		=	-I../../include

LIB =	./my_compute_power_rec.c\
	./my_getnbr.c\
	./my_isneg.c\
	./my_put_nbr.c\
	./my_putchar.c\
	./my_putstr.c\
	./my_strdup.c\
	./my_strncmp.c\
	./my_strcpy.c\
	./my_strlen.c\
	./my_strncpy.c\
	./my_swap.c\
	./my_sort_params.c\
	./my_revstr.c\
	./my_str_to_word_array.c\
	./flag_c.c\
	./flag_d.c\
	./flag_i.c\
	./flag_o.c\
	./flag_percent.c\
	./flag_s.c\
	./flag_x.c\
	./flag_x2.c\
	./my_printf.c\
	./my_strcmp.c\
	./my_strnmajcmp.c\
	./my_strcat.c\
	./my_show_word_in_array.c\
	./my_getenv.c\
	./extract_str.c\
	./extract_str_advanced.c\
	./my_strchr.c\
	./my_strtok.c\
	./my_str_to_word_array_advanced.c\
	./my_str_tolower.c\
	./my_free_word_array.c\
	./my_atoi.c\
	./my_isalpha.c\
	./my_strncat.c\
	./my_isdigit.c\
	./my_str_isalnum.c\
	./free_array.c\
	./my_compute_square_root.c\
	./my_strmajcmp.c\
	./my_str_isnum.c\
	./my_copy_word_in_array.c\
	./my_strisalnum.c\
	./my_puterror.c\
	./my_strstr.c\
	./my_strtol.c\

OBJ		=	$(LIB:.c=.o)

NAME	=	libmy.a

all:			$(NAME)

$(NAME):		$(OBJ)
		ar rc -o $(NAME) $(OBJ)
		mv $(NAME) $(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(LIB_DIR)$(NAME)

re: fclean all
