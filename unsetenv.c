/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** unsetenv
*/

#include "my.h"

void free_node(env_t *node)
{
    free(node->key);
    free(node->val);
    free(node);
}

void del_node(env_t **head, env_t *node)
{
    if (!node)
        return;
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        *head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    free_node(node);
}

static void find_and_del(env_t **head, char *key)
{
    env_t *current = *head;

    while (current) {
        if (my_strcmp(current->key, key) == 0) {
            del_node(head, current);
            return;
        }
        current = current->next;
    }
}

void do_unsetenv(env_t **head, char **args, int *last_status)
{
    if (!args[0])
        return;
    for (int i = 1; args[i]; i++) {
        find_and_del(head, args[i]);
    }
}
