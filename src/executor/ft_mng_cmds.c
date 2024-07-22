//CABECERA

#include "../../include/minishell.h"

static int	ft_close_unused_pipes(t_single_cmd *current_cmd);

/** Establece las configuraciones de lectura y escritura en los pipes
 * que correponden al comando pasado como parametro.
 * 
 * @param current_cmd Punteor al comando a tratar.
 * @param main_out Referencia al STDOUT principal para recuperarlo
 * en caso de necesidad.
 * 
 * @return Resultado de la ejecución e impresión de errores sin procede.
*/
int	ft_set_pipes(t_single_cmd *current_cmd, int main_out)
{
	if (EXIT_FAILURE == ft_close_unused_pipes(current_cmd))
		return (EXIT_FAILURE);
	if (current_cmd->prev)
	{
		if (-1 == dup2(current_cmd->prev->pipe_fd[0], STDIN_FILENO))
			return (perror("1_SET_Minishell "), EXIT_FAILURE);
		close(current_cmd->prev->pipe_fd[0]);
	}
	if (current_cmd->next)
	{
		if (-1 == dup2(current_cmd->pipe_fd[1], STDOUT_FILENO))
			return (perror("2_SET_Minishell "), EXIT_FAILURE);
		close(current_cmd->pipe_fd[1]);
	}
	else
	{
		if (-1 == dup2(main_out, STDOUT_FILENO))
			return (perror("3_SET_Minishell "), EXIT_FAILURE);
		close(main_out);
	}
	return (EXIT_SUCCESS);
}

/** Cierra lo pipes de lectura del comando actual en adelante y los de
 * escritura a partir del siguiente comando (Se lee del pipe del comando 
 * anterior y se escribe en pipe del comando actual).
 * 
 * @param current_cmd Comando a tratar.
 * 
 * @return Resultado de la ejecución e impresión de errores sin procede. * 
 */
static int	ft_close_unused_pipes(t_single_cmd *current_cmd)
{
	t_single_cmd	*tmp;

	tmp = current_cmd;
	while (tmp->next)
	{
		if (tmp != current_cmd->prev)
			if (-1 == close(tmp->pipe_fd[0]))
				return (perror("1_CLOSE_UNUS_Minishell "), EXIT_FAILURE);
		if (tmp != current_cmd)
			if (-1 == close(tmp->pipe_fd[1]))
				return (perror("2_CLOSE_UNUS_Minishell "), EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
