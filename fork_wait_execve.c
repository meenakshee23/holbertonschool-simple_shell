#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - executes 'ls -l /tmp' in 5 separate child processes
 *
 * Return: Always 0
 */
int main(void)
{
	pid_t pid;
	int i, status;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

	for (i = 0; i < 5; i++)
	{
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			return (1);
		}

		if (pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	return (0);
}
