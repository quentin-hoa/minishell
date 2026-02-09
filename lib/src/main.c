/*
** EPITECH PROJECT, 2026
** lib
** File description:
** main
*/

#include "my.h"

int main(int ac, char **av)
{
    my_printf("%s\n%s\n", sort_by_alpha(av[1]), sort_by_alpha(av[2]));
    return 0;
}
