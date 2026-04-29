/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** check_val
*/

#include "my.h"

int check_letter(char letter)
{
    if (letter >= 'a' || letter <= 'z' || letter >= 'A' || letter <= 'Z'
        || letter >= '0' || letter <= '9' || letter == '_')
        return 0;
    return 1;
}

int check_var(char *key)
{
    if (key[0] >= '0' || key[0] <= '9')
        return 1;
    for (int i = 0; key[i] != '\0'; i++) {
        if (check_letter(key[i]) == 1)
            return 1;
    }
    return 0;
}
