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
 * trim_spaces - Removes leading and trailing spaces from a string
 * @str: Input string
 * Return: Trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str == ' ')
		str++;

	if (*str == 0)
		return str;

	end = str + strlen(str) - 1;
	while (end > str && *end == ' ')
		end--;

	end[1] = '\0';
	return str;
}

/**
 * main - Simple shell main loop
 * Return: Always 0
 */
int main(void)
{
	int interactive, status, i;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	char *command;
	char *token;
	char *args[64];

	interactive = isatty(STDIN_FILENO);

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
		command = trim_spaces(line);

		if (command[0] == '\0')
			continue;

		i = 0;
		token = strtok(command, " ");
		while (token != NULL && i < 63)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		pid = fork();
		if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
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

	free(line);
	return (0);
}
