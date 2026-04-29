/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** new_cd
*/

#include "my.h"
#include <stdio.h>

const cd_error_t errors_cd[] = {
    {ENOENT, ": No such file or directory.\n"},
    {EACCES, ": Permission denied.\n"},
    {ENOTDIR, ": Not a directory.\n"}
};

void my_put_cd_error(char *path, char *arg)
{
    if (!path) {
        write(2, "cd: No home directory.\n", 23);
        return;
    }
    write(2, path, my_strlen(path));
    for (int i = 0; i < 3; i++) {
        if (errno == errors_cd[i].code) {
            write(2, errors_cd[i].msg, my_strlen(errors_cd[i].msg));
            return;
        }
    }
    write(2, ": ", 2);
    write(2, strerror(errno), my_strlen(strerror(errno)));
    write(2, ".\n", 2);
}

static char *get_env_val(env_t *head, char *key)
{
    env_t *tmp = head;

    while (tmp) {
        if (my_strcmp(tmp->key, key) == 0)
            return tmp->val;
        tmp = tmp->next;
    }
    return NULL;
}

static void update_pwd(env_t **head)
{
    char *cwd = getcwd(NULL, 0);
    char *args_pwd[] = {"setenv", "PWD", cwd, NULL};

    if (cwd) {
        do_setenv(head, args_pwd, NULL);
        free(cwd);
    }
}

static void end_funct(char **args_old, env_t **head)
{
    do_setenv(head, args_old, NULL);
    update_pwd(head);
}

int new_cd(env_t **head, char **args, int *last_status)
{
    char *path = NULL;
    char *old_cwd = getcwd(NULL, 0);
    char *args_old[] = {"setenv", "OLDPWD", old_cwd, NULL};

    if (!args[1] || my_strcmp(args[1], "~") == 0)
        path = my_strdup(get_env_val(*head, "HOME"));
    else if (my_strcmp(args[1], "-") == 0)
        path = my_strdup(get_env_val(*head, "OLDPWD"));
    else
        path = my_strdup(args[1]);
    if (!path || chdir(path) == -1) {
        my_put_cd_error(path, args[0]);
        free(old_cwd);
        free(path);
        return 1;
    }
    end_funct(args_old, head);
    free(old_cwd);
    free(path);
    return 0;
}
