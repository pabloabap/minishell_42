//CABECERA

#include "../../include/minishell.h"

static char	*ft_path_finder (char *cmd_name);
int ft_executor(t_single_cmd *head, char **envp)
{
	int fd1[2];
	int pid;
	//int wstatus;
	
	while (head)
	{
		if( -1 == pipe(fd1))
			return(perror("01_Minishell"), EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (perror("02_Minishell"), EXIT_FAILURE);
		if (pid == 0)
		{
			
			close(fd1[1]);
			dup2(fd1[0], STDIN_FILENO);
			close(fd1[0]);
			if (EXIT_FAILURE == ft_prepare_redirections(head->redirection))
				return (EXIT_FAILURE);
			if (execve(ft_path_finder(head->str[0]), head->str, envp) < 0)
				perror("Minishell ");
		}
		else	
		{
			int i = 0;
			while (head->str[i])
			{
				write(fd1[1], head->str[i], ft_strlen(head->str[i]));
				i++;
			}
			close(fd1[1]);
			close(fd1[0]);
			wait(NULL);
		}
		head = head->next;
	}
	return (EXIT_SUCCESS);	
}

static char	*ft_path_finder (char *cmd_name)
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

