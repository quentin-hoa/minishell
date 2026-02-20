##
## EPITECH PROJECT, 2025
## Day10
## File description:
## task01 Makefile
##

INCLUDE_PATH = ./include/

CFLAGS = -I$(INCLUDE_PATH) -g -Wall

NAME = mysh

SRC	= main.c \
	new_cd.c \
	utils.c \
	new_path.c \
	new_env.c \
	new_myshell.c \
	unsetenv.c \
	utils2.c

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	make -C ./lib
	clang *.o -o $(NAME)  -L./lib -lmy

push: fclean
	git add .
	git commit -m "$(COMMIT)"
	git push

clean:
	rm -f $(OBJ)
fclean: clean
	make fclean -C ./lib
	rm -f $(NAME)

re: fclean all
