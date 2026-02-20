/*
** EPITECH PROJECT, 2025
** strdup
** File description:
** strdup
*/

#include "my.h"

char *my_strdup(char *str)
{
    int len = my_strlen(str) + 1;
    char *result = malloc(len);
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        result[i] = str[i];
    }
    result[i] = '\0';
    return result;
}

char *my_strndup(char const *src, int n)
{
    char *dest = malloc(sizeof(char) * (n + 1));
    int i = 0;

    if (!dest)
        return NULL;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strchr(char const *str, int c)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == (char)c) {
            return (char *)&str[i];
        }
        i++;
    }
    if ((char)c == '\0') {
        return (char *)&str[i];
    }
    return NULL;
}
