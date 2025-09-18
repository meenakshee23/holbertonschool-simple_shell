#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *line = NULL;
	size_t len = 0;

	 printf("$ ");
	 if (getline(&line, &len, stdin) != -1)
		 printf("%s", line);

	 free(line);
	 return 0;
}

