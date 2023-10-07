#ifndef _SHELLH_
#define _SHELLH_

#define _GNU_SOURCE

/* Standard library headers. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Custom header files. */
#include "history.h"
#include "shellvars.h"

/*
 * Function declarations.
 */

/* from interactive.c */
int is_interactive_mode(void);

/* from print_env.c */
int print_environment(void);

/* from execute_cmd.c */
int execute_builtin(char *av[]);
int execute_command(char *av[], char *path);

/* from parser.c */
int parse_arguments(char **buf);

/* from error_handl.c */
int handle_error(int status);

/* from string.c */
size_t string_length(char *str);
char *copy_string(char *dest, char *src);
int compare_strings(char *str1, char *str2);
char *duplicate_string(char *str);
char *concatenate_strings(char *a, char *b);

/* from get_env.c and get_env_var.c */
char ***get_environment(void);
int set_all_environment_variables(char **environ, char *add);
char *get_environment_variable(char *avzero);
int set_environment_variable(char *name, char *val);
int unset_environment_variable(char *name);
char **get_all_environment_variables(void);

/* from utility.c */
char *convert_integer_to_string(int digits);
char *find_character(char *s, char c);
int print_strings_to_file_descriptor(int fd, char *str, ...);
int print_error(char *message);
int count_lines_in_file(int fd);

/* from change_d.c */
int change_directory(char *av[]);

/* from alias.c */
int execute_alias(char **av);
char *get_alias(char *name);
int unset_alias(char *name);

/* from shell_var.c */
int initialize_shell_variables(int ac, char **av);
char *get_shell_variable(char *name);
int set_shell_variable(char *name, char *val);
int unset_shell_variable(char *name);
ShellVar **get_special_shell_variables(void);
ShellVar **get_all_shell_variables(void);

/* from realloc.c */
void *realloc_memory(void *ptr, unsigned int old_size, unsigned int new_size);

/* from split_str.c */
char *split_string(char *str, char *delim);

/* from get_line.c */
int get_line(char **lineptr, int fd);

char *split_string_quoted(char *str, char *delim, int escflags);

/* from s_p_e_history.c */
int set_history_entry(char *cmd);
int print_history(void);
int exit_history(void);

/* from _printenv.c */
int print_environment(void);
int put_character(char c);

/* from help.c */
int help(char *cmd);

/* from exit_clean_up.c */
void exit_cleanup(char **av);

/* from convert_s_to_i */
int convert_string_to_integer(char *s);

char *get_process_id(void);

#endif
