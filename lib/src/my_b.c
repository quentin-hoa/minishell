/*
** EPITECH PROJECT, 2025
** Printf
** File description:
** add 0 to the left for int
*/

#include "my.h"

int my_b_caller(va_list list)
{
    int nb = va_arg(list, int);

    return my_b(nb);
}

int my_b(int nb)
{
    char hexa[] = "01";
    int nbcopy;
    int count = 0;

    if (nb >= 2)
        count += my_b(nb / 2);
    nbcopy = nb % 2;
    count += my_c(hexa[nbcopy]);
    return count;
}

int my_w_caller(va_list list)
{
    int nb = va_arg(list, int);

    return my_w(nb);
}

int my_w(int nb)
{
    char octo[] = "012345";
    int nbcopy;
    int count = 0;

    if (nb >= 6)
        count += my_w(nb / 6);
    nbcopy = nb % 6;
    count += my_c(octo[nbcopy]);
    return count;
}
