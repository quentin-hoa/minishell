/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** new_myhsell
*/

#include "my.h"

const builtin_t builtins[NB_BUILTIN] = {
    {"exit", (int (*)(env_t **, char **, int *))&exit_funct},
    {"cd", (int (*)(env_t **, char **, int *))&new_cd},
    {"setenv", (int (*)(env_t **, char **, int *))&do_setenv},
    {"unsetenv", (int (*)(env_t **, char **, int *))&do_unsetenv}
};

int exit_funct(env_t **head, char **args, int *last_status)
{
    if (isatty(0))
        write(1, "exit\n", 6);
    if (args[1]) {
        if (my_str_isnum(args[1])) {
            *last_status = my_atoi(args[1]);
        } else {
            write(2, "exit: Expression Syntax.\n", 25);
            *last_status = 1;
            return 1;
        }
    }
    return -42;
}

void my_put_exec_error(char *cmd, int err)
{
    write(2, cmd, my_strlen(cmd));
    if (err == ENOEXEC) {
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
    } else if (err == EACCES) {
        write(2, ": Permission denied.\n", 21);
    } else {
        write(2, ": Command not found.\n", 21);
    }
}

static void check_signals(int status)
{
    if (WTERMSIG(status) == SIGSEGV)
        write(2, "Segmentation fault\n", 19);
    if (WTERMSIG(status) == SIGFPE)
        write(2, "Floating exception\n", 19);
}

void handle_error_status(int status, int *last_status)
{
    if (WIFEXITED(status)) {
        *last_status = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        check_signals(status);
        *last_status = 128 + WTERMSIG(status);
    }
}

int execute_extern_command(char **args, env_t *head)
{
    char **env_tab = list_to_array(head);
    char *path = get_path(args[0], head);
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        return 1;
    if (pid == 0) {
        if (execve(path, args, env_tab) == -1) {
            my_put_exec_error(args[0], errno);
            exit(1);
        }
    } else {
        waitpid(pid, &status, 0);
        handle_error_status(status, &status);
    }
    free_list(env_tab);
    if (path)
        free(path);
    return status;
}

static int check_builtins(char **args, env_t **head, int *last_status)
{
    int ret = 0;

    for (int i = 0; i < NB_BUILTIN; i++) {
        if (my_strcmp(args[0], builtins[i].key) == 0) {
            ret = builtins[i].func(head, args, last_status);
            return ret;
        }
    }
    return -1;
}

int new_shell(char *str, env_t **head, int *last_status)
{
    char **args = word_separator_space(str);
    int ret = 0;

    if (!args || !args[0])
        return 0;
    ret = check_builtins(args, head, last_status);
    if (ret != -1) {
        if (ret != -42)
            *last_status = ret;
        free_list(args);
        return ret;
    }
    *last_status = execute_extern_command(args, *head);
    free_list(args);
    return 0;
}
