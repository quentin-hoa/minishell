/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** utils
*/

#include "my.h"

int check_var(char *var)
{
    char *e = "setenv: Variable name must contain alphanumeric characters.\n";

    if (!((var[0] >= 'a' && var[0] <= 'z')
        || (var[0] >= 'A' && var[0] <= 'Z'))) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return 84;
    }
    for (int i = 0; var[i] != '\0'; i++) {
        if (!((var[i] >= 'a' && var[i] <= 'z') ||
            (var[i] >= 'A' && var[i] <= 'Z') ||
            (var[i] >= '0' && var[i] <= '9') ||
            (var[i] == '_'))) {
            write(2, e, 60);
            return 84;
        }
    }
    return 0;
}

void shift_values(char **env, int j)
{
    while (env[j]) {
        env[j] = env[j + 1];
        j++;
    }
}

int count_lines_env(char **env)
{
    int lines = 0;

    for (int i = 0; env[i]; i++) {
        lines++;
    }
    return lines;
}

void display_env(char **env)
{
    for (int i = 0; env[i]; i++) {
        my_printf("%s\n", env[i]);
    }
}

int is_only_space(char *line)
{
    int count = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ' ' || line[i] == '\t')
            count++;
    }
    if (count == my_strlen(line))
        return 1;
    return 0;
}
