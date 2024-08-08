/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:22:37 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 19:16:40 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_prepare_exec(t_single_cmd *head, int *std_out, int *err_n);
static int	ft_child_mng(t_single_cmd *cmd, int std_out, char **envp, int *e);
static int	ft_parent_mng(t_single_cmd *cmd, char **envp, int *err_n, \
		int std_out);
static int	ft_single_builtin(t_single_cmd *cmd, char **envp, int *err_n, \
	int std_out);

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
		if (is_builtin(head->str[0]))
        {
            // Ejecutar builtin en el proceso padre
            printf("Ejecutando builtin en el proceso padre...\n");
            execute_builtin(head->str, envp);
            head = head->next; // Mover al siguiente comando
            continue; // Saltar la creación de un proceso hijo para este comando
        }
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
	if (is_builtin(cmd->str[0]) && !cmd->prev && !cmd->next)
		return (exit(0), EXIT_SUCCESS);
	else if (!cmd->str || \
		EXIT_FAILURE == ft_set_pipes(cmd, std_out, en, 0) || \
		EXIT_FAILURE == ft_prepare_redirections(cmd, en) || \
		EXIT_FAILURE == ft_path_finder(cmd, en))
		return (exit(*en), EXIT_FAILURE);
	else if (is_builtin(cmd->str[0]) && cmd->next)
		execute_builtin(cmd->str, envp);
	else if (execve(cmd->cmd_path, cmd->str, envp) < 0)
	{
		printf("ENTRA2!!\n");
		if (access(cmd->cmd_path, X_OK) < 0)
			return (perror("2-Minishell "), exit(126), EXIT_FAILURE);
		return (perror("22-Minishell "), exit(errno), EXIT_FAILURE);
	}
	return (exit(0), EXIT_SUCCESS);
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
static int	ft_parent_mng(t_single_cmd *cmd, char **envp, int *err_n, \
	int std_out)
{
	t_single_cmd	*tmp;
	int				wstatus;

	tmp = cmd;
	if (is_builtin(cmd->str[0]) && !cmd->next)
		if (EXIT_FAILURE == ft_single_builtin(cmd, envp, err_n, std_out))
			return (EXIT_FAILURE);
	while (tmp)
	{
		if (tmp->next)
			if (-1 == close(tmp->pipe_fd[1]))
				return (perror("3-Minishell "), *err_n = errno, EXIT_FAILURE);
		if (tmp->prev)
			if (-1 == close(tmp->prev->pipe_fd[0]))
				return (perror("33-Minishell "), *err_n = errno, EXIT_FAILURE);
		tmp = tmp-> next;
	}
	while (cmd)
	{
		wait_signal(0);
		wait(&wstatus);
		cmd = cmd->next;
	}
	close (std_out);
	return (ft_parent_exit(wstatus, err_n));
}

/** Gestiona los casos en los que solo se recibe un comando builtin como input.
 * Cuando minishell recibe un solo comando y es una builtin function
 * el programa ejecuta la funcion en el mismo proceso, no crea un subproceso.
 * 
 * @param cmd Puntero a la estructura que contiene informacion del 
 * comando.
 * @param envp Array a las variables de entorno.
 * @param err_n Puntero al espacio de memoria que almacena el numero del
 * ultimo error de ejecucion.
 * @param std_out File descriptor que apunta al STDOUT por defecto del 
 * terminal, para recuperarlo en caso de que se haya cambiado.
 * 
 * @return Resultado de la ejecucion. Actualiza a traves de punteros el
 * err_n en caso de fallo.
 */
static int	ft_single_builtin(t_single_cmd *cmd, char **envp, int *err_n, \
	int std_out)
{
	int	default_stdin;

	default_stdin = dup(STDIN_FILENO);
	if (0 > default_stdin)
		return (perror("0000-Minishell "), *err_n = errno, EXIT_FAILURE);
	if (EXIT_FAILURE == ft_prepare_redirections(cmd, err_n))
		return (EXIT_FAILURE);
	if (0 > dup2(default_stdin, STDIN_FILENO))
		return (close (default_stdin), perror("00000-Minishell "), \
			*err_n = errno, EXIT_FAILURE);
	execute_builtin(cmd->str, envp);
	if (0 > dup2(std_out, STDOUT_FILENO))
		return (close (default_stdin), perror("000000-Minishell "), \
			*err_n = errno, EXIT_FAILURE);
	ft_close(default_stdin, err_n);
	return (EXIT_SUCCESS);
}
