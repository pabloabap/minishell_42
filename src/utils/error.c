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
	ft_putendl_fd("Minishell: Redirections must be followed \
		by a file name or delimiter.", STDERR_FILENO);
}

void err_pipe_start(void)
{
	ft_putendl_fd("Minishell: syntax error near unexpected token '|'", STDERR_FILENO);
}

void err_malloc_fail(void)
{
	ft_putendl_fd("Minishell: malloc fail. Out of memorry", STDERR_FILENO);
}