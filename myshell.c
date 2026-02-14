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
    for (int  i = 0; list_of_args[i]; i++) {
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

int my_shell(char *line, char ***env, int *last_status)
{
    char **list_of_args = word_separator_space(line);
    int status = 0;
    char **new_env = NULL;
    char **old_env = NULL;

    if (!list_of_args || !line)
        return 84;
    if (my_strcmp(list_of_args[0], "exit") == 0) {
        if (list_of_args[1]) {
            *last_status = my_atoi(list_of_args[1]);
        }
        free_list(list_of_args);
        return -42;
    }
    if (my_strcmp(list_of_args[0], "env") == 0)
        return handle_env(*env, last_status, list_of_args);
    if (my_strcmp(list_of_args[0], "cd") == 0)
        return cd_func(*env, last_status, list_of_args, &status);
    if (my_strcmp(list_of_args[0], "setenv") == 0) {
        if (!list_of_args[1]) {
            return handle_env(*env, last_status, list_of_args);
        }
        old_env = *env;
        new_env = init_new_env(old_env);
        if (modif_var(list_of_args[1], new_env, list_of_args[2]) == 0) {
            *env = new_env;
            free_list(old_env);
        } else {
            free_list(new_env);
        }
        free_list(list_of_args);
        return 0;
    }
    if (my_strcmp(list_of_args[0], "unsetenv") == 0) {
        if (!list_of_args[1] || my_strcmp(list_of_args[1], "") == 0) {
            write(2, "unsetenv: Too few arguments.\n", 30);
            free(list_of_args);
            return 0;
        }
        old_env = *env;
        new_env = handle_unsetenv(list_of_args, *env);
        free_list(list_of_args);
        return 0;
    }
    else {
        if (execute_command(list_of_args, *env, &status) == 84) {
            return 84;
        }
    }
    free_list(list_of_args);
    *last_status = status;
    return 0;
}
