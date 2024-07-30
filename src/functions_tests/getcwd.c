#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char *buff;

	buff = getcwd(NULL, 0);
	
	
	printf("%s\n", buff);
	return (0);
}

