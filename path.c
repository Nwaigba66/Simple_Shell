#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* main - main is the entry point of the program
*
* Return: 0 on success
*/
int main(void)
{
	char *path = "/bin/ls";
	char *args[] = { path, "/var", NULL };
	int i;

	i = 0;

/**Execute /bin/ls*/
	
	system(path);
	printf("\n");
/**Execute /bin/ls 3 times*/
	for (i = 0; i < 3; i++)
	{
		system(path);
		printf("\n");
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
	path = "./hbtn_ls";
	execv(path, args);
	return (0);
}

