/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mng_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:22:51 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:22:55 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int			ft_close_unused_pipes(t_single_cmd *current_cmd, int *en);
static t_single_cmd	*ft_head_cmd(t_single_cmd *curr_cmd);

/** Establece las configuraciones de lectura y escritura en los pipes
 * que correponden al comando pasado como parametro.
 * 
 * @param current_cmd Punteor al comando a tratar.
 * @param std_out Referencia al STDOUT principal para recuperarlo
 * en caso de necesidad.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 * 
 * @return Resultado de la ejecución e impresión de errores sin procede.
*/
int	ft_set_pipes(t_single_cmd *current_cmd, int std_out, int *err_n)
{
	if (EXIT_FAILURE == ft_close_unused_pipes(current_cmd, err_n))
		return (EXIT_FAILURE);
	if (current_cmd->prev)
	{
		if (-1 == dup2(current_cmd->prev->pipe_fd[0], STDIN_FILENO))
			return (perror("-minishell "), *err_n = errno, EXIT_FAILURE);
		close(current_cmd->prev->pipe_fd[0]);
	}
	if (current_cmd->next)
	{
		if (-1 == dup2(current_cmd->pipe_fd[1], STDOUT_FILENO))
			return (perror("-minishell "), *err_n = errno, EXIT_FAILURE);
		close(current_cmd->pipe_fd[1]);
	}
	else
	{
		if (-1 == dup2(std_out, STDOUT_FILENO))
			return (perror("-minishell "), *err_n = errno, EXIT_FAILURE);
	}
	close(std_out);
	return (EXIT_SUCCESS);
}

/** Cierra los pipes de lectura del comando actual en adelante y los de
 * escritura a partir del siguiente comando (Se lee del pipe del comando 
 * anterior y se escribe en pipe del comando actual).
 * 
 * @param current_cmd Comando a tratar.
 * @param en Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 * 
 * @return Resultado de la ejecución e impresión de errores sin procede.
 */
static int	ft_close_unused_pipes(t_single_cmd *current_cmd, int *en)
{
	t_single_cmd	*tmp;

	tmp = ft_head_cmd(current_cmd);
	while (tmp->next)
	{
		if (tmp != current_cmd->prev)
			if (-1 == close(tmp->pipe_fd[0]))
				return (perror("-minishell "), \
					*en = errno, EXIT_FAILURE);
		if (tmp != current_cmd)
			if (-1 == close(tmp->pipe_fd[1]))
				return (perror("-minishell "), \
					*en = errno, EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/** Funcion que devuelve el primer elemento de una lista de 
 * estructuras t_single_cmd.
 * @param curr_cmd cmd actual.
 * 
 * @return Primer elemento de la lista.
 */

static t_single_cmd	*ft_head_cmd(t_single_cmd *curr_cmd)
{
	while (curr_cmd->prev)
		curr_cmd = curr_cmd->prev;
	return (curr_cmd);
}
