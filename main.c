/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** main
*/

#include "my.h"
#include <dirent.h>
#include <stddef.h>
#include <stdlib.h>

static void handle_line(char *line, env_t **env_list, int *last_status)
{
    int ret = 0;

    if (line[my_strlen(line) - 1] == '\n')
        line[my_strlen(line) - 1] = '\0';
    if (line[0] == '\0')
        return;
    ret = new_shell(line, env_list, last_status);
    if (ret == -42) {
        free(line);
        exit(*last_status);
    }
}

int shell_loop(env_t *env_list)
{
    char *line = NULL;
    size_t len = 0;
    int last_status = 0;

    if (isatty(0))
        write(1, "$> ", 3);
    while (getline(&line, &len, stdin) != -1) {
        handle_line(line, &env_list, &last_status);
        if (isatty(0))
            write(1, "$> ", 3);
    }
    if (isatty(0))
        write(1, "exit\n", 5);
    free(line);
    return last_status;
}

int main(int ac, char **av, char **env)
{
    env_t *env_list = NULL;
    int status = 0;

    if (ac != 1)
        return 84;
    env_list = init_env_list(env);
    status = shell_loop(env_list);
    free_env_list(env_list);
    return status;
}
