#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "simple_shell.h"

#define BUFFER_SIZE 1024

/**
* read_line - gets input
*
*
* Return: string of characters inputed
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
	int bufsize = 64, position = 0;
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
		bufsize += 64;
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
	(
	return (tokens)
	);
	}
/**
* main - main is the entry point of the program
*
* Return: 0 (success)
*/
int main(void)
{
	printf("Enter a line of text: ");
	printf("You entered: %s", input);
	free(input);
	return (0);

	printf("Enter a line of text: ");
	getline(line, sizeof(line), stdin);
	tokens = split_line(line);
	for (i = 0; tokens[i] != NULL; i++)
	{
		printf("%s\n", tokens[i]);
	}
	free(tokens);
	return (0);
/*Handle command lines with arguments**/
	while (1)
	{
		printf("simple_shell$ ");
		getline(command, Max_length, stdin);
/*If user presses Ctrl+D, exit the shell*/
	command[strcspn(command, "\n")] = '\0';
	if (strcmp(command, "exit") == 0)
	{
	exit(0);
	}
	if (strcmp(command, "env") == 0)
	{
	for (char **env = environ; *env != NULL; env++)
/*Handle end of file condition*/
	{
	printf("%s\n", *env);
	}
	continue;
	}
	input[strcspn(input, "\n")] = '\0';/*Remove trailing newline character*/
/*Parse command and arguments*/
	command = strtok(input, " ");
	int i = 0;

	while (command != NULL && i < MAX_ARGUMENTS)
	{
	arguments[i] = command;
	i++;
	command = strtok(NULL, " ");
	}
	arguments[i] = NULL;
/*Set last argument to NULL for use in exec*/

/*Search for command in PATH*/
	path = get_path(arguments[0]);
	if (path == NULL)
	{
		printf("simple_shell: command not found: %s\n", arguments[0]);
	continue;
	}
	pid = fork();

	if (pid  == -1)
	{
	perror("fork() error");
	exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
/*Child process*/
	execvp(arguments[0], argv);
	perror("execvp() error");
	exit(EXIT_FAILURE);
	}
	else
	{
/*Parent process*/
	waitpid(pid, &status, 0);
	}
	free(path);
	}
	return (0);
}
