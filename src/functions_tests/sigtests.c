#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler (int signal)
{
	if (signal == SIGQUIT) //Number of SIGUSR1
		printf("SIGQUIT received\n");
	else if (signal == SIGTERM) //Number of SIGUSR1
		printf("SIGTERM received\n");
	else if (signal == SIGQUIT) //Number of SIGUSR1
		printf("SIGQUIT received\n");
	// else if (signal == SIGINT) //Number of SIGUSR2
	// 	printf("SIGINT received\n");
}

int main (void)
{
	printf("%i\n", getpid());
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	//signal(SIGINT, signal_handler);
	while (1)
	{
		continue;
	}

	return (0);
}