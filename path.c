#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * get_path - create a path to a file
 *
 * @command: parameter of type file *
 *
 * Return: NULL
 *
*/
char *get_path(char *command)
{
	char *path = getenv("PATH");
	char *dir;
	char *path_copy = strdup(path);

	for (dir = strtok(path_copy, ":"); dir; dir = strtok(NULL, ":"))
	{
		char *full_path = malloc(strlen(dir) + strlen(command) + 2);

		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
	}
	free(path_copy);
	return (NULL);
}
/**
* main - main is the entry point of the program
*
* Return: 0 on success
*
*/
int main(void)
{
	char *command = "/bin/ls";
	char *path = get_path(command);

	if (path == NULL)
	{
		printf("Error: %s command not found\n", command);
		exit(EXIT_FAILURE);
	}
	printf("Executing %s\n", path);
	system(path);
	free(path);
	return (0);
}
