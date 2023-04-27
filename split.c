#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "simple_shell.h"
extern char **environ;

#define BUFFER_SIZE 1024
#define MAX_ARGUMENTS 64
/**
* split_line - the function name to split line
* @line: parameter of type char *.
* Return: char **.
*/
char **split_line(char *line)
{
        int bufsize = MAX_ARGUMENTS, position = 0;
        char **tokens = malloc(bufsize * sizeof(char *));
        char *token;

        if (!tokens)
        {
                fprintf(stderr, "split_line: allocation error\n");
                exit(EXIT_FAILURE);
        }
        token = strtok(line, " \t\n\r\a");
        while (token != NULL)
        {
        tokens[position] = token;
        position++;
        if (position >= bufsize)
        {
                bufsize += MAX_ARGUMENTS;
                tokens = realloc(tokens, bufsize * sizeof(char *));
                if (!tokens)
                {
                fprintf(stderr, "split_line: allocation error\n");
                exit(EXIT_FAILURE);
                }
        }
        token = strtok(NULL, " \t\n\r\a");
        }
        tokens[position] = NULL;
        return (tokens);
}
