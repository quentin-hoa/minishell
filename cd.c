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
    else
        cd_path = my_strdup(list_of_args[1]);
    if (chdir(cd_path) == -1) {
        perror(cd_path);
        return -1;
    }
    free(cd_path);
    return 0;
}
