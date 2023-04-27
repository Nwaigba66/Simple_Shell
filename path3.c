#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - Entry point of the program
 *
 *get_path - creates a path to a file
 *
 * @command: parameter of type file *
 *
 * Return: NULL
 *
 */
char *get_path(char *command);

int main(void)
{
	char *command = "ls";
	char *path = get_path(command);
	int i;
	char *args[] = { "./hbtn_ls", "/var", NULL };

	i = 0;
	if (path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", command);
		return (1);
	}
/**Execute /bin/ls*/

	system(path);
/**Execute /bin/ls 3 times*/
	for (i = 0; i < 3; i++)
	{
		system(path);
	}
/**Execute /bin/ls 4 times (surrounded by spaces)*/
	for (i = 0; i < 4; i++)
	{
		printf(" ");
		system(path);
	}
	printf("\n");
/**Copy the file /bin/ls to hbtn_ls (in the current directory)*/
	system("cp /bin/ls ./hbtn_ls");
/**Execute ./hbtn_ls /var*/
	execv(args[0], args);
/**Spaces only (small)*/
	printf(" ");
	system(path);
/**Spaces only (large)*/
	for (i = 0; i < 10; i++)
	{
		printf(" ");
	}
	system(path);
/**Spaces only (medium)*/
	for (i = 0; i < 5; i++)
	{
		printf(" ");
	}
	system(path);
	free(path);
	return (0);
}
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

