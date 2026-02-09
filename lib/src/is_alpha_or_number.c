/*
** EPITECH PROJECT, 2025
** Printf
** File description:
** add 0 to the left for int
*/

#include "my.h"

int is_alpha_char(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

int is_number(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}
