#define _GNU_SOURCE
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/**
 * display_prompt - is displayed again each time a command has been executed
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * read_command - reads a line from stdin.
 * Return: Pointer to the input string, or NULL on EOF.
 */
char *read_command(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * execute_command - forks and executes the command using execve
 * @command: the full path to the executable
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[20];

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(command, argv, environ) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * main - main loop of the shell.
 * Return: 0 on success.
 */
int main(void)
{
	int i = 0;

	while (1)
	{
		display_prompt();
		command = read_command();

		if (command == NULL)  /* Handle Ctrl+D */
			break;

		if (strlen(command) > 0)
			execute_command(command);

		free(command);
	}

	return (0);
}
