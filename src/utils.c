/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** utils
*/

#include "my.h"

int count_nodes(env_t *head)
{
    int i = 0;
    env_t *tmp = head;

    while (tmp) {
        i++;
        tmp = tmp->next;
    }
    return i;
}

char *my_strcat_env(char *key, char *val)
{
    int len_key = my_strlen(key);
    int len_val = my_strlen(val);
    char *res = malloc(sizeof(char) * (len_key + len_val + 2));
    int i = 0;
    int j = 0;

    if (!res)
        return NULL;
    while (key[i]) {
        res[i] = key[i];
        i++;
    }
    res[i] = '=';
    i++;
    while (val[j]) {
        res[i + j] = val[j];
        j++;
    }
    res[i + j] = '\0';
    return res;
}

char **list_to_array(env_t *head)
{
    int size = count_nodes(head);
    char **array = malloc(sizeof(char *) * (size + 1));
    env_t *tmp = head;
    char *full;

    if (!array)
        return NULL;
    for (int i = 0; i < size; i++) {
        full = my_strcat_env(tmp->key, tmp->val);
        array[i] = full;
        tmp = tmp->next;
    }
    array[size] = NULL;
    return array;
}
