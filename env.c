/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** new_env
*/

#include "my.h"
#include <ncurses.h>

env_t *create_basic_node(char *key, char *val)
{
    env_t *new_node = malloc(sizeof(env_t));

    if (!new_node)
        return NULL;
    new_node->key = my_strdup(key);
    new_node->val = (val) ? my_strdup(val) : my_strdup("");
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void add_or_create_var(env_t **head, char *key, char *val)
{
    env_t *new_node = create_basic_node(key, val);
    env_t *tmp = *head;

    if (!new_node)
        return;
    if (!*head) {
        *head = new_node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
}

static int check_env_error(char *key)
{
    char *error =
        "setenv: Variable name must contain alphanumeric characters.\n";

    if (!((key[0] >= 'a' && key[0] <= 'z') ||
            (key[0] >= 'A' && key[0] <= 'Z'))) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return 1;
    }
    for (int i = 0; key[i]; i++) {
        if (!((key[i] >= 'a' && key[i] <= 'z') ||
                (key[i] >= 'A' && key[i] <= 'Z') ||
                (key[i] >= '0' && key[i] <= '9') || (key[i] == '_'))) {
            write(2, error, 60);
            return 1;
        }
    }
    return 0;
}

static int update_existing_var(env_t *current, char *key, char *val)
{
    while (current) {
        if (my_strcmp(key, current->key) == 0) {
            free(current->val);
            current->val = (val) ? my_strdup(val) : my_strdup("");
            return 1;
        }
        if (!current->next)
            break;
        current = current->next;
    }
    return 0;
}

int do_setenv(env_t **head, char **args, int *last_status)
{
    env_t *new_node = NULL;
    env_t *current = *head;
    char *key = args[1];
    char *val = args[2];

    if (!key) {
        print_env(*head);
        return 0;
    }
    if (check_env_error(key))
        return 1;
    if (*head && update_existing_var(*head, key, val))
        return 0;
    add_or_create_var(head, key, val);
    return 0;
}
