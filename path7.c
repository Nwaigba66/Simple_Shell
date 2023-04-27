#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_ARGUMENTS 64

/**
 * read_line - reads a line of input from the user
 *
 * Return: pointer to the string read from the user
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	printf("simple_shell$ ");
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
	int bufsize = MAX_ARGUMENTS;
	int position = 0;
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
 * main - entry point of the program
 *
 * Return: always 0 (success)
 */
int main(void)
{
	char *line;
	char **args;
	pid_t pid;
	int status;

	while (1)
	{
	line = read_line();
	if (!line)
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}

/* Remove trailing newline */
	line[strcspn(line, "\n")] = '\0';

/* Parse command line */
	args = split_line(line);

/* Fork a child process */
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
/* Child process */
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
/* Parent process */
	do {
	waitpid(pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
/* Free memory */
	free(line);
	free(args);
	}
	return (0);
}

