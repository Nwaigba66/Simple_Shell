#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[], char *envp[])
{
    char command[100];
    char *path;
    char *args[2];

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        // Remove the newline character from the end of the command
        command[strcspn(command, "\n")] = '\0';

        // Look for the command in the current directory
        path = command;
        args[0] = path;
        args[1] = NULL;

        if (access(path, X_OK) != 0) {
            printf("%s: %s\n", path, strerror(errno));
            continue;
        }

        // Execute the command
        if (fork() == 0) {
            execve(path, args, envp);
            printf("%s: %s\n", path, strerror(errno));
            exit(1);
        }
        else {
            wait(NULL);
        }
    }

    return 0;
}

