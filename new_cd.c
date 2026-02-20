/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** new_cd
*/

#include "my.h"

void my_put_cd_error(char *path, char *arg)
{
    if (!path)
        write(2, "cd: No home directory.\n", 23);
    else {
        write(2, arg, my_strlen(arg));
        write(2, ": No such file or directory.\n", 29);
    }
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

int new_cd(env_t **head, char **args, int *last_status)
{
    char *path = NULL;
    char *old_cwd = getcwd(NULL, 0);

    if (!args[1] || my_strcmp(args[1], "~") == 0)
        path = my_strdup(get_env_val(*head, "HOME"));
    else if (my_strcmp(args[1], "-") == 0)
        path = my_strdup(get_env_val(*head, "OLDPWD"));
    else
        path = my_strdup(args[1]);
    if (!path || chdir(path) == -1) {
        my_put_cd_error(path, args[1]);
        free(old_cwd); free(path);
        return 1;
    }
    char *args_old[] = {"setenv", "OLDPWD", old_cwd, NULL};
    do_setenv(head, args_old, NULL);
    update_pwd(head);
    free(old_cwd); free(path);
    return 0;
}
