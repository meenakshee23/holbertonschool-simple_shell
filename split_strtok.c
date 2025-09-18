#include <stdio.h>
#include <string.h>
/**
 *
 */
void split_string(char *str)
{
	char *word = strtok(str, " ");
	while (word != NULL)
	{
		printf("%s\n", word);
		word = strtok(NULL, " ");
	}
}
int main()
{
	char str[] = "Hello";

	split_string(str);

	return 0;
}

