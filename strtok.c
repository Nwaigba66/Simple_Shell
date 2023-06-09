#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * _strtok - parse a string
 *
 * @numString: string number
 * @Sep: separators
 * @myPtr: rest of the string
 *
 * Return: first token of the string
 */
char *_strtok(char *numString, const char *Sep, char **myPtr)
{
	char *token;

	if (numString == NULL)
	{
	numString = *myPtr;
	}
	numString += strspn(numString, Sep);
	if (*numString == '\0')
	{
	return (NULL);
	}
	token = numString;
	numString = strpbrk(numString, Sep);
	if (numString != NULL)
	{
	*numString = '\0';
	numString++;
	}
	*myPtr = numString;
	return (token);
}

