#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/**
 * execute_command - forks and executes the command
 * @line: the input command string
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[2];

	pid = fork();

	if (pid == 0)
	{
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

/**
 * main - simple shell that executes a single command
 *
 *  Return: Always 0
 */
int main(void)
{
	int interactive = isatty(STDIN_FILENO);
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		if (interactive)
			printf("simpleshell$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}

		line[nread - 1] = '\0';

		execute_command(line);
	}

	free(line);
	return (0);
}
