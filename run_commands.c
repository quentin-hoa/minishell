/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** run_commands
*/

#include "my.h"
#include <unistd.h>

const builtin_t builtins[NB_BUILTIN] = {
    {"exit", &exit_funct},
    {"cd", &new_cd},
    {"setenv", &do_setenv},
    {"unsetenv", &do_unsetenv}
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
    if (err == ENOEXEC)
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
    else if (err == EACCES)
        write(2, ": Permission denied.\n", 21);
    if (err == ENOENT)
        write(2, ": Command not found.\n", 21);
    else {
        write(2, ": ", 2);
        my_printf("%s", strerror(err));
        write(2, ".\n", 2);
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

static void do_exec(char **args, char **env_tab, char *path, int *last_status)
{
    if (execve(path, args, env_tab) == -1) {
        my_put_exec_error(args[0], errno);
        *last_status = 1;
        exit(1);
    }
}

static void free_end(char ***env_table, char **path)
{
    free_list(*env_table);
    free(*path);
}

static void call_error_exec(int *last_status, int status, pid_t pid)
{
    waitpid(pid, &status, 0);
    handle_error_status(status, last_status);
}

int execute_extern_command(char **args, env_t *head, int *last_status)
{
    char **env_tab = list_to_array(head);
    char *path = get_path(args[0], head);
    pid_t pid;
    int status = 0;

    if (!path) {
        write(2, args[0], my_strlen(args[0]));
        write(2, ": Command not found.\n", 22);
        return 1;
    }
    pid = fork();
    if (pid == -1)
        return 1;
    if (pid == 0)
        do_exec(args, env_tab, path, last_status);
    else
        call_error_exec(last_status, status, pid);
    free_end(&env_tab, &path);
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

int run_simple_cmd(char **args, env_t **head, int *last_status)
{
    int ret = 0;

    if (!args || !args[0])
        return 0;
    ret = check_builtins(args, head, last_status);
    if (ret != -1) {
        if (ret != -42)
            *last_status = ret;
        return ret;
    }
    *last_status = execute_extern_command(args, *head, last_status);
    return 0;
}
