#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/**
 * trim_spaces - trim leading and trailing spaces of string
 * @str: input string
 * Return: pointer to trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
	{
		*end = '\0';
		end--;
	}

	return (str);
}

/**
 * main - simple shell
 * Return: 0 on success
 */
int main(void)
{
	int interactive;
	char *line;
	size_t len;
	ssize_t nread;
	pid_t pid;
	int status;
	char *command;
	char *args[64];
	int i;
	char *token;

	interactive = isatty(STDIN_FILENO);
	line = NULL;
	len = 0;

	while (1)
	{
		if (interactive)
			printf("simpleshell$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		line[nread - 1] = '\0';

		command = trim_spaces(line);

		i = 0;
		token = strtok(command, " \t\n");

		while (token != NULL && i < 63)
		{
			args[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		if (command[0] == '\0')
			continue;

		pid = fork();
		if (pid == 0)
		{
			args[0] = command;
			args[1] = NULL;

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
