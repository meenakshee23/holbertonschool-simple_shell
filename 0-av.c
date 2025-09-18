#include <stdio.h>
/**
 * main - prints all command line args
 * @ac: argument count unused
 * @av: argument vector array of strings
 *
 * Return: always 0 success
 */
int main(int ac, char **av)
{
	(void)ac;

	while (*av)
	{
		printf("%s\n", *av);
		av++;
	}

	return (0);
}



