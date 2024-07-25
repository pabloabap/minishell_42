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

static int	ft_prepare_exec(t_single_cmd *head, int *main_out);
static int	ft_child_mng(t_single_cmd *cmd, int main_out, char **envp);
static int	ft_parent_mng(t_single_cmd **cmd);
static char	*ft_path_finder(char *cmd_name);

/** Funcion principal executor. Crea un proceso hijo por comando 
 * a ejecutar y configura su entrada, salida y redirecciones. 
 * El padre espera la finalizacion del proceso hijo, recoge su
 * estado de salida y mueve head al siguiente comando a ejecutar 
 * si la ejecucion ha ido bien.
 * 
 * @param head Puntero al primer comando de la lista de comandos
 * @param envp Variables de entorno aplicables.
 * 
 * @return Resultado de la ejecución.
 */
int	ft_executor(t_single_cmd *head, char **envp)
{
	int	main_out;
	int	pid;

	if (EXIT_FAILURE == ft_prepare_exec(head, &main_out))
		return (EXIT_FAILURE);
	while (head)
	{
		pid = fork();
		if (pid == -1)
			return (perror("02_Minishell"), EXIT_FAILURE);
		if (pid == 0)
			ft_child_mng(head, main_out, envp);
		if(EXIT_FAILURE == ft_parent_mng(&head))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/** Crea los pipes necesarios en la ejecución (uno menos que el número de 
 * comandos).
 * 
 * @param head Puntero al primer elemento de la lista de comandos.
 * @param main_out Referencia al STDOUT para que en caso de que tenga que ser 
 * modificado por por algún comando intermedio podamos recuperar el principal.
 * 
 * @return Resultado de la ejecución e impresión de error si existe. 
 */
static int	ft_prepare_exec(t_single_cmd *head, int *main_out)
{
	while (head)
	{
		if (head->next)
			if (-1 == pipe(head->pipe_fd))
				return (perror("1_PREPARE_Minishell "), EXIT_FAILURE);
		head = head->next;
	}
	*main_out = dup(STDOUT_FILENO);
	if (*main_out == -1)
		return (perror("3_PREPARE_Minishell "), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Gestiona instrucciones para el proceso hijo de un fork.
 * 
 * @param cmd Puntero al comando actual a procesar.
 * @param main_out file descriptor del STDOUT principal.
 * @param envp Puntero de punteros a la lista de variables de entorno.
 * 
 * @return Resultado de ejecición e impresión de errores si procede. * 
 */
static int	ft_child_mng(t_single_cmd *cmd, int main_out, char **envp)
{
	if (EXIT_FAILURE == ft_set_pipes(cmd, main_out))
		return (EXIT_FAILURE);
	if (EXIT_FAILURE == ft_prepare_redirections(cmd->redirection))
		return (EXIT_FAILURE);
	if (execve(ft_path_finder(cmd->str[0]), cmd->str, envp) < 0)
		return(perror("1_EXEC_Minishell "), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Gestiona instrucciones para el proceso padre en un fork.
 * Espera a que su proceso hijo termine, cierra los extremos de los pipes 
 * que ya no se van a utilizar (el de lectura del pipe almacenado en la 
 * estructura del cmd anterior y , si hay siguiente comando, el de escritura
 * del pipe almacenado en la estructura del comando actual).
 * 
 * @param cmd Doble puntero al comando actual a procesar.
 * 
 * @return Resultado de ejecición e impresión de errores si procede. 
 */
static int	ft_parent_mng(t_single_cmd **cmd)
{
	t_single_cmd	*tmp;
	int				wstatus;

	tmp = *cmd;
	wait(&wstatus);
	if (tmp->next)
		if (-1 == close(tmp->pipe_fd[1]))
			return (perror("Minishell "), EXIT_FAILURE);
	if (tmp->prev)
		if (-1 == close(tmp->prev->pipe_fd[0]))
			return (perror("Minishell "), EXIT_FAILURE);
	*cmd = tmp->next;
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Localiza la ruta del comando.
 * 
 * @param cmd_name Nombre del comando a buscar.
 * 
 * @return Ruta absoluta al fichero del comando. 
 */
static char	*ft_path_finder(char *cmd_name)
{
	char			**dirs;
	int				i;
	DIR				*actual;
	struct dirent	*subdir;

	dirs = ft_split(getenv("PATH"), ':');
	i = 0;
	while (dirs && dirs[i])
	{
		actual = opendir(dirs[i]);
		if (actual != NULL)
		{
			subdir = readdir(actual);
			while (subdir)
			{
				if (!ft_strncmp(subdir->d_name, cmd_name, ft_strlen(cmd_name)) \
					&& ft_strlen(subdir->d_name) == ft_strlen(cmd_name))
					return (ft_strjoin(ft_strjoin(dirs[i], "/"), subdir->d_name));
				subdir = readdir(actual);
			}
			closedir(actual);
		}
		free(dirs[i]);
		dirs[i] = NULL;
		i++;
	}
	free(dirs);
	dirs = NULL;
	return (NULL);
}
