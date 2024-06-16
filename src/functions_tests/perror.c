#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;

    fd = open("does_not_exist", O_RDONLY);
    if (fd == -1)
    {
        perror("open: malloc error");
        return (1);
    }
    close(fd);
    return (0);
}