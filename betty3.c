#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * write_output - outputs data to a file
 *
 * @str: parameter of type char **.
 *
 * Return: 0 on success negative value with error
 *
*/
int write_output(char **str)
{
	int index = 0;
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters = 0;
	const char *prompt = "Enter some text: ";
	FILE *file = NULL;

	if (str == NULL)
		return (-1);
	while (str[index] != NULL)
	{
		printf("index: %d -> %s\n", index, str[index]);
		index++;
	}
	if (!isatty(STDIN_FILENO))
	{
		characters = getline(&buffer, &bufsize, stdin);
		if (characters <= 0)
			return (-1);
	}
	else
	{
		write(STDOUT_FILENO, prompt, strlen(prompt));
		characters = getline(&buffer, &bufsize, stdin);
		if (characters <= 0)
			return (-1);
	}
	file = fopen("output.txt", "w");
	if (file == NULL)
	{
		printf("Error: failed to open file\n");
		return (-1);
	}
	fprintf(file, "%s\n", buffer);
	fclose(file);
	free(buffer);
	
	return (0);
}

/**
* main - main is the entry point of the program
* @argc: number of arguments passed
* @argv: array of pointers to char **
*
* Return: 0 (success)
*/
int main(int argc, char **argv)
{
	printf("args num: %d\n", argc);
	write_output(argv);
	return (0);
}

