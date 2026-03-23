/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** tree
*/

#include "my.h"
#include <stdlib.h>
#include <termios.h>

treenode_t *crea_tree_node(char **args, type_t type)
{
    treenode_t *new = malloc(sizeof(treenode_t));

    if (!new)
        return NULL;
    new->args = args;
    new->type = type;
    new->left = NULL;
    new->right = NULL;
    return new;
}

int execute_tree(treenode_t *node, env_t **head, int *last_status)
{
    if (!node)
        return 0;
    if (node->type == SEMI_COL) {
            execute_tree(node->left, head, last_status);
        return execute_tree(node->right, head, last_status);
    }
    if (node->type == PIPE)
        return execute_pipe(node, head, last_status);
    if (node->type == REDIR_R || node->type == APPEND)
        return execute_redir_r(node, head, last_status);
    if (node->type == REDIR_L || node->type == HEREDOC)
        return execute_redir_l(node, head, last_status);
    if (node->type == CMD)
        return run_simple_cmd(node->args, head, last_status);
    return 0;
}
