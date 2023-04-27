#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/**
* main - Entry point of the program
*
* Return: Exit on success
*/
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *args[2];

	while (1)
{
	printf("$ ");
	nread = getline(&line, &len, stdin);

	if (nread == -1)
{
/**End of file (Ctrl+D)*/
	break;
	}
/**Replace the newline character with a null character*/
	line[nread - 1] = '\0';

/**Set up the arguments for the command*/
	args[0] = line;
	args[1] = NULL;

/**Execute the command*/
	if (fork() == 0)
{
		execve(args[0], args, NULL);
/**If we get here, execve failed*/
		perror("execve");
		exit(EXIT_FAILURE);
		}
	else
{
		wait(NULL);
		}
	}
	free(line);
	exit(EXIT_SUCCESS);
}

