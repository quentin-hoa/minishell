/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** main
*/

#include "my.h"
#include <dirent.h>
#include <stddef.h>

int main(int ac, char **av, char **env)
{
    char *line =  NULL;
    size_t len = 0;
    int return_nb;
    int last_status = 0;

    if (ac != 1)
        return 84;
    while (1) {
        my_printf("$> ");
        if (getline(&line, &len, stdin) == -1)
            return last_status;
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        if (my_strcmp(line, "") == 0)
            continue;
        return_nb = my_shell(line, env, &last_status);
        if (return_nb == -42)
            break;
        if (return_nb == 84)
            return 84;
    }
    return last_status;
}