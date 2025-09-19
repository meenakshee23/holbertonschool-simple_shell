#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;
/**
 * main- entry point of the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int interactive = isatty(STDIN_FILENO);
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		if (interactive)
			printf("simpleshell");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}

		line[nread - 1] = '\0';

		pid = fork();
		if (pid == 0)
		{
			char *args[2];

			args[0] = line;
			args[1] = NULL;

			if (execve(line, args, environ) == -1)
			{
				printf("Command not found\n");
				exit(1);
			}
		}
		else if (pid > 0)
		{
			wait(&status);
		}
		else
		{
			perror("fork");
			free(line);
			exit(1);
		}
	}

	return (0);
}
