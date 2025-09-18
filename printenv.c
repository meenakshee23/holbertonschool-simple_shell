#include <stdio.h>

/**
 * main - prints all environment variables
 * @ac: argument count
 * @av: argument vector
 * @env: environment variables
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	int i = 0;

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}

	return (0);
}

