#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    char *args[2];
    int status;

    while (1) {
        printf("#cisfun$ ");

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        args[0] = buffer;
        args[1] = NULL;

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execve(args[0], args, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return EXIT_SUCCESS;
}
