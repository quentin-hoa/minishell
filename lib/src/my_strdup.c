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
