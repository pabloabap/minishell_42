/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:17:13 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/27 23:17:20 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_heredoc_creation(t_lexem *redir, t_data *data);
static int	ft_fill_hdoc(char *line, t_data *data, int fd_hdoc);
static int	ft_write_char(char *line, int *i, int fd_hdoc, int *err_n);
static int	ft_write_env_var(char *line, int v_start, t_data *data, int hdoc);

/** Crea un heredoc(fichero temporal) en el que almacenar el input recibido
 *  por el usuario hasta llegar a un string marcado como indicador de final de
 *  fichero. Se expanden variable de entorno del fichero salvo si el indicador
 *  de final de fichero es entrecomillado (`redir->token` >= SINGLE_QUO_RED).
 *
 *	@param	redir estructura `t_lexem` que contiene informacion del tipo de
 *	redireccion (atributo `token`) y el indicador de final del fichero
 *  (atributo `str`).
 *  @param data Puntero a la estructura data con datos generales del programa
 *  para utilizar o modificar los atributos last_exit y env.
 * 
 * 	@return fd en formato lectura recien abierto. 
 */
int	ft_check_hdoc(t_single_cmd *cmd, t_data *data)
{
	t_lexem	*redir;

	redir = cmd->redirection;
	while (redir)
	{
		if (redir->token >= HERE_DOC)
		{
			cmd->fd_hdoc = ft_heredoc_creation(redir, data);
			if (0 > cmd->fd_hdoc)
				return (EXIT_FAILURE);
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}

static int	ft_heredoc_creation(t_lexem *redir, t_data *data)
{
	int		w_fd;
	int		r_fd;
	char	*line;

	w_fd = open("./tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (w_fd < 0)
		return (perror("-minishell "), w_fd);
	line = readline("heredoc> ");
	while (line && ft_strncmp(line, redir->str, ft_strlen(redir->str) + 1))
	{
		if (redir->token >= SINGLE_QUO_RED)
			ft_putstr_fd(line, w_fd);
		else if (EXIT_FAILURE == ft_fill_hdoc(line, data, w_fd))
			return (free(line), ft_close(w_fd, &(data->last_exit)), -1);
		write(w_fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	ft_hdoc_close_check(redir, line, &(data->last_exit));
	ft_close(w_fd, &(data->last_exit));
	r_fd = open("./tmp.txt", O_RDONLY);
	if (0 > r_fd)
		data->last_exit = errno;
	return (unlink("tmp.txt"), r_fd);
}

/** Escribe caracteres de un string que no tienen que ser expandidos en
 * 	el fichero al que apunta fd_hdoc.
 *
 *	@param	line String a procesar.
 *  @param data Puntero a la estructura data con datos generales del programa
 *  para utilizar o modificar los atributos last_exit y env.
 *	@param	fd_hdoc fd en modo escritura del heredoc.
 * 	para modificar el valor si es necesario.
 *
 * 	@return Resultado de ejecucion.
 */
static int	ft_fill_hdoc(char *line, t_data *data, int fd_hdoc)
{
	int		i;
	char	*char_exit;

	i = 0;
	char_exit = ft_itoa(data->last_exit);
	if (!char_exit)
		return (EXIT_FAILURE);
	if (EXIT_FAILURE == ft_write_char(line, &i, fd_hdoc, &(data->last_exit)))
		return (free(char_exit), EXIT_FAILURE);
	if (line[i] == '$')
	{
		i++;
		if (line[i] == '?')
		{
			if (-1 == write(fd_hdoc, char_exit, ft_strlen(char_exit)))
				return (free(char_exit), data->last_exit = errno, EXIT_FAILURE);
			line += ++i;
			if (EXIT_FAILURE == ft_fill_hdoc(line, data, fd_hdoc))
				return (free(char_exit), EXIT_FAILURE);
		}
		else if (EXIT_FAILURE == ft_write_env_var(line, i, data, fd_hdoc))
			return (free(char_exit), EXIT_FAILURE);
	}
	return (free(char_exit), EXIT_SUCCESS);
}

/** Escribe caracteres de un string que no tienen que ser expandidos en
 * 	el fichero al que apunta fd_hdoc.
 *
 *	@param	line String a procesar.
 *	@param	i Indice del caracter a procesar.
 *	@param	fd_hdoc fd en modo escritura del heredoc.
 * 	para modificar el valor si es necesario.
 *	@param 	err_n Puntero a int que almacena el errno de la ultima ejecucion
 *	para modificar el valor si es necesario.
 *
 * 	@return Resultado de ejecucion.
 */
static int	ft_write_char(char *line, int *i, int fd_hdoc, int *err_n)
{
	while (line[*i] && line[*i] != '$')
	{
		if (-1 == write(fd_hdoc, &line[*i], 1))
			return (*err_n = errno, EXIT_FAILURE);
		*i += 1;
	}
	return (EXIT_SUCCESS);
}

/** Escribe el valor de una variable de entorno que se encuentra
 *  en un string en el fichero al que apunta hdoc.
 *
 *	@param	line String que contiene una variable de entorno.
 *	@param	v_start Indice del comienzo del VAR_NAME.
 *  @param data Puntero a la estructura data con datos generales del programa
 *  para utilizar o modificar los atributos last_exit y env.
 *	@param	hdoc fd en modo escritura del heredoc.
 * 	para modificar el valor si es necesario.
 *
 * 	@return Resultado de ejecucion.
 */
static int	ft_write_env_var(char *line, int v_start, t_data *data, int hdoc)
{
	char	*v_name;
	int		v_end;

	v_end = v_start;
	while (ft_isalnum(line[v_end]) || line[v_end] == '_')
		v_end += 1;
	if (v_end > v_start)
	{
		v_name = ft_substr(line, v_start, v_end - v_start);
		if (v_name == NULL)
			return (perror("-minishell "), data->last_exit = errno, 1);
		if (ft_getenv(v_name, data->env->envp_cpy) != NULL)
			ft_putstr_fd(ft_getenv(v_name, data->env->envp_cpy), hdoc);
		free(v_name);
	}
	else
		if (-1 == write(hdoc, "$", 1))
			return (perror("-minishell "), data->last_exit = errno, 1);
	if (line[v_end])
	{
		line += v_end;
		if (EXIT_FAILURE == ft_fill_hdoc(line, data, hdoc))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
