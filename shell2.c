#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
/**
 * main - The main function for the simple shell
 * @argc: The argument count
 * @argv: The argument values
 * @env: The environment variables
 * Return: 0 on success, otherwise the status of the last executed command
 */
#define MAX_ARGS 64
#define MAX_COMMAND_LENGTH 1024

int main(int argc, char *argv[], char *env[])
{
    char input[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    int status;

    while (1) {
        printf("shell> ");
        fflush(stdout);

        fgets(input, MAX_COMMAND_LENGTH, stdin);
        input[strlen(input) - 1] = '\0'; /** remove newline character*/

 /**parse input into separate arguments*/
	char *token = strtok(input, " ");
	int i = 0;

	while (token != NULL && i < MAX_ARGS - 1)
{
	args[i++] = token;
	token = strtok(NULL, " ");
}
	args[i] = NULL;
	
	if (args[0] == NULL)
{
	continue; /** empty command, prompt again*/
}
	if (strcmp(args[0], "exit") == 0)
{
	return 0; /** exit command, terminate shell*/
}
	pid_t pid = fork();
	
	if (pid == 0)
{ /**child process*/
	execvp(args[0], args);
	perror("execvp failed");
	exit(1);
}
	else if (pid > 0)
{ /** parent process*/
	waitpid(pid, &status, 0);
}
	else
{ /**error*/
	perror("fork failed");
	exit(1);
}
}
	return status;
}
/**
 * execute_input_file - Execute commands from an input file
 * @file: The path to the input file
 * @env: Null-terminated array of environment variables
 *
 * Return: 0 on success, 1 on error
 */
/**Execute commands from an input file*/
int execute_input_file(const char *file, char *env[])
{
	FILE *fp = fopen(file, "r");
	if (fp == NULL)
	{
		perror("Error opening file");
		return 1;
	}
	
	while (getline(input, MAX_COMMAND_LENGTH, fp) != NULL)
	{
		input[strlen(input) - 1] = '\0'; /**remove newline character*/

/**parse input into separate arguments*/
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue; /**empty command, skip to next line*/
        }

        pid_t pid = fork();

        if (pid == 0) { // child process
            execvp(args[0], args);
            perror("execvp failed");
            exit(1);
        } else if (pid > 0) { // parent process
            waitpid(pid, &status, 0);
        } else { // error
            perror("fork failed");
            return 1;
        }
    }

    fclose(fp);
    return status;
}
/**
 * read_line - Read a line from standard input
 *
 * Return: A pointer to the read line on success, NULL on error or end of file
 */
// Read a line from standard input
#include <stdio.h>
#include <stdlib.h>

char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        // getline failed, either due to error or end of file
        free(line);
        return NULL;
    }

    return line;
}

