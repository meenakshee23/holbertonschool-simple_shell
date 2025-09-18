#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
/**
 * display_prompt - prints the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#myshell$", 9);
}
/**
 * read_command - reads a command line from stdin
 * Return: pointer to the input string, or NULL on EOF
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
 * execute_command - executes the command if valid
 * @command: full path to the executable
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return;
	}

	if (pid == 0)
	{
		execve(command, argv, NULL);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * main - simple shell loop
 * Return: 0 on success
 */
int main(void)
{
	char *command;

	while (1)
	{
		display_prompt();

		command = read_command();

		if (command == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (strlen(command) > 0)
			execute_command(command);

		free(command);
	}

	return (0);
}
