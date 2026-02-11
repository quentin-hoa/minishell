/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** env
*/

#include "my.h"

int count_lines_env(char **env)
{
    int lines = 0;

    for(int i = 0; env[i]; i++) {
        lines++;
    }
    return lines;
}

void display_env(char **env)
{
    for (int i= 0; env[i]; i++) {
        my_printf("%s\n", env[i]);
    }
}

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

int check_var(char *var)
{
    if (!((var[0] >= 'a' && var[0] <= 'z') || (var[0] >= 'A' && var[0] <= 'Z'))) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return 84;
    }
    for (int i = 0; var[i] != '\0'; i++) {
        if (!((var[i] >= 'a' && var[i] <= 'z') || 
              (var[i] >= 'A' && var[i] <= 'Z') || 
              (var[i] >= '0' && var[i] <= '9') || 
              (var[i] == '_'))) {
            write(2, "setenv: Variable name must contain alphanumeric characters.\n", 60);
            return 84;
        }
    }
    return 0;
}

int modif_var(char *var, char **new_env, char *value) 
{
    int i = 0;
    int val_len = (value) ? my_strlen(value) : 0;
    char *temp;

    if (check_var(var) == 84)
        return 84;
    temp = malloc(my_strlen(var) + val_len + 2);
    if (!temp)
        return 84;
    my_strcpy(temp, var);
    my_strcat(temp, "=");
    my_strcat(temp, (value) ? value : "");
    for (;new_env[i]; i++) {
        if (my_strncmp(var, new_env[i], my_strlen(var)) == 0 && new_env[i][my_strlen(var)] == '=') {
            free(new_env[i]);
            new_env[i] = temp;
            return 0;
        }
    }
    new_env[i] = temp;
    new_env[i + 1] = NULL;
    return 0;
}