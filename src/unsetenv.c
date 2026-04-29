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

static int find_and_del(env_t **head, char *key)
{
    env_t *current = *head;

    while (current) {
        if (my_strcmp(current->key, key) == 0) {
            del_node(head, current);
            return 0;
        }
        current = current->next;
    }
    return -84;
}

int do_unsetenv(env_t **head, char **args, int *last_status)
{
    if (!args[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return 1;
    }
    for (int i = 1; args[i]; i++) {
        if (find_and_del(head, args[i]) == -84) {
            *last_status = 1;
            return 1;
        }
    }
    return 0;
}
