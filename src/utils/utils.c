/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:18:47 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/27 23:18:53 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** Cirra fd y actualiza err_n si hay error en el cierre*/

int	ft_close(int fd, int *err_n)
{
	if (-1 == close(fd))
		return (*err_n = errno, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
