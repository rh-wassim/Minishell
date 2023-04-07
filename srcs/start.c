#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    int status;

    while(1) {
        printf("myshell$ ");
        fflush(stdout);
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Remove the newline character from the end of the input
        input[strlen(input) - 1] = '\0';

        // Parse the input into arguments
        char *arg = strtok(input, " ");
        int i = 0;
        while (arg != NULL && i < MAX_ARGS - 1) {
            args[i++] = arg;
            arg = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Check for built-in commands
        if (strcmp(args[0], "exit") == 0) {
            break;
        } else if (strcmp(args[0], "cd") == 0) {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
            continue;
        }

        // Fork a new process to execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            perror(args[0]);
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}