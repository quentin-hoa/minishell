##
## EPITECH PROJECT, 2025
## Day10
## File description:
## task01 Makefile
##

INCLUDE_PATH = ./include/

CFLAGS = -I$(INCLUDE_PATH) -g -Wall

NAME = mysh

SRC	= src/main.c \
	src/new_cd.c \
	src/utils.c \
	src/path.c \
	src/env.c \
	src/myshell.c \
	src/unsetenv.c \
	src/utils2.c \
	src/check_val.c \
	src/tree.c \
	src/run_commands.c \
	src/execute_buildin_2.c \
	src/build_tree.c \
	src/init_env.c

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	make -C ./lib
	clang $(OBJ) -o $(NAME)  -L./lib -lmy

push: fclean
	git add .
	git commit -m "$(COMMIT)"
	git push

clean:
	make clean -C ./lib
	rm -f $(OBJ)
fclean: clean
	make fclean -C ./lib
	rm -f $(NAME)

re: fclean all
