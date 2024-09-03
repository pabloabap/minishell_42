/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:22:37 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/26 12:32:51 by anguil-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_prepare_exec(t_single_cmd *head, int *std_out, t_data *data);
static int	ft_child_mng(t_single_cmd *cmd, int std_out, t_data *data);
static int	ft_parent_mng(t_single_cmd *cmd, t_data *data, int std_out);
static int	ft_single_builtin(t_single_cmd *cmd, t_data *data, int std_out);

/** Funcion principal executor. Crea un proceso hijo por comando
 * a ejecutar, configura su entrada, salida y redirecciones y los ejecuta
 * en paralelo.
 * El padre espera la finalizacion de todos los hijos para recoger
 * el exit status final.
 *
 * @param head Puntero al primer comando de la lista de comandos
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 * 
 * @return Resultado de la ejecución.
 */
int	ft_executor(t_single_cmd *head, t_data *data)
{
	int				std_out;
	int				pid;
	t_single_cmd	*tmp;

	tmp = head;
	if (EXIT_FAILURE == ft_prepare_exec(head, &std_out, data))
		return (EXIT_FAILURE);
	while (head)
	{
		pid = fork();
		if (pid == -1)
			return (perror("-minishell"), data->last_exit = errno, \
				EXIT_FAILURE);
		if (pid == 0)
			if (EXIT_FAILURE == ft_child_mng(head, std_out, data))
				return (EXIT_FAILURE);
		head = head->next;
	}
	ft_sleep(2);
	if (EXIT_FAILURE == ft_parent_mng(tmp, data, std_out))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Crea los pipes necesarios en la ejecución (uno menos que el número de
 * comandos).
 *
 * @param head Puntero al primer elemento de la lista de comandos.
 * @param std_out Referencia al STDOUT para que en caso de que tenga que ser
 * modificado por por algún comando intermedio podamos recuperar el principal.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 * 
 * @return Resultado de la ejecución e impresión de error si existe. 
 */
static int	ft_prepare_exec(t_single_cmd *head, int *std_out, t_data *data)
{
	while (head)
	{
		if (head->next)
			if (-1 == pipe(head->pipe_fd))
				return (perror("-minishell "), data->last_exit = errno, \
					EXIT_FAILURE);
		if (EXIT_FAILURE == ft_check_hdoc(head, data))
			return (EXIT_FAILURE);
		head = head->next;
	}
	*std_out = dup(STDOUT_FILENO);
	if (*std_out == -1)
		return (perror("-minishell "), data->last_exit = errno, \
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Gestiona instrucciones para el proceso hijo de un fork.
 *
 * @param cmd Puntero al comando actual a procesar.
*  @param std_out Referencia al STDOUT para que en caso de que tenga que ser 
 * modificado por por algún comando intermedio podamos recuperar el principal.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 *  
 * @return Resultado de ejecición e impresión de errores si procede.
 */
static int	ft_child_mng(t_single_cmd *cmd, int std_out, t_data *data)
{
	if (cmd->str && is_builtin(cmd->str[0]) && !cmd->prev && !cmd->next)
		return (exit(0), EXIT_SUCCESS);
	else if (
		EXIT_FAILURE == ft_set_pipes(cmd, std_out, &(data->last_exit)) || \
		EXIT_FAILURE == ft_prepare_redirections(cmd, &(data->last_exit)) || \
		!cmd->str || \
		EXIT_FAILURE == ft_path_finder(cmd, data))
		return (exit(data->last_exit), EXIT_FAILURE);
	else if (is_builtin(cmd->str[0]) && (cmd->next || cmd->prev))
	{
		execute_builtin(cmd->str, data->env, &(data->last_exit));
		exit(data->last_exit);
	}
	else if (execve(cmd->cmd_path, cmd->str, data->env->envp_cpy) < 0)
	{
		if (access(cmd->cmd_path, F_OK) < 0)
			return (perror("-minishell "), exit(127), EXIT_FAILURE);
		else if (access(cmd->cmd_path, X_OK) < 0)
			return (perror("-minishell "), exit(126), EXIT_FAILURE);
		return (perror("-minishell "), exit(errno), EXIT_FAILURE);
	}
	return (exit(0), EXIT_SUCCESS);
}

/** Gestiona instrucciones para el proceso padre en un fork.
 * Cierra todos los pipes ya que no son utilizados en el padre.
 * Espera a que los procesos hijos terminen y comprueba el exit status
 * para actualizarlo si es necesario.
 *
 * @param cmd Doble puntero al comando actual a procesar.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 * @param std_out Referencia al STDOUT para que en caso de que tenga que ser 
 * modificado por por algún comando intermedio podamos recuperar el principal.
 * 
 * @return Resultado de ejecición e impresión de errores si procede. 
 */
static int	ft_parent_mng(t_single_cmd *cmd, t_data *data, int std_out)
{
	t_single_cmd	*tmp;
	int				wstatus;

	tmp = cmd;
	if (cmd->str && is_builtin(cmd->str[0]) && !cmd->next)
		if (EXIT_FAILURE == ft_single_builtin(cmd, data, std_out))
			return (EXIT_FAILURE);
	while (tmp)
	{
		if (tmp->next)
			if (-1 == close(tmp->pipe_fd[1]))
				return (perror("-minishell "), data->last_exit = errno, 1);
		if (tmp->prev)
			if (-1 == close(tmp->prev->pipe_fd[0]))
				return (perror("-minishell "), data->last_exit = errno, 1);
		tmp = tmp-> next;
	}
	while (cmd)
	{
		wait_signal(0);
		wait(&wstatus);
		cmd = cmd->next;
	}
	close(std_out);
	return (ft_parent_exit(wstatus, &(data->last_exit)));
}

/** Gestiona los casos en los que solo se recibe un comando builtin como input.
 * Cuando minishell recibe un solo comando y es una builtin function
 * el programa ejecuta la funcion en el mismo proceso, no crea un subproceso.
 *
 * @param cmd Puntero a la estructura que contiene informacion del
 * comando.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 * @param std_out File descriptor que apunta al STDOUT por defecto del 
 * terminal, para recuperarlo en caso de que se haya cambiado.
 *
 * @return Resultado de la ejecucion. Actualiza a traves de punteros el
 * err_n en caso de fallo.
 */
static int	ft_single_builtin(t_single_cmd *cmd, t_data *data, int std_out)
{
	int	default_stdin;
	int	exit_status;

	default_stdin = dup(STDIN_FILENO);
	if (0 > default_stdin)
		return (perror("-minishell "), data->last_exit = errno, \
			EXIT_FAILURE);
	if (EXIT_FAILURE == ft_prepare_redirections(cmd, &(data->last_exit)))
		return (EXIT_FAILURE);
	if (0 > dup2(default_stdin, STDIN_FILENO))
		return (close(default_stdin), perror("-minishell "), \
			data->last_exit = errno, EXIT_FAILURE);
	exit_status = execute_builtin(cmd->str, data->env, &(data->last_exit));
	if (0 > dup2(std_out, STDOUT_FILENO))
		return (close(default_stdin), perror("-minishell "), \
			data->last_exit = errno, EXIT_FAILURE);
	ft_close(default_stdin, &(data->last_exit));
	return (exit_status);
}
