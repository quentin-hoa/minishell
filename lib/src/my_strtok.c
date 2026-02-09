/*
** EPITECH PROJECT, 2025
** My_radar
** File description:
** my_strtok
*/

#include "my.h"

static int is_delimiter(char c, const char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i]) {
            return 1;
        }
    }
    return 0;
}

static char *find_token_end(char *str, const char *delim)
{
    while (*str != '\0' && !is_delimiter(*str, delim))
        str++;
    return (str);
}

char *my_strtok(char *str, const char *delim)
{
    static char *last_token = NULL;
    char *token_start = NULL;

    if (str != NULL)
        last_token = str;
    else if (last_token == NULL)
        return NULL;
    while (*last_token != '\0' && is_delimiter(*last_token, delim))
        last_token++;
    if (*last_token == '\0') {
        last_token = NULL;
        return NULL;
    }
    token_start = last_token;
    last_token = find_token_end(last_token, delim);
    if (*last_token != '\0') {
        *last_token = '\0';
        last_token++;
    } else
        last_token = NULL;
    return token_start;
}
