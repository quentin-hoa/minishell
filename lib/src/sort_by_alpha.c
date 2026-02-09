/*
** EPITECH PROJECT, 2026
** lib
** File description:
** sort_by_apha
*/

#include "my.h"

char *sort_by_alpha(char *str)
{
    char temp;
    int len = my_strlen(str);

    for (int i = 0; i < len; i++) {
        for (int j = 0; str[j] != '\0' && str[j + 1] != '\0'; j++) {
            if (str[j] > str[j + 1]) {
                temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
    return str;
}
