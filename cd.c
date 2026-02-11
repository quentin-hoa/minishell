/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** cd
*/

#include "my.h"

char *get_home_path(char **env)
{
    char *local_path;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "HOME=", 5) == 0) {
            local_path =  my_strdup(env[i] + 5);
            if (!local_path)
                return NULL;
            else
                return local_path;
        }
    }
    return NULL;
}

int handle_cd_path(char **list_of_args, char **env)
{
    char *cd_path;

    if (!list_of_args[1])
        cd_path = get_home_path(env);
    if (list_of_args[2]) {
        write(2, "cd: to many arguments.\n", 24);
        return 1;
    }
    else
        cd_path = my_strdup(list_of_args[1]);
    if (!cd_path) {
        write(2, "cd: No home directory.\n", 24);
        return 1;
    }
    if (chdir(cd_path) == -1) {
        perror(cd_path);
        free(cd_path);
        return 1;
    }
    free(cd_path);
    return 0;
}

int cd_func(char **env, int *last_status, char **list_of_args, int *status)
{
    *status = handle_cd_path(list_of_args, env);
    *last_status = *status;
    free_list(list_of_args);
    return *status;
}
