/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mng_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:23:07 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:23:11 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_open_redirs(t_single_cmd *cmd, t_lexem *redir, int *err_n);
static int	ft_dup_manage(int fd, t_lexem *redir, int *err_n);

/** Función principal de gestion de las redirecciones.
 * 
 * @param redirs Puntero a la cabecera de la lista `t_lexem`
 * que contine las redirecciones a aplicar a un comando.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 * 
 * @return Resultado de ejecución de la función.
 */

int	ft_prepare_redirections(t_single_cmd *cmd, int *err_n)
{
	t_lexem	*redirs;
	t_lexem	*tmp;
	int		hdoc_count;

	redirs = cmd->redirection;
	tmp = cmd->redirection;
	hdoc_count = 0;
	while (tmp)
	{
		if (tmp->token >= HERE_DOC)
			hdoc_count ++;
		tmp = tmp->next;
	}
	while (redirs)
	{
		if (hdoc_count > 1)
			hdoc_count --;
		else if (EXIT_FAILURE == ft_open_redirs(cmd, redirs, err_n))
			return (EXIT_FAILURE);
		redirs = redirs->next;
	}
	return (EXIT_SUCCESS);
}

/** Función para abrir los ficheros de redirección con las configuraciones
 * especificas para cada uno.
 * 
 * @param cmd Puntero al comando simple a tratar.
 * @param redirs Puntero la redirecci'on a tratar.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 *  
 * @return Resultado de ejecución e impresioón de error si existe. 
 */
static int	ft_open_redirs(t_single_cmd *cmd, t_lexem *redir, int *err_n)
{
	int	fd;

	if (redir->token == IN_REDIR)
		fd = open(redir->str, O_RDONLY);
	if (redir->token == OUT_REDIR)
		fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (redir->token == APPEND_REDIR)
		fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, \
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (redir->token >= HERE_DOC)
		fd = cmd->fd_hdoc;
	if (fd < 0)
		return (ft_putstr_fd("-minishell: ", STDERR_FILENO), \
			perror(redir->str), *err_n = 1, EXIT_FAILURE);
	else
	{
		if (EXIT_FAILURE == ft_dup_manage(fd, redir, err_n))
			return (*err_n = errno, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/** Ajuste de STDIN y STDOUT para que apunten a los ficheros de redirección
 * que les corresponde.
 * 
 * @param fd File descriptor del que duplicar la referencia.
 * @param redirs Puntero la redirecci'on a tratar.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 * 
 * @return Resultado de ejecución de la función.
 */

static int	ft_dup_manage(int fd, t_lexem *redir, int *err_n)
{
	if (redir->token == IN_REDIR || redir->token >= HERE_DOC)
	{
		if (0 > dup2(fd, STDIN_FILENO))
			return (close (fd), perror("-minishell "), \
				*err_n = errno, EXIT_FAILURE);
	}
	else if (redir->token == OUT_REDIR || redir->token >= APPEND_REDIR)
	{
		if (0 > dup2(fd, STDOUT_FILENO))
			return (close (fd), perror("-minishell "), \
				*err_n = errno, EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}
