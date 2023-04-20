#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "simple_shell.h"

#define MAX_INPUT 1024

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

int main(void)
{
	printf("Enter a line of text: ");
	char *input = read_line();

	printf("You entered: %s", input);
	free(input);
	return (0);
}
/**
* split_line - the function name
* @line: parameter of type char *.
* Return: char **.
*/

#define MAX_TOKENS 100
#define DELIMITER " \t\r\n\a"

char **split_line(char *line)
{
	int bufsize = MAX_TOKENS, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
	fprintf(stderr, "split_line: allocation error\n");
	exit(EXIT_FAILURE);
	}
	token = strtok(line, DELIMITER);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
	if (position >= bufsize)
		bufsize += MAX_TOKENS;
	tokens = realloc(tokens, bufsize * sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "split_line: allocation error\n");
		exit(EXIT_FAILURE);
	}
	}
	token = strtok(NULL, DELIMITER);
	}
	tokens[position] = NULL;
	return (tokens);
	}
/**
* main - The entry point of the program
*
* Return: 0 (success)
*/
int main(void)
{
	printf("Enter a line of text: ");
	fgets(line, sizeof(line), stdin);
	tokens = split_line(line);
	for (i = 0; tokens[i] != NULL; i++)
	{
		printf("%s\n", tokens[i]);
	}
	free(tokens);
	return (0);
}


