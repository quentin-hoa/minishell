/*
** EPITECH PROJECT, 2025
** Printf
** File description:
** transform an int into a string
*/

#include "my.h"

char *my_decimal(int nb)
{
    char *result = malloc(10);
    char hexa[] = "0123456789";
    int i = 0;
    int nbcopy;

    do {
        nbcopy = nb % 10;
        result[i] = hexa[nbcopy];
        nb /= 10;
        i++;
    } while (nb != 0);
    my_revstr(result);
    result[i] = '\0';
    return result;
}
