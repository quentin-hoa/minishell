/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** execute_buildin_2
*/

#include "my.h"
#include <fcntl.h>

int execute_redir_r(treenode_t *node, env_t **head, int *last_status)
{
    char *file;
    int fd;
    int save_stdout;

    if (!node->right || !node->right->args)
        return 1;
    file = node->right->args[0];
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror(file);
        *last_status = 1;
        return 1;
    }
    save_stdout = dup(1);
    dup2(fd, 1);
    close(fd);
    execute_tree(node->left, head, last_status);
    dup2(save_stdout, 1);
    close(save_stdout);
    return 0;
}

int execute_pipe(treenode_t *node, env_t **head, int *last_status)
{
    return 0;
}
