/*
** EPITECH PROJECT, 2025
** Printf
** File description:
** add 0 to the left for int
*/

#include "my.h"

int mini_three(int a, int b, int c)
{
    if (a <= b && a <= c) {
        return a;
    } else if (b <= c) {
        return b;
    } else {
        return c;
    }
}
