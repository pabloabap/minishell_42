#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv)
{
	if (argc == 2)
		printf("%s", getenv(argv[1]));
	return (0);
}