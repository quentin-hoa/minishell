##
## EPITECH PROJECT, 2025
## Day10
## File description:
## task01 Makefile
##

INCLUDE_PATH = ./include/
CFLAGS = -I$(INCLUDE_PATH) -g
NAME = libmy.a
EXE = setting_up

SRC	= src/my_0.c \
	src/my_c.c \
	src/my_d.c \
	src/my_e.c \
	src/my_ee.c \
	src/my_f.c \
	src/my_o.c \
	src/my_printf.c \
	src/my_put_decimal.c \
	src/my_revstr.c \
	src/my_s.c \
	src/my_space.c \
	src/my_strcat.c \
	src/my_strlen.c \
	src/my_x.c \
	src/my_xx.c \
	src/my_plus.c \
	src/my_p.c \
	src/my_b.c \
	src/my_atoi.c \
	src/my_strdup.c \
	src/is_alpha_or_number.c \
	src/mini.c \
	src/my_strcmp.c \
	src/my_strcpy.c \
	src/my_str_to_word_array.c \
	src/my_to_lower.c \
	src/word_separator_space.c \
	src/str_to_word_array_delim.c

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)


re: fclean all
