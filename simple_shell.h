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
char *read_line(void)
char **split_line(char *line)
int main(void)
char *getline(void)

#endif 
