/*
** EPITECH PROJECT, 2026
** minishell_1
** File description:
** word_separator_space
*/

#include "my.h"


int is_separator(char c)
{
    if (c == ' ' || c == '\t')
        return 1;
    return 0;
}

static void while_loop(int *count, int *in_word, const char *str, int i)
{
    if (is_separator(str[i]) == 0 && *in_word == 0) {
        (*count)++;
        *in_word = 1;
    } else if (is_separator(str[i]) == 1){
        *in_word = 0;
    }
}

static int count_words(char *str)
{
    int count = 0;
    int in_word = 0;
    int i = 0;

    while (str[i] != '\0') {
        while_loop(&count, &in_word, str, i);
        i++;
    }
    return count;
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

static int get_word_len(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0' && is_separator(str[i]) == 0; i++) {
        count++;
    }
    return count;
}

static void more_20_lines(char **word_array, char *str)
{
    int word_index = 0;
    int word_len = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        while (str[i] != '\0' && is_separator(str[i]) == 1) {
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

char **word_separator_space(char *str)
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
