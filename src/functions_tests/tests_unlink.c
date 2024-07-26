#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int unlink(const char *path);

int main (void)
{
	char *path = "/home/pabad-ap/minishell42/borrar.txt";
	int fd;
	int fd2;
	char buff[110];

	fd = open(path, O_WRONLY | O_CREAT, S_IRWXU);
	fd2 = open(path, O_RDONLY, S_IRWXU);
	write(fd, "PABLO\n", 6);
	sleep(10);
	write(0, "UNLINK\n", 7);
	unlink(path);
	sleep(10);
	read(fd2, buff, 10);
	write(0, buff, 7);
	close(fd);

	return (0);
}