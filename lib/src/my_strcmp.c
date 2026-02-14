/*
** EPITECH PROJECT, 2025
** strcmp
** File description:
** strcmp
*/

#include "my.h"

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
        i++;
    }
    return (s1[i] - s2[i]);
}

int my_strncmp(char *s1, char *s2, int n)
{
    int i = 0;

    if (n <= 0)
        return 0;
    while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
        i++;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
