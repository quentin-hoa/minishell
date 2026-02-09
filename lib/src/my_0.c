/*
** EPITECH PROJECT, 2025
** Printf
** File description:
** add 0 to the left for int
*/

#include "my.h"

int my_flag_0(int min, int nb, char *(*fnt_ptr)(int nb))
{
    char *number = fnt_ptr(nb);
    int lenght = my_strlen(number);
    int number_of_0 = min - lenght;
    char *result = malloc(min + lenght + 1);

    for (int i = 0; i < number_of_0; i++) {
        result[i] = '0';
    }
    return my_s(my_strcat(result, number));
}
