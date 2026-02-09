/*
** EPITECH PROJECT, 2025
** Day03
** File description:
** Alphabet
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int lenght = my_strlen(dest);
    int i = 0;

    for (; src[i] != '\0'; i++) {
        dest[i + lenght] = src[i];
    }
    dest[i + lenght] = '\0';
    return dest;
}
