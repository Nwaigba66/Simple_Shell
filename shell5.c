#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "simple_shell.h"
extern char **environ;

#define BUFFER_SIZE 1024
#define MAX_ARGUMENTS 64

/**
* read_line - gets input
*
*
* Return: string of characters inputted
*/
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    getline(&line, &bufsize, stdin);
    return (line);
}

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

/**
* main - main is the entry point of the program
*
* Return: 0 (success)
*/
int main(void)
{
    char *command = NULL;
    char *arguments[MAX_ARGUMENTS];
    char *path = NULL;
    pid_t pid;
    int status;
    char *token;
    int i = 0;

    while (1)
    {
        printf("simple_shell$ ");
        command = read_line();

        /* If user presses Ctrl+D, exit the shell */
        if (!command)
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }

        if (strcmp(command, "env") == 0)
        {
            char **env = environ;
            for (; *env != NULL; env++)
            {
                printf("%s\n", *env);
            }
            continue;
        }

        /* Parse command and arguments */
        token = strtok(command, " ");
        i = 0;
        while (token != NULL && i < MAX_ARGUMENTS)
        {
            arguments[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        arguments[i] = NULL;

        /* Search for command in PATH */
        path = get_path(arguments[0]);
        if (path == NULL)
        {
            printf("simple_shell: command not found: %s\n", arguments[0]);
            continue;
        }

        pid = fork();

        if (pid == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */
            if (execve(path, arguments, environ) == -1)
            {
                perror("execve() error");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, WUNTRACED);
        }

        free(path);
        free(command);
    }
    return (EXIT_SUCCESS);
}
