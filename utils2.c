/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** utils2
*/

#include "my.h"

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
