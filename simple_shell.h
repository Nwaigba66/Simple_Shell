#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Function Prototypes */
ssize_t _getline(char **lineptr, size_t *n);
void print_error(char *argv0, char *input, char *err);
void free_tokens(char **tokens);
size_t token_count(const char *str, const char *delim);
int shell_loop(char *argv0);
char **parse_input(char *input);
int execute_command(char *argv0, char **args);
int exit_shell(char *argv0, char **args);
int print_env(char *argv0, char **args);
int set_env_var(char *argv0, char **args);
int unset_env_var(char *argv0, char **args);
int change_directory(char *argv0, char **args);


#endif 
