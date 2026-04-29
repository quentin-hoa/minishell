/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** build_tree
*/

#include "my.h"

static treenode_t *check_semi(char *line, treenode_t *node)
{
    char *separator = my_strchr(line, ';');

    if (separator != NULL) {
        *separator = '\0';
        node = crea_tree_node(NULL, SEMI_COL);
        node->left = build_tree(line);
        node->right = build_tree(separator + 1);
        return node;
    }
    return NULL;
}

static treenode_t *check_pipe(char *line, treenode_t *node)
{
    char *separator = my_strchr(line, '|');

    if (separator != NULL) {
        *separator = '\0';
        node = crea_tree_node(NULL, PIPE);
        node->left = build_tree(line);
        node->right = build_tree(separator + 1);
        return node;
    }
    return NULL;
}

static treenode_t *check_re_r(char *line, treenode_t *node)
{
    char *separator = my_strchr(line, '>');

    if (separator != NULL) {
        if (*(separator + 1) == '>') {
            *separator = '\0';
            node = crea_tree_node(NULL, APPEND);
            node->left = build_tree(line);
            node->right = build_tree(separator + 2);
        } else {
            *separator = '\0';
            node = crea_tree_node(NULL, REDIR_R);
            node->left = build_tree(line);
            node->right = build_tree(separator + 1);
        }
        return node;
    }
    return NULL;
}

static treenode_t *check_re_l(char *line, treenode_t *node)
{
    char *separator = my_strchr(line, '<');

    if (separator != NULL) {
        if (*(separator + 1) == '<') {
            *separator = '\0';
            node = crea_tree_node(NULL, HEREDOC);
            node->left = build_tree(line);
            node->right = build_tree(separator + 2);
        } else {
            *separator = '\0';
            node = crea_tree_node(NULL, REDIR_L);
            node->left = build_tree(line);
            node->right = build_tree(separator + 1);
        }
        return node;
    }
    return NULL;
}

treenode_t *build_tree(char *line)
{
    treenode_t *node = NULL;

    node = check_semi(line, node);
    if (node)
        return node;
    node = check_pipe(line, node);
    if (node)
        return node;
    node = check_re_r(line, node);
    if (node)
        return node;
    node = check_re_l(line, node);
    if (node)
        return node;
    return crea_tree_node(word_separator_space(line), CMD);
}
