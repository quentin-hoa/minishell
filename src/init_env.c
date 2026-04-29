/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** init_env
*/

#include "my.h"

void print_env(env_t *head)
{
    env_t *current = head;

    while (current) {
        my_printf("%s=%s\n", current->key, current->val);
        current = current->next;
    }
}

env_t *create_node(char *str)
{
    env_t *node = malloc(sizeof(env_t));
    char *separator;

    if (!node)
        return NULL;
    separator = my_strchr(str, '=');
    if (!separator) {
        node->key = my_strdup(str);
        node->val = my_strdup("");
    } else {
        node->key = my_strndup(str, separator - str);
        node->val = my_strdup(separator + 1);
    }
    node->next = NULL;
    node->prev = NULL;
    return node;
}

env_t *init_env_list(char **env)
{
    env_t *head = NULL;
    env_t *new_node = NULL;
    env_t *last = NULL;

    if (!env || !env[0])
        return NULL;
    for (int i = 0; env[i]; i++) {
        new_node = create_node(env[i]);
        if (!head) {
            head = new_node;
            last = new_node;
            head->prev = NULL;
        } else {
            last->next = new_node;
            new_node->prev = last;
            last = new_node;
        }
    }
    return head;
}
