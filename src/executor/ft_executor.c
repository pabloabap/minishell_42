/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:22:37 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:22:43 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_prepare_exec(t_single_cmd *head, int *std_out, int *err_n);
static int	ft_builtins(t_single_cmd *cmd, int std_out, char **envp, int *en);
static int	ft_child_mng(t_single_cmd *cmd, int std_out, char **envp, int *e);
static int	ft_parent_mng(t_single_cmd *cmd, char **envp, int *err_n, int std_out);

/** Funcion principal executor. Crea un proceso hijo por comando 
 * a ejecutar, configura su entrada, salida y redirecciones y los ejecuta 
 * en paralelo.
 * El padre espera la finalizacion de todos los hijos para recoger
 * el exit status final.
 * 
 * @param head Puntero al primer comando de la lista de comandos
 * @param envp Variables de entorno aplicables.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion.
 * 
 * @return Resultado de la ejecución.
 */
int	ft_executor(t_single_cmd *head, char **envp, int *err_n)
{
	int				std_out;
	int				pid;
	t_single_cmd	*tmp;

	tmp = head;
	if (EXIT_FAILURE == ft_prepare_exec(head, &std_out, err_n))
		return (EXIT_FAILURE);
	while (head)
	{
		pid = fork();
		if (pid == -1)
			return (perror("00-Minishell"), *err_n = errno, EXIT_FAILURE);
		if (pid == 0)
			if (EXIT_FAILURE == ft_child_mng(head, std_out, envp, err_n))
				return (EXIT_FAILURE);
		head = head->next;
	}
	if (EXIT_FAILURE == ft_parent_mng(tmp, envp, err_n, std_out))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Crea los pipes necesarios en la ejecución (uno menos que el número de 
 * comandos).
 * 
 * @param head Puntero al primer elemento de la lista de comandos.
 * @param std_out Referencia al STDOUT para que en caso de que tenga que ser 
 * modificado por por algún comando intermedio podamos recuperar el principal.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion.
 * 
 * @return Resultado de la ejecución e impresión de error si existe. 
 */
static int	ft_prepare_exec(t_single_cmd *head, int *std_out, int *err_n)
{
	while (head)
	{
		if (head->next)
			if (-1 == pipe(head->pipe_fd))
				return (perror("1-Minishell "), *err_n = errno, EXIT_FAILURE);
		if (EXIT_FAILURE == ft_check_hdoc(head, err_n))
			return (EXIT_FAILURE);
		head = head->next;
	}
	*std_out = dup(STDOUT_FILENO);
	if (*std_out == -1)
		return (perror("11-Minishell "), *err_n = errno, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_builtins(t_single_cmd *cmd, int std_out, char **envp, int *en)
{
	char	*builtins;
	char	**tmp;
	int		i;

	builtins = "echo:cd:pwd:export:unset:env:exit";
	tmp = ft_split(builtins, ':');
	i = 0;
	while (cmd)
	{
		while (tmp[i])
		{
			if (0 == ft_strncmp(tmp[i], cmd->str[0], ft_strlen(tmp[i]) + 1))
			{
				if (EXIT_FAILURE == ft_set_pipes(cmd, std_out, en, 1) || \
					EXIT_FAILURE == ft_prepare_redirections(cmd, en))					
					return (printf("A22X\n"), exit(*en), EXIT_FAILURE);
				execute_builtin(cmd->str, envp);
			}
			if (!cmd->next)
				free(tmp[i]);
			i ++;
		}
		i = 0;
		cmd = cmd->next;
	}
	free(tmp);
	return (EXIT_SUCCESS);
}

/** Gestiona instrucciones para el proceso hijo de un fork.
 * 
 * @param cmd Puntero al comando actual a procesar.
 * @param main_out file descriptor del STDOUT principal.
 * @param envp Puntero de punteros a la lista de variables de entorno.
 * @param en Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 * 
 * @return Resultado de ejecición e impresión de errores si procede.
 */
static int	ft_child_mng(t_single_cmd *cmd, int std_out, char **envp, int *en)
{
	if (is_builtin(cmd->str[0]))
		return (exit(0), EXIT_SUCCESS);
	else if (!cmd->str || \
		EXIT_FAILURE == ft_set_pipes(cmd, std_out, en, 0) || \
		EXIT_FAILURE == ft_prepare_redirections(cmd, en) || \
		EXIT_FAILURE == ft_path_finder(cmd, en))
		return (exit(*en), EXIT_FAILURE);
	else if (execve(cmd->cmd_path, cmd->str, envp) < 0)
	{
		if (access(cmd->cmd_path, X_OK) < 0)
			return (perror("2-Minishell "), exit(126), EXIT_FAILURE);
		return (perror("22-Minishell "), exit(errno), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/** Gestiona instrucciones para el proceso padre en un fork.
 * Cierra todos los pipes ya que no son utilizados en el padre.
 * Espera a que los procesos hijos terminen y comprueba el exit status 
 * para actualizarlo si es necesario.
 * 
 * @param cmd Doble puntero al comando actual a procesar.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 * 
 * @return Resultado de ejecición e impresión de errores si procede. 
 */
static int	ft_parent_mng(t_single_cmd *cmd, char **envp, int *err_n, int std_out)
{
	t_single_cmd	*tmp;
	//t_single_cmd	*tmp2;
	int				wstatus;

	tmp = cmd;
	//tmp2 = cmd;
	ft_builtins(cmd, std_out, envp, err_n);
    //close (std_out);
	while (tmp)
	{
		if (tmp->next)
			if (!is_builtin(tmp-> str[0]) && -1 == close(tmp->pipe_fd[1]))
				return (perror("3-Minishell "), *err_n = errno, EXIT_FAILURE);
		if (tmp->prev)
			if (!is_builtin(tmp-> str[0]) && -1 == close(tmp->prev->pipe_fd[0]))
				return (perror("33-Minishell "), *err_n = errno, EXIT_FAILURE);
		tmp = tmp-> next;
	}
	while (cmd)
	{
		wait_signal(0);
		if (!is_builtin(cmd->str[0]))
			wait(&wstatus);
		cmd = cmd->next;
	}
	return (ft_parent_exit(wstatus, err_n));
}
