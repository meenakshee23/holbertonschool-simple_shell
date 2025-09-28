#define _GNU_SOURCE
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

extern char **environ;

/**
 * main - simple shell
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	int interactive = isatty(STDIN_FILENO);
	int argc;
	char *argv[64];
	char *token;


	while (1)
	{
		if (interactive)
			printf("simpleshell$ ");
		fflush(stdout);


		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0')
			continue;

		argc = 0;
		token = strtok(line, " ");
		while (token != NULL && argc < 63)
		{
			argv[argc++] = token;
			token = strtok(NULL, " ");
		}
		argv[argc] = NULL;
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				free(line);
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				execve(argv[0], argv, environ);
				perror("simpleshell");
				exit(EXIT_FAILURE);
			}
			else
			{
				wait(&status);
				token = strtok(NULL, " ");
			}
		}
	}
	free(line);
	return (0);
}
