/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** myshell
*/

#include "my.h"

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

static char *get_path_line(char **env)
{
    char *result = NULL;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0) {
            result = my_strdup(env[i] + 5);
            break;
        }
    }
    return result;
}

static char *get_exe_path(char **env, char *command)
{
    char *line_path = NULL;
    char *new_path = NULL;
    char *test_path;

    line_path = get_path_line(env);
    if (!line_path)
        return NULL;
    test_path = strtok(line_path, ":");
    while (test_path) {
        new_path = malloc(my_strlen(test_path) + my_strlen(command) + 2);
        my_strcpy(new_path, test_path);
        my_strcat(new_path, "/");
        my_strcat(new_path, command);
        if (access(new_path, F_OK | X_OK) == 0) {
            free(line_path);
            return new_path;
        }
        free(new_path);
        test_path = strtok(NULL, ":");
    }
    free(line_path);
    return NULL;
}

int execute_command(char **list_of_args, char **env, int *status)
{
    char *exe_file;
    pid_t child_pid;

    if (find_slash(list_of_args[0]) == 1)
        exe_file = my_strdup(list_of_args[0]);
    else
        exe_file = get_exe_path(env, list_of_args[0]);
    if (!exe_file){
        my_printf("%s: Command not found.\n", list_of_args[0]);
        *status = 1;
        return 0;
    }
    child_pid = fork();
    if (child_pid == -1)
        return 84;
    if (child_pid == 0) {
        execve(exe_file, list_of_args, env);
        perror("execve");
        exit(1);
    } else {
        waitpid(child_pid, status, 0);
        if (WIFEXITED(*status))
            *status = WEXITSTATUS(*status);
        else
            *status = 128 + WTERMSIG(*status);
    }
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
