#include "../../include/minishell.h"

#include <unistd.h>
#include <dirent.h>
#include <stdio.h>


int ft_heredoc_creation(int *fd, t_lexem *redir);
int	ft_open_redirs(int *fd, t_lexem *redir);
int	ft_prepare_redirections(int *fd_in, int *fd_out, t_lexem *redirs);
char	*ft_path_finder (char *cmd_name);
int ft_pipe(t_single_cmd *head);

int main (void)
{
	t_single_cmd *head;
	t_single_cmd cmd1;
	t_single_cmd cmd2;
//----------CMD 1----------//	
	t_lexem *redirs1;
	t_lexem r1;
//----------CMD 2----------//	
	t_lexem *redirs2;
	t_lexem r2;
//------CMD 1 FILL---------//
	char *cmd1_args[] = {"ls", "-la", NULL};
	r1.str = "r.txt";
	r1.token = OUT_REDIR;
	r1.next = NULL;
	r1.prev = NULL;
	redirs1 = &r1;
	cmd1.str = cmd1_args;
	cmd1.redirection = redirs1;
	cmd1.prev = NULL;
	cmd1.next = &cmd2;
//------CMD 2 FILL---------//
	char *cmd2_args[] = {"wc", NULL};
	r2.str = "r2.txt";
	r2.token = OUT_REDIR;
	r2.prev = &r1;
	r2.next = NULL;
	redirs2 = &r2;
	cmd2.str = cmd2_args;
	cmd2.redirection = redirs2;
	cmd2.prev = NULL;
	cmd2.next = NULL;
	head = &cmd1;
//-------------------------//
	ft_pipe(head);
	return (0);
}

int ft_pipe(t_single_cmd *head)
{
	int fd1[2];
	int pid;
	int fd_in;
	int fd_out;
	
	fd_in = 0;
	fd_out = 1;
	while (head)
	{
		if( -1 == pipe(fd1))
			return(perror("01_Minishell"), EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (perror("02_Minishell"), EXIT_FAILURE);
		if (pid == 0)
		{
			if (EXIT_FAILURE == ft_prepare_redirections(&fd_in, &fd_out, \
				head->redirection))
				return (EXIT_FAILURE);
			close(fd1[0]);
			dup2(fd_in, STDIN_FILENO);
			if (!(head->redirection))
				dup2(fd1[1], STDOUT_FILENO);
			else
				dup2(fd_out, STDOUT_FILENO);
			close(fd1[1]);
			close(fd_out);
			execve(ft_path_finder(head->str[0]), head->str, NULL);
		}
		else
		{
			wait(NULL);
			close(fd1[1]);
			dup2(fd1[0], fd_in);
			close(fd1[0]);
			head = head->next;
		}
	}
	return (EXIT_SUCCESS);
}

char	*ft_path_finder (char *cmd_name)
{
	char	**dirs;
	int		i;
	DIR		*actual;
	struct dirent	*subdir;

	dirs = ft_split(getenv("PATH"), ':');
	i = 0;
	while (dirs && dirs[i])
	{
		actual = opendir(dirs[i]);
		if (actual != NULL)
		{
			subdir = readdir(actual);
			while (subdir)
			{
				if (!ft_strncmp(subdir->d_name, cmd_name, ft_strlen(cmd_name)) \
					&& ft_strlen(subdir->d_name) == ft_strlen(cmd_name))
					return (ft_strjoin(ft_strjoin(dirs[i], "/"), subdir->d_name));
				subdir = readdir(actual);
			}
			closedir(actual);
		}
		free(dirs[i]);
		dirs[i] = NULL;
		i++;
	}
	free(dirs);
	dirs = NULL;
	return (NULL);
}

int	ft_prepare_redirections(int *fd_in, int *fd_out, t_lexem *redirs)
{
	while (redirs)
	{
		print("___ENTRA EN BUCLE PREPARACION___\n");
		if (redirs->token == IN_REDIR || redirs->token >= HERE_DOC)
		{	
			if (*fd_in != 0)
				if (-1 == close(*fd_in));
					return (perror("10_Minishell "), EXIT_FAILURE);
			if (EXIT_FAILURE == ft_open_redirs(fd_in, redirs))
				return (EXIT_FAILURE);
		}	
		else if (redirs->token == OUT_REDIR || redirs->token >= APPEND_REDIR)
		{	
			printf("FD_OUT - %i\n", *fd_out);
			if (*fd_out != 1)
				if (-1 == close(*fd_out))
					return (perror("11_Minishell "), EXIT_FAILURE);
			if (EXIT_FAILURE == ft_open_redirs(fd_out, redirs))
				return (EXIT_FAILURE);
		}
		redirs = redirs->next;	
	}
	return (EXIT_SUCCESS);
}


int	ft_open_redirs(int *fd, t_lexem *redir)
{
	if (redir->token == IN_REDIR)
		*fd = open(redir->str, O_RDONLY);
	if (redir->token == OUT_REDIR)
		*fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (redir->token == APPEND_REDIR)
		*fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, \
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (redir->token >= HERE_DOC)
		*fd = open(redir->str, O_RDONLY);	
	if (*fd < 0 || (*fd == 1 && redir->token >= HERE_DOC))
		return(perror("12_Minishell "), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int ft_heredoc_creation(int *fd, t_lexem *redir)
{
	printf ("HEREDOC\n");
	return (EXIT_FAILURE);
}