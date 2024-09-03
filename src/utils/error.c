/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:24:21 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:24:26 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** Gestion de errores de redirecciones sin fichero */
void	err_red_no_file(void)
{
	ft_putendl_fd("-minishell: syntax error near unexpected token `newline'", \
	STDERR_FILENO);
}

/** Gestion de errores de pipes al comienzo del input */
void	err_pipe_start(void)
{
	ft_putendl_fd("-minishell: syntax error near unexpected token '|'" \
	, STDERR_FILENO);
}

/** Gestion de errores de pipes sin comando a su derecha*/
void	err_pipe(void)
{
	ft_putendl_fd("-minishell: Pipe without command at its right" \
	, STDERR_FILENO);
}

/** Gestion de errores de malloc*/
void	err_malloc_fail(int *err_n)
{
	perror("-minishell: malloc fails");
	if (err_n != NULL)
		*err_n = ENOMEM;
}

/** Gestion del cierre de un HEREDOC por la recepción de una señal de EOF.*/
void	ft_hdoc_close_check(t_lexem *redir, char *line, int *err_n)
{
	int	i;

	i = 0;
	if (line == NULL)
	{
		ft_putstr_fd("-minishell: warning: here-document", STDERR_FILENO);
		ft_putstr_fd(" delimited by end-of-file (wanted ", STDERR_FILENO);
		while (redir->str[i])
			ft_putchar_fd(redir->str[i++], STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
		*err_n = 0;
	}
	free(line);
}
