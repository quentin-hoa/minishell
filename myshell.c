/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** myshell
*/

#include "my.h"
#include <ncurses.h>
#include <sys/wait.h>

static int find_slash(char *command)
{
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '/')
            return 1;
    }
    return 0;
}

void free_list(char **list_of_args)
{
    for (int i = 0; list_of_args[i]; i++) {
        free(list_of_args[i]);
    }
    free(list_of_args);
}

static void wait_child(pid_t child_pid, int *status)
{
    waitpid(child_pid, status, 0);
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    else
        *status = 128 + WTERMSIG(*status);
}

int execute_command(char **list_of_args, char **env, int *status)
{
    char *exe_file;
    pid_t child_pid;

    exe_file = (find_slash(list_of_args[0])) ? my_strdup(list_of_args[0]) :
        get_exe_path(env, list_of_args[0]);
    if (!exe_file){
        my_printf("%s: Command not found.\n", list_of_args[0]);
        *status = 1;
        return 0;
    }
    child_pid = fork();
    if (child_pid == 0) {
        execve(exe_file, list_of_args, env);
        perror("execve");
        exit(1);
    }
    wait_child(child_pid, status);
    free(exe_file);
    return 0;
}

static int exec_setenv(char **list_of_args, char ***env)
{
    char **new_env;

    if (!list_of_args[1])
        return 1;
    new_env = init_new_env(*env);
    if (modif_var(list_of_args[1], new_env, list_of_args[2]) == 0) {
        free_list(*env);
        *env = new_env;
    } else {
        free_list(new_env);
    }
    return 0;
}

static int exec_unsetenv(char **list_of_args, char **env)
{
    if (!list_of_args[1] || my_strcmp(list_of_args[1], "") == 0) {
        write(2, "unsetenv: Too few arguments.\n", 30);
        return 1;
    }
    handle_unsetenv(list_of_args, env);
    return 0;
}

static int check_builtin_commands(char **args, char ***env, int *last_status)
{
    int status = 0;

    if (my_strcmp(args[0], "setenv") == 0) {
        if (exec_setenv(args, env) == 1)
            return handle_env(*env, last_status, args);
    } else if (my_strcmp(args[0], "unsetenv") == 0) {
        exec_unsetenv(args, *env);
    } else {
        execute_command(args, *env, &status);
    }
    free_list(args);
    *last_status = status;
    return 0;
}

int my_shell(char *line, char ***env, int *last_status)
{
    char **args = word_separator_space(line);
    int status = 0;

    if (!args || !line)
        return 84;
    if (my_strcmp(args[0], "exit") == 0) {
        if (args[1])
            *last_status = my_atoi(args[1]);
        free_list(args);
        return -42;
    }
    if (my_strcmp(args[0], "env") == 0)
        return handle_env(*env, last_status, args);
    if (my_strcmp(args[0], "cd") == 0)
        return cd_func(*env, last_status, args, &status);
    return check_builtin_commands(args, env, last_status);
}
