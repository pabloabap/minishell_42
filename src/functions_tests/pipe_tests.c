//CABECERA

#include "../../include/minishell.h"


int main (void)
{
	int in_backup;
	int out_backup;
	int	pipes[2];
	int	pipes1[2];
	int pid;

	in_backup = dup(STDIN_FILENO);
	out_backup = dup(STDOUT_FILENO);
	if( -1 == in_backup || -1 == out_backup)
		return(perror("Minishell "), EXIT_FAILURE);
	if(0 > pipe(pipes) || 0 > pipe(pipes1))
		return(perror("Minishell "), EXIT_FAILURE);
	
	pid = fork();
	if (pid == -1)
		return(perror("Minishell "), EXIT_FAILURE);
	else if (pid == 0)
	{
		close(pipes[1]);
		close(pipes1[0]);
		if (-1 == dup2(pipes[0], STDIN_FILENO))
			return (perror("Minishell "), EXIT_FAILURE);
		close(pipes[0]);
		if (-1 == dup2(pipes1[1], STDOUT_FILENO))
			return (perror("Minishell "), EXIT_FAILURE);
		close(pipes1[1]);
		char w[11] = {};
		read(STDIN_FILENO, w, 11);
		write(STDOUT_FILENO, w, 11);
		write(STDOUT_FILENO, "PABLO HOLA", 11);
		write(STDOUT_FILENO, "PABLO AOLA", 11);
		close(STDOUT_FILENO);
		return(0);
	}
	else
	{
		close(pipes[0]);
		close(pipes1[1]);
		if (-1 == dup2(pipes[1], STDIN_FILENO))
			return (perror("Minishell "), EXIT_FAILURE);
		close(pipes[1]);
		write(STDIN_FILENO, "HOLA PABLO\n", 11);
		close(STDIN_FILENO);
		char w[11] = {};
		wait(NULL);
		int p = read(pipes1[0], w, 11);
		while (p > 0)
		{
			write(STDOUT_FILENO, w, 11);
			p = read(pipes1[0], w, 11);
		}
		close(pipes1[0]);
	}
	return(0);
}