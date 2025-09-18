#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/**
 * main - compares the address of env and environ
 * @ac: argument count
 * @av: argument vector
 * @env: environment passed to main
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	printf("Address of env:     %p\n", (void *)env);
	printf("Address of environ: %p\n", (void *)environ);

	return (0);
}
