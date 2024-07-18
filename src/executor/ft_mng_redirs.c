//CABECERA

#include "../../include/minishell.h"

static int	ft_open_redirs(t_lexem *redir);
static int ft_heredoc_creation(t_lexem *redir);
static int ft_dup_manage(int fd, t_lexem *redir);

int	ft_prepare_redirections(t_lexem *redirs)
{

	while (redirs)
	{
		if(EXIT_FAILURE == ft_open_redirs(redirs))
			return (EXIT_FAILURE);
		redirs = redirs->next;	
	}
	return (EXIT_SUCCESS);
}

static int	ft_open_redirs(t_lexem *redir)
{
	int fd;

	if (redir->token == IN_REDIR)
		fd = open(redir->str, O_RDONLY);
	if (redir->token == OUT_REDIR)
		fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (redir->token == APPEND_REDIR)
		fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, \
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (redir->token >= HERE_DOC)
		fd = ft_heredoc_creation(redir);
	if (fd < 0)
		return(perror("12_Minishell "), EXIT_FAILURE);
	else
	{
		if(EXIT_FAILURE == ft_dup_manage(fd, redir))
			return(EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int ft_heredoc_creation(t_lexem *redir)
{
	printf ("HDOC DEL - %s\n", redir->str);
	return (EXIT_FAILURE);
}

static int ft_dup_manage(int fd, t_lexem *redir)
{
	if(redir->token == IN_REDIR || redir->token >= HERE_DOC)
	{
		if (0 > dup2(fd, STDIN_FILENO))
			return(close (fd), perror("13_Minishell "), EXIT_FAILURE);
	}
	else if(redir->token == OUT_REDIR || redir->token >= APPEND_REDIR)
	{
		if (0 > dup2(fd, STDOUT_FILENO))
			return(close (fd), perror("14_Minishell "), EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}