#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int					i = 0;

void	signal_handler(int signum)
{
	printf("SEÑAL Nº%i RECIBIDA\n", signum);
}

void	signal_handler2(int signum)
{
	printf("Nº%i SEÑAL RECIBIDA\n", signum);
}


int main (void)
{
	struct sigaction	sa;
	struct sigaction	sa2;
	struct sigaction	sa3;
	struct sigaction	sa4;

	sa.sa_handler = SIG_IGN;	
	sa2.sa_handler = SIG_DFL;
	sa3.sa_handler = &signal_handler;
	sa4.sa_handler = &signal_handler2;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa2, NULL);
	sigaction(SIGCHLD, &sa4, NULL);
	sigaction(SIGCHLD, &sa3, NULL);
	
	//signal(SIGINT, signal_handler);
	while (1)
	{
		continue;
	}

	return (0);
}