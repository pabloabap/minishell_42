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

/** Cierra fd y actualiza err_n si hay error en el cierre*/

int	ft_close(int fd, int *err_n)
{
	if (-1 == close(fd))
		return (*err_n = errno, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Gestion de la salida del proceso padre tras haber esperado a que todos
 * los procesos hijos terminen.
 * 
 * @param wstatus Información de los estados y el tipo de salida de los
 * procesos hijo.
 * 
 * @param err_n Puntero a entero que almacena el número del último error de
 * salida.
 * 
 * @return Resultado de ejecución de la función.
 */
int	ft_parent_exit(int wstatus, int *err_n)
{
	wait_signal(1);
	if (WIFSIGNALED(wstatus))
		return (*err_n = 128 + WTERMSIG(wstatus), EXIT_FAILURE);
	else if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
		return (*err_n = WEXITSTATUS(wstatus), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
