#define _GNU_SOURCE
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
	ssize_t read;
	pid_t pid;
	int status;
	int interactive = isatty(STDIN_FILENO);
	char *argv[64];
	int argc;
	int i;
	char *token;

	while (1)
	{
		if (interactive)
		{
			printf("simpleshell$ ");
		}

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (interactive)
				printf("simpleshell$\n");
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0')
			continue;

		argc = 0;
		token = strtok(line, " ");

		while (token != NULL && argc < 63)
		{
			argv[argc] = token;
			token = strtok(NULL, " ");
			argc++;
		}

		argv[argc] = NULL;
		if (argc == 0)
			continue;

		if (strcmp(argv[0], "exit") == 0)
			break;
		if (strcmp(argv[0], "env") == 0)
		{
			for (i = 0; environ[i] != NULL; i++)
				printf("%s\n", environ[i]);
			continue;
		}
		if (argv[0][0] != '/' && !(argv[0][0] == '.' && argv[0][1] == '/'))
		{
			printf("Command not found\n");
			continue;
        }
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
				printf("Command not found\n");
				exit(EXIT_FAILURE);
			}
        }
		else
        {
			waitpid(pid, &status, 0);
		}
    }
	free(line);
	return (0);
}
