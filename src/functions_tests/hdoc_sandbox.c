//CABECERA
#include "../../include/minishell.h"
#include <stdio.h>

static int	ft_fill_hdoc(char *line, char *exit);
static int	ft_write_char(char *line, int *i);
static int	ft_write_env_var(char *line, int var_start, char *exit);
static void	error_malloc_fail(void);

int	main(void)
{
	char			*line;
	char			*lst_exit;

	lst_exit = ft_itoa(0);
	line = readline("heredoc> ");
	while (0 != ft_strncmp(line, "EOF", 4))
	{
		ft_fill_hdoc(line, lst_exit);
		write(STDOUT_FILENO, "\n", 1);
		line = readline("heredoc> ");
	}
	free(lst_exit);
	return (0);
}

static int	ft_fill_hdoc(char *line, char *exit)
{
	int		i;

	i = 0;
	ft_write_char(line, &i);
	if (line[i] == '$')
	{
		i ++;
		if (line[i] == '?')
		{
			write(STDOUT_FILENO, exit, ft_strlen(exit));
			line += ++i;
			if (EXIT_FAILURE == ft_fill_hdoc(line, exit))
				return (EXIT_FAILURE);
		}
		else
			if (EXIT_FAILURE == ft_write_env_var(line, i, exit))
				return (free(exit), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_write_char(char *line, int *i)
{
	while (line[*i] && line[*i] != '$')
	{
		if (-1 == write(STDOUT_FILENO, &line[*i], 1))
			return (EXIT_FAILURE);
		*i += 1;
	}
	return (EXIT_SUCCESS);
}

static int	ft_write_env_var(char *line, int var_start, char *exit)
{
	char	*var_name;
	int		var_end;

	var_end = var_start;
	while (ft_isalnum(line[var_end]) || line[var_end] == '_')
		var_end += 1;
	if (var_end > var_start)
	{
		var_name = ft_substr(line, var_start, var_end - var_start);
		if (var_name == NULL)
			return (error_malloc_fail(), EXIT_FAILURE);
		if (getenv(var_name) != NULL)
			ft_putstr_fd(getenv(var_name), STDOUT_FILENO);
		free(var_name);
	}
	else
		write(STDOUT_FILENO, "$", 1);
	if (line[var_end])
	{
		line += var_end;
		if (EXIT_FAILURE == ft_fill_hdoc(line, exit))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	error_malloc_fail(void)
{
	perror("Minishell: malloc fails");
}
