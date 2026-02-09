/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** main
*/

#include "lib/include/my.h"
#include "my.h"
#include <stddef.h>

static void display_env(char **env)
{
    for (int i= 0; env[i]; i++) {
        my_printf("%s\n", env[i]);
    }
}

static void free_list(char **list_of_args)
{
    for (int  i = 0; list_of_args[i]; i++) {
        free(list_of_args[i]);
    }
    free(list_of_args);
}

static void exe_command(char **list_of_args, pid_t child_pid, int status, int nb_args)
{
    my_printf("Program name: %s\n", list_of_args[0]);
    my_printf("Nb args: %d\n", nb_args);
    my_printf("PID: %d\n", getpid());
    my_printf("Child PID: %d\n", child_pid);
    waitpid(child_pid, &status, 0);
    my_printf("Program terminated.\nStatus: ");
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGSEGV)
            my_printf("Segmentation fault\n");
        else
            my_printf("Killed by signal %d\n", WTERMSIG(status));
    } else {
        my_printf("OK\n");
    }
}

char *getpaht(char **env, char *command)
{
    char *line_path = NULL;
    char *new_path = NULL;
    char *test_path;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0) {
            line_path = my_strdup(env[i] + 5);
            break;
        }
    }
    if (!line_path)
        return NULL;
    test_path = strtok(line_path, ":");
    while (test_path) {
        new_path = malloc(my_strlen(test_path) + my_strlen(command) + 2);
        my_strcpy(new_path, test_path);
        my_strcat(new_path, "/");
        my_strcat(new_path, command);
        if (access(new_path, F_OK | X_OK) == 0)
            return new_path;
        free(new_path);
        test_path = strtok(NULL, ":");
    }
    return NULL;
}

int print_info(char *av, char **env)
{
    char **list_of_args = word_separator_space(av);
    int nb_args = 0;
    pid_t child_pid;
    int status = 0;
    char *path;

    if (!list_of_args)
        return 84;
    if (my_strcmp(list_of_args[0], "exit") == 0)
        return 1;
    if (my_strcmp(list_of_args[0], "env") == 0) {
        display_env(env);
        return 0;
    }
    path = getpaht(env, list_of_args[0]);
    while (list_of_args[nb_args])
        nb_args++;
    nb_args = (nb_args > 0) ? nb_args - 1 : 0;
    child_pid = fork();
    if (child_pid == -1)
        return 84;
    if (child_pid == 0) {
        execve(path, list_of_args, env);
        perror("execve");
        exit(84);
    } else {
        exe_command(list_of_args, child_pid, status, nb_args);
    }
    free_list(list_of_args);
    return 0;
}

int main(int ac, char **av, char **env)
{
    char *line =  NULL;
    size_t len = 0;
    int return_nb;

    if (ac != 1)
        return 84;
    while (1) {
        my_printf("\n$> ");
        if (getline(&line, &len, stdin) == -1)
            return 84;
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        return_nb = print_info(line, env);
        if (return_nb == 1)
            break;
        if (return_nb == 84)
            return 84;

    }
    return 0;
}