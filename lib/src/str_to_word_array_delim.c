/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** str_to_word_array_delim
*/

#include "my.h"

static int count_words_delim(char const *str, char delim)
{
    int count = 0;
    int i = 0;

    while (str[i]) {
        if (str[i] != delim && (i == 0 || str[i - 1] == delim))
            count++;
        i++;
    }
    return count;
}

static int get_word_len_delim(char const *str, char delim)
{
    int len = 0;

    while (str[len] && str[len] != delim)
        len++;
    return len;
}

static void fill_array(char **array, char const *str, char delim)
{
    int i = 0;
    int k = 0;
    int len = 0;

    while (str[i]) {
        while (str[i] && str[i] == delim)
            i++;
        if (!str[i])
            break;
        len = get_word_len_delim(&str[i], delim);
        array[k] = malloc(sizeof(char) * (len + 1));
        my_strncpy(array[k], &str[i], len);
        array[k][len] = '\0';
        i += len;
        k++;
    }
}

char **my_str_to_word_array_delim(char const *str, char delim)
{
    int nb_words = count_words_delim(str, delim);
    char **array = malloc(sizeof(char *) * (nb_words + 1));
    int i = 0;
    int k = 0;
    int len = 0;

    if (!array)
        return NULL;
    fill_array(array, str, delim);
    array[nb_words] = NULL;
    return array;
}
