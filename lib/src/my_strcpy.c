/*
** EPITECH PROJECT, 2025
** POINTEURS
** File description:
** copy string
*/

#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *my_strncpy(char *dest, char const *src, int nb)
{
    int i = 0;

    for (i = 0; i < nb; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
