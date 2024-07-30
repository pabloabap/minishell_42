#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler (int signal)
{
	if (signal == SIGUSR1) //Number of SIGUSR1
		printf("SIGUSR1 received\n");
	else if (signal == SIGUSR2) //Number of SIGUSR2
		printf("SIGUSR2 received\n");
}

int main (void)
{
	printf("%i\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
	{
		continue;
	}

	return (0);
}