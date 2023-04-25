#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
/**
 * getline - Return command line type by user
 *
 * Return: buffer
 */
char *getline(void)
{ static char buffer[BUFFER_SIZE];
	static int pos = 0;

    
	char c = '\0', *buffer;
	int i = 0, pos, bufferSize = BUFFER_SIZE;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);

	while (c != '\n' && c != EOF)
	{
		pos = read(STDIN_FILENO, &c, 1);

		if (pos == 0)
		{
			c = EOF;
			write(STDIN_FILENO, "\n", 1);
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		if (i >= bufferSize - 1)
		{
			buffer = _realloc(buffer, bufferSize, sizeof(char) * (i + 2));
			bufferSize = i + 2;
		}
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';

	return (buffer);
}
