/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** new_path
*/

#include "my.h"

char *build_path(char *dir, char *command)
{
    int len = my_strlen(dir) + my_strlen(command) + 2;
    char *path = malloc(sizeof(char) * len);

    if (!path)
        return NULL;
    my_strcpy(path, dir);
    my_strcat(path, "/");
    my_strcat(path, command);
    return path;
}

static char *get_path_from_list(env_t *head)
{
    env_t *tmp = head;

    while (tmp) {
        if (my_strcmp(tmp->key, "PATH") == 0)
            return my_strdup(tmp->val);
        tmp = tmp->next;
    }
    return NULL;
}

static char *search_path(char **dirs, char *command, char *path_env)
{
    char *full_path = NULL;

    for (int i = 0; dirs[i]; i++) {
        full_path = build_path(dirs[i], command);
        if (access(full_path, F_OK) == 0) {
            free_list(dirs);
            free(path_env);
            return full_path;
        }
        free(full_path);
    }
    return NULL;
}

char *get_path(char *command, env_t *head)
{
    char *path_env = NULL;
    char *res = NULL;
    char **dirs = NULL;

    if (find_slash(command)) {
        if (access(command, F_OK) == 0)
            return my_strdup(command);
        return NULL;
    }
    path_env = get_path_from_list(head);
    if (!path_env)
        return NULL;
    dirs = my_str_to_word_array_delim(path_env, ':');
    res = search_path(dirs, command, path_env);
    if (res)
        return res;
    free_list(dirs);
    free(path_env);
    return NULL;
}
