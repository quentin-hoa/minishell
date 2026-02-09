/*
** EPITECH PROJECT, 2025
** My Str Len
** File description:
** My Str Len
*/

#include "my.h"

int my_strlen(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        count++;
    return count;
}
