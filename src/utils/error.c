// CABECERA

#include "../../include/minishell.h"

void err_red_no_file(void)
{
	ft_putendl_fd("Minishell: Redirections must be followed \
		by a file name or delimiter.", STDERR_FILENO);
}

void err_pipe_start(void)
{
	ft_putendl_fd("Minishell: syntax error near unexpected token '|'", STDERR_FILENO);
}