#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;
/**
 * main - simple shell
 * Return: 0 success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[2];
	pid_t pid;
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))

		printf("simpleshell$ ");
		fflush(stdout);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("simpleshell");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
