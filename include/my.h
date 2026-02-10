/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include <stdio.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <termios.h>
    #include <ncurses.h>
    #include <time.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <dirent.h>
    #include <sys/wait.h>
    #include <fcntl.h>

    int my_printf(char *format, ...);
    char **word_separator_space(char const *str);
    char **my_str_to_word_array(char const *str);
    char *my_strncpy(char *dest, char const *src, int nb);
    char *my_strcpy(char *dest, char const *src);
    int my_strncmp(char *s1, char  *s2, int n);
    int my_atoi(char *str);
    int my_strcmp(char *s1, char *s2);
    char *my_strdup(char *str);
    char *get_home_path(char **env);
    int handle_cd_path(char **list_of_args, char **env);
    int execute_command(char **list_of_args, char **env, int *status);
    int my_shell(char *line, char **env, int *last_status);
    int my_strlen(char *str);
    char *my_strcat(char *dest, char const *src);

#endif
