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

void err_red_no_file(void)
{
	ft_putendl_fd("Minishell: Redirection without file or delimiter", \
	STDERR_FILENO);
}

void err_pipe_start(void)
{
	ft_putendl_fd("Minishell: syntax error near unexpected token '|'", STDERR_FILENO);
}

void err_malloc_fail(void)
{
	perror("Minishell: t_lexem malloc fails");
}