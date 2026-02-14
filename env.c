/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** env
*/

#include "my.h"

int handle_env(char **env, int *last_status, char **list_of_args)
{
    display_env(env);
    *last_status = 0;
    free_list(list_of_args);
    return 0;
}

char **init_new_env(char **env)
{
    int lines = count_lines_env(env);
    char **new_env = malloc(sizeof(char *) * (lines + 2));
    int i = 0;

    if (!new_env)
        return NULL;
    for (; env[i]; i++) {
        new_env[i] = my_strdup(env[i]);
    }
    new_env[i] = NULL;
    new_env[i + 1] = NULL;
    return new_env;
}

static char *make_path(char *temp, char *var, char *value)
{
    int val_len = (value) ? my_strlen(value) : 0;

    temp = malloc(my_strlen(var) + val_len + 2);
    if (!temp)
        return NULL;
    my_strcpy(temp, var);
    my_strcat(temp, "=");
    my_strcat(temp, (value) ? value : "");
    return temp;
}

int modif_var(char *var, char **new_env, char *value)
{
    int i = 0;
    char *temp;

    if (check_var(var) == 84)
        return 84;
    temp = make_path(temp, var, value);
    if (!temp)
        return 84;
    for (;new_env[i]; i++) {
        if (my_strncmp(var, new_env[i], my_strlen(var)) == 0
            && new_env[i][my_strlen(var)] == '=') {
            free(new_env[i]);
            new_env[i] = temp;
            return 0;
        }
    }
    new_env[i] = temp;
    new_env[i + 1] = NULL;
    return 0;
}

char **handle_unsetenv(char **list_of_args, char **env)
{
    int j = 0;

    for (int i = 1; list_of_args[i]; i++) {
        for (j = 0; env[j]; j++) {
            if (my_strncmp(list_of_args[i], env[j],
                my_strlen(list_of_args[i])) == 0
                && env[j][my_strlen(list_of_args[i])] == '=') {
                free(env[j]);
                shift_values(env, j);
                break;
            }
        }
    }
    return env;
}
