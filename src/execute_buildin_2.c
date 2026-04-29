/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** execute_buildin_2
*/

#include "my.h"
#include <fcntl.h>
#include <stddef.h>

int check_fd(int fd, char **file, int *last_status)
{
    if (fd == -1) {
        perror(*file);
        *last_status = 1;
        return 1;
    }
    return 0;
}

int execute_redir_r(treenode_t *node, env_t **head, int *last_status)
{
    char *file;
    int fd;
    int save_stdout;
    int macro = (node->type == APPEND) ? O_APPEND : O_TRUNC;
    int ret;

    if (!node->right || !node->right->args)
        return 1;
    file = node->right->args[0];
    fd = open(file, O_WRONLY | O_CREAT | macro, 0644);
    if (check_fd(fd, &file, last_status) == 1)
        return 1;
    save_stdout = dup(1);
    dup2(fd, 1);
    close(fd);
    ret = execute_tree(node->left, head, last_status);
    dup2(save_stdout, 1);
    close(save_stdout);
    return ret;
}

static void do_fork_left(int pipefd[], treenode_t *node,
    env_t **head, int *last_status)
{
    close(pipefd[0]);
    dup2(pipefd[1], 1);
    close(pipefd[1]);
    exit(execute_tree(node->left, head, last_status));
}

static void do_fork_right(int pipefd[], treenode_t *node,
    env_t **head, int *last_status)
{
    close(pipefd[1]);
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    exit(execute_tree(node->right, head, last_status));
}

int execute_pipe(treenode_t *node, env_t **head, int *last_status)
{
    int pipefd[2];
    pid_t pid_left;
    pid_t pid_right;
    int status;

    if (pipe(pipefd) == -1)
        return 1;
    pid_left = fork();
    if (pid_left == 0)
        do_fork_left(pipefd, node, head, last_status);
    pid_right = fork();
    if (pid_right == 0)
        do_fork_right(pipefd, node, head, last_status);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid_left, &status, 0);
    waitpid(pid_right, &status, 0);
    handle_error_status(status, last_status);
    return *last_status;
}

int write_heredoc_to_file(treenode_t *node)
{
    int fd = open(".tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC);
    size_t len = 0;
    char *line = NULL;
    char *delimiter = node->right->args[0];

    if (fd == -1 || !delimiter)
        return -84;
    while (isatty(0)) {
        write(1, "? ", 2);
        if (getline(&line, &len, stdin) == -1)
            break;
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        if (my_strcmp(line, delimiter) == 0)
            break;
        write(fd, line, my_strlen(line));
        write(fd, "\n", 1);
    }
    close(fd);
    return 0;
}

static int check_heredoc(treenode_t *node, int *last_status,
    char **file, int *fd)
{
    if (node->type == HEREDOC) {
        if (write_heredoc_to_file(node) == -84) {
            write(2, "Missing name for redirect.\n", 27);
            *last_status = 1;
            return 1;
        }
        *fd = open(".tmp_heredoc", O_RDONLY);
        *file = ".tmp_heredoc";
    } else {
        *file = node->right->args[0];
        *fd = open(*file, O_RDONLY);
    }
    return 0;
}

int execute_redir_l(treenode_t *node, env_t **head, int *last_status)
{
    char *file = NULL;
    int fd = 0;
    int save_stdin = dup(0);
    int ret;

    if (!node->right || !node->right->args)
        return 1;
    if (check_heredoc(node, last_status, &file, &fd) == 1)
        return 1;
    if (check_fd(fd, &file, last_status) == 1)
        return 1;
    dup2(fd, 0);
    close(fd);
    ret = execute_tree(node->left, head, last_status);
    dup2(save_stdin, 0);
    close(save_stdin);
    return ret;
}
