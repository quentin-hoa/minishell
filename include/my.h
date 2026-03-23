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
    #include <errno.h>
    #define NB_BUILTIN 4
    #define TRUE 1
    #define FALSE 0

int my_printf(char *format, ...);
char **word_separator_space(char *str);
char **my_str_to_word_array(char const *str);
char *my_strncpy(char *dest, char const *src, int nb);
char *my_strcpy(char *dest, char const *src);
int my_strncmp(char *s1, char *s2, int n);
int my_atoi(char *str);
int my_strcmp(char *s1, char *s2);
char *my_strdup(char *str);
char *get_home_path(char **env);
int handle_cd_path(char **list_of_args, char ***env);
int execute_command(char **list_of_args, char **env, int *status);
int my_shell(char *line, char ***env, int *last_status);
int my_strlen(char *str);
char *my_strcat(char *dest, char const *src);
int cd_func(char ***env, int *last_status, char **list_of_args, int *status);
void free_list(char **list_of_args);
int is_alpha_char(char c);
int is_number(char c);
void display_env(char **env);
int handle_env(char **env, int *last_status, char **list_of_args);
char **init_new_env(char **env);
int check_var(char *var);
int modif_var(char *var, char **new_env, char *value);
char **handle_unsetenv(char **list_of_args, char **env);
void shift_values(char **env, int j);
int count_lines_env(char **env);
char *get_exe_path(char **env, char *command);
int is_only_space(char *line);
char *my_strndup(char const *src, int n);
char *my_strchr(char const *str, int c);
int find_slash(char *command);
char **my_str_to_word_array_delim(char const *str, char delim);
int my_str_isnum(char *str);

typedef struct env_s {
    char *key;
    char *val;
    struct env_s *next;
    struct env_s *prev;
} env_t;

env_t *init_env_list(char **env);
void print_env(env_t *head);

typedef struct builtin_s {
    char *key;
    int (*func)(env_t **head, char **args, int *last_status);
} builtin_t;

int exit_funct(env_t **head, char **args, int *last_status);
void do_unsetenv(env_t **head, char **args, int *last_status);
int new_shell(char *str, env_t **head, int *last_status);
int make_chdir(char *cd_path);
int new_cd(env_t **head, char **args, int *last_status);
void do_setenv(env_t **head, char **args, int *last_status);
char **list_to_array(env_t *head);
char *get_path(char *command, env_t *head);
void free_env_list(env_t *head);
int check_var(char *key);
//---------------minishell 2 --------------------

typedef enum {
    CMD,
    PIPE,// |
    SEMI_COL, // ;
    REDIR_R,// >
    REDIR_L,// <
    APPEND,// >>
    HEREDOC// <<
} type_t;

typedef struct treenode_s {
    char **args;
    type_t type;
    struct treenode_s *left;
    struct treenode_s *right;
} treenode_t;

treenode_t *build_tree(char *line);
int run_simple_cmd(char **args, env_t **head, int *last_status);
int execute_tree(treenode_t *node, env_t **head, int *last_status);
void free_tree(treenode_t *root);
int shell(char *str, env_t **head, int *last_status);
treenode_t *crea_tree_node(char **args, type_t type);
int execute_pipe(treenode_t *node, env_t **head, int *last_status);
int execute_redir(treenode_t *node, env_t **head, int *last_status);

#endif
