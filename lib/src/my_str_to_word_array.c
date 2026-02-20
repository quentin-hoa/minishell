/*
** EPITECH PROJECT, 2025
** Day03
** File description:
** Alphabet
*/

#include "my.h"

static int is_alphanum(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9')) {
        return (TRUE);
    }
    return FALSE;
}

static void while_loop(int *count, int *in_word, const char *str, int i)
{
    if (is_alphanum(str[i]) == TRUE && *in_word == FALSE) {
        (*count)++;
        *in_word = TRUE;
    } else if (is_alphanum(str[i]) == FALSE) {
        *in_word = FALSE;
    }
}

static int count_words(char const *str)
{
    int count = 0;
    int in_word = FALSE;
    int i = 0;

    while (str[i] != '\0') {
        while_loop(&count, &in_word, str, i);
        i++;
    }
    return count;
}

static int get_word_len(char const *str)
{
    int len = 0;

    while (str[len] != '\0' && is_alphanum(str[len]) == TRUE) {
        len++;
    }
    return len;
}

static char *duplicate_word(char const *src, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));

    if (word == NULL) {
        return (NULL);
    }
    my_strncpy(word, src, len);
    word[len] = '\0';
    return word;
}

static void more_20_lines(char **word_array, char const *str)
{
    int word_index = 0;
    int word_len = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        while (str[i] != '\0' && is_alphanum(str[i]) == FALSE) {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }
        word_len = get_word_len(&str[i]);
        word_array[word_index] = duplicate_word(&str[i], word_len);
        if (word_array[word_index] == NULL) {
            return;
        }
        word_index++;
        i += word_len - 1;
    }
}

char **my_str_to_word_array(char const *str)
{
    int nb_words;
    char **word_array;
    int word_index = 0;
    int word_len = 0;

    if (str == NULL) {
        return NULL;
    }
    nb_words = count_words(str);
    word_array = malloc(sizeof(char *) * (nb_words + 1));
    if (word_array == NULL) {
        return NULL;
    }
    more_20_lines(word_array, str);
    word_array[nb_words] = NULL;
    return word_array;
}
