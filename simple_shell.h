#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv);
int built_exit(void);
char *_strdup(char *str);
int _strlen(char *s);
char **tokenize(char *str, char *delimiter);
char *get_path(char *command);
char **get_all_paths(void);
int execute(char **arguments);
int shell_loop(void);
int main(void);
char *_strtok(char *numString, const char *Sep, char **myPtr);

#endif

