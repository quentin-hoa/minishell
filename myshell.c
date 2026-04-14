/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** new_myhsell
*/

#include "my.h"

int shell(char *str, env_t **head, int *last_status)
{
    char *cp_line = my_strdup(str);
    treenode_t *root = build_tree(cp_line);
    int ret = 0;

    if (!root) {
        free(cp_line);
        return 0;
    }
    ret = execute_tree(root, head, last_status);
    free_tree(root);
    free(cp_line);
    return ret;
}
