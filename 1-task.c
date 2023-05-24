#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

int main(void) {
    char *buffer;
    size_t bufsize = BUFFER_SIZE;
    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL) {
        perror("Unable to allocate buffer");
        exit(1);
    }

    while (1) {
        printf(PROMPT);
        if (getline(&buffer, &bufsize, stdin) == -1) {
            printf("\n");
            break;
        }

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid < 0) {
            perror("Unable to fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            if (execlp(buffer, buffer, NULL) == -1) {
                printf("%s: No such file or directory\n", buffer);
                exit(1);
            }
        } else {
            // Parent process
            wait(NULL);
        }
    }

    free(buffer);
    return 0;
}

