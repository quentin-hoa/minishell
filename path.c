/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** path
*/

#include "my.h"

static char *get_path_line(char **env)
{
    char *result = NULL;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0) {
            result = my_strdup(env[i] + 5);
            break;
        }
    }
    return result;
}

static char *search_in_path(char *line_path, char *command)
{
    char *new_path = NULL;
    char *test_path = strtok(line_path, ":");

    while (test_path) {
        new_path = malloc(my_strlen(test_path) + my_strlen(command) + 2);
        my_strcpy(new_path, test_path);
        my_strcat(new_path, "/");
        my_strcat(new_path, command);
        if (access(new_path, F_OK | X_OK) == 0)
            return new_path;
        free(new_path);
        test_path = strtok(NULL, ":");
    }
    return NULL;
}

char *get_exe_path(char **env, char *command)
{
    char *line_path = NULL;
    char *result;

    line_path = get_path_line(env);
    if (!line_path)
        return NULL;
    result = search_in_path(line_path, command);
    free(line_path);
    return result;
}
