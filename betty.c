#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

int main(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf(PROMPT);
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		/* Remove newline character */
		buffer[strcspn(buffer, "\n")] = '\0';

		pid_t pid = fork();
		if (pid < 0)
		{
			perror("Unable to fork");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execlp(buffer, buffer, NULL) == -1)
			{
				printf("%s: No such file or directory\n", buffer);
				exit(1);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	return 0;
}

