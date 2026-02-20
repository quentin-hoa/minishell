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

int count_nodes(env_t *head)
{
    int i = 0;
    env_t *tmp = head;

    while (tmp) {
        i++;
        tmp = tmp->next;
    }
    return i;
}

char *my_strcat_env(char *key, char *val)
{
    int len_key = my_strlen(key);
    int len_val = my_strlen(val);
    char *res = malloc(sizeof(char) * (len_key + len_val + 2));
    int i = 0;
    int j = 0;

    if (!res)
        return NULL;
    while (key[i]) {
        res[i] = key[i];
        i++;
    }
    res[i++] = '=';
    while (val[j]) {
        res[i + j] = val[j];
        j++;
    }
    res[i + j] = '\0';
    return res;
}

char **list_to_array(env_t *head)
{
    int size = count_nodes(head);
    char **array = malloc(sizeof(char *) * (size + 1));
    env_t *tmp = head;
    char *full;

    if (!array) return NULL;
    for (int i = 0; i < size; i++) {
        full = my_strcat_env(tmp->key, tmp->val);
        array[i] = full;
        tmp = tmp->next;
    }
    array[size] = NULL;
    return array;
}

int find_slash(char *command)
{
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '/')
            return 1;
    }
    return 0;
}

void free_list(char **list_of_args)
{
    for (int i = 0; list_of_args[i]; i++) {
        free(list_of_args[i]);
    }
    free(list_of_args);
}

int my_str_isnum(char *str)
{
    int i = 0;

    if (!str || str[0] == '\0')
        return 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

void free_env_list(env_t *head)
{
    env_t *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp->val);
        free(tmp);
    }
}
