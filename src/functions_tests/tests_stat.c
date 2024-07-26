#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main (void)
{
	struct stat statbuf;
	char *path = "/home/pabad-ap/minishell42/colors.txt";
	int status;

	status = stat(path, &statbuf);
	return (0);
}