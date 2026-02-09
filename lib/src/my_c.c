/*
** EPITECH PROJECT, 2025
** POINTEURS
** File description:
** Evil swap string
*/

#include "my.h"

int my_c_caller(va_list list)
{
    char c = va_arg(list, int);

    return my_c(c);
}

int my_c(char c)
{
    return write(1, &c, 1);
}
