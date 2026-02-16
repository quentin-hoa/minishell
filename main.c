/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** main
*/

#include "my.h"
#include <dirent.h>
#include <stddef.h>

static void process_line(char *line, char ***my_env, int *last_status,
    int *ret)
{
    if (line[my_strlen(line) - 1] == '\n')
        line[my_strlen(line) - 1] = '\0';
    if (is_only_space(line) == 1)
        return;
    if (my_strcmp(line, "") == 0)
        return;
    *ret = my_shell(line, my_env, last_status);
}

static int shell_loop(char **my_env, int *last_status)
{
    char *line = NULL;
    size_t len = 0;
    int ret = 0;

    while (1) {
        write(1, "$> ", 3);
        if (getline(&line, &len, stdin) == -1)
            break;
        process_line(line, &my_env, last_status, &ret);
        if (ret == -42 || ret == 84)
            break;
    }
    free(line);
    return ret;
}

int main(int ac, char **av, char **env)
{
    int last_status = 0;
    int ret_nb = 0;
    char **my_env = init_new_env(env);

    if (ac != 1)
        return 84;
    ret_nb = shell_loop(my_env, &last_status);
    free_list(my_env);
    if (ret_nb == 84)
        return 84;
    return last_status;
}
