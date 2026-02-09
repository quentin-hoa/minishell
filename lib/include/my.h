/*
** EPITECH PROJECT, 2025
** Day03
** File description:
** Alphabet
*/

#ifndef _MY_H_
    #define _MY_H_
    #define SIZEBUFFER 1000100
    #include <unistd.h>
    #include <stdarg.h>
    #include <stdarg.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #define NUMBER_OF_SP 14
    #define NUMBER_OF_FLAGS 3
    #define FALSE 0
    #define TRUE 1

typedef struct specifier_s {
    char option;
    int (*fonction_pointer)(va_list list);
} specifier_t;
// printf part ---------------------
int my_u_caller(va_list list);
int my_g_caller(va_list list);
int my_s_caller(va_list list);
int my_c_caller(va_list list);
int my_c(char c);
int my_d(int nb);
int my_d_caller(va_list list);
void my_swap(char *a, char *b);
int my_s(char *str);
int my_f(double nb);
int my_f_caller(va_list list);
int my_strlen(char *str);
char *my_strcat(char *dest, char const *src);
int my_e(double nb);
int my_e_caller(va_list list);
int my_ee(double nb);
int my_ee_caller(va_list list);
char *my_revstr(char *str);
int my_xx(int nb);
int my_xx_caller(va_list list);
char *my_xx_char_caller(va_list list);
char *my_xx_char(int nb);
int my_x(int nb);
int my_x_caller(va_list list);
char *my_x_char_caller(va_list list);
char *my_x_char(int nb);
int my_o(int nb);
int my_o_caller(va_list list);
char *my_o_char(int nb);
char *my_o_char_caller(va_list list);
int my_u(unsigned int n);
int my_g(double nb);
int my_plus(int nb);
int my_plus_caller(va_list list);
int my_space(int nb);
int my_space_caller(va_list list);
int my_flag_0(int min, int nb, char *(*fnt_ptr)(int nb));
char *my_decimal(int nb);
int my_p(void *pointeur);
int my_p_caller(va_list list);
int my_b(int nb);
int my_b_caller(va_list list);
int my_w_caller(va_list list);
int my_w(int nb);
int is_apha_char(char c);
int is_number(char c);
int mini_three(int a, int b, int c);
int my_atoi_c(char c);
int my_strcmp(char *s1, char *s2);
char *my_strtok(char *str, const char *delim);
char **my_str_to_word_array(char const *str);
char *my_strncpy(char *dest, char const *src, int nb);
char *my_strcpy(char *dest, char const *src);
char *sort_by_alpha(char *str);
int my_printf(char *format, ...);
char *to_lower(char *str);
//------------------------------------

#endif /* _MY_H_ */
