#include <stdio.h>

extern char **environ;

/**
 * main - prints the environment using the global variable 'environ'
 *
 * Return: Always 0
 */
int main(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}
