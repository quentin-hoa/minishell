/*
** EPITECH PROJECT, 2025
** Day03
** File description:
** Alphabet
*/

#include "my.h"

int my_s_caller(va_list list)
{
    char *str = va_arg(list, char *);

    return my_s(str);
}

int my_s(char *str)
{
    for (int i = 0; str[i] != '\0'; i++){
        my_c(str[i]);
    }
    return my_strlen(str);
}
