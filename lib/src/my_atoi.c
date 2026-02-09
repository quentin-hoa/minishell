/*
** EPITECH PROJECT, 2025
** Atoi
** File description:
** transform a string of number into an int
*/
#include "my.h"

int my_atoi(char *str)
{
    int nb = 0;
    int i = 0;
    int sign = 1;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    } else if (str[0] == '+') {
        i = 1;
    }
    for (; i < my_strlen(str); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            nb = (nb * 10) + (str[i] - '0');
        } else {
            break;
        }
    }
    return nb * sign;
}
