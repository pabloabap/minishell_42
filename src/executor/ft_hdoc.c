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

static int	ft_fill_hdoc(char *line, int *err_n, int fd_hdoc);
static int	ft_write_char(char *line, int *i, int fd_hdoc, int *err_n);
static int	ft_write_env_var(char *line, int v_start, int *err_n, int hdoc);

/** Crea un heredoc(fichero temporal) en el que almacenar el input recibido 
 *  por el usuario hasta llegar a un string marcado como indicador de final de
 *  fichero. Se expanden variable de entorno del fichero salvo si el indicador 
 *  de final de fichero es entrecomillado (`redir->token` >= SINGLE_QUO_RED).
 * 	
 *	@param	redir estructura `t_lexem` que contiene informacion del tipo de 
 *	redireccion (atributo `token`) y el indicador de final del fichero
 *  (atributo `str`).
 *	@param err_n Puntero a int que almacena el errno de la ultima ejecucion
 *	para modificar el valor si es necesario.
 * 
 * 	@return fd en formato lectura recien abierto. 
 */
int	ft_heredoc_creation(t_lexem *redir, int *err_n)
{
	int		w_fd;
	int		r_fd;
	char	*line;

	w_fd = open("./tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (w_fd < 0)
		return (perror("Minishell% "), w_fd);
	line = readline("heredoc> ");
	while (0 != ft_strncmp(line, redir->str, ft_strlen(redir->str) + 1))
	{
		if (redir->token >= SINGLE_QUO_RED)
			ft_putstr_fd(line, w_fd);
		else if (EXIT_FAILURE == ft_fill_hdoc(line, err_n, w_fd))
			return (ft_close(w_fd, err_n), -1);
		write(w_fd, "\n", 1);
		line = readline("heredoc> ");
	}
	ft_close(w_fd, err_n);
	r_fd = open("./tmp.txt", O_RDONLY);
	if (0 > r_fd)
		*err_n = errno;
	unlink("tmp.txt");
	return (r_fd);
}

/** Escribe caracteres de un string que no tienen que ser expandidos en
 * 	el fichero al que apunta fd_hdoc.
 * 	
 *	@param	line String a procesar.
 *	@param err_n Puntero a int que almacena el errno de la ultima ejecucion
 *	para modificar el valor si es necesario.
 *	@param	fd_hdoc fd en modo escritura del heredoc.
 * 	para modificar el valor si es necesario.
 * 
 * 	@return Resultado de ejecucion. 
 */
static int	ft_fill_hdoc(char *line, int *err_n, int fd_hdoc)
{
	int		i;
	char	*char_exit;

	i = 0;
	char_exit = ft_itoa(*err_n);
	if (!char_exit)
		return (EXIT_FAILURE);
	if (EXIT_FAILURE == ft_write_char(line, &i, fd_hdoc, err_n))
		return (free(char_exit), EXIT_FAILURE);
	if (line[i] == '$')
	{
		i ++;
		if (line[i] == '?')
		{
			if (-1 == write(fd_hdoc, char_exit, ft_strlen(char_exit)))
				return (free(char_exit), *err_n = errno, EXIT_FAILURE);
			line += ++i;
			if (EXIT_FAILURE == ft_fill_hdoc(line, err_n, fd_hdoc))
				return (free(char_exit), EXIT_FAILURE);
		}
		else
			if (EXIT_FAILURE == ft_write_env_var(line, i, err_n, fd_hdoc))
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
 *	@param	err_n Puntero a int que almacena el errno de la ultima ejecucion
 *	para modificar el valor si es necesario.
 *	@param	hdoc fd en modo escritura del heredoc.
 * 	para modificar el valor si es necesario.
 * 
 * 	@return Resultado de ejecucion. 
 */
static int	ft_write_env_var(char *line, int v_start, int *err_n, int hdoc)
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
			return (perror("Minishell% "), *err_n = errno, EXIT_FAILURE);
		if (getenv(v_name) != NULL)
			ft_putstr_fd(getenv(v_name), hdoc);
		free(v_name);
	}
	else
		if (-1 == write(hdoc, "$", 1))
			return (perror("Minishell% "), *err_n = errno, EXIT_FAILURE);
	if (line[v_end])
	{
		line += v_end;
		if (EXIT_FAILURE == ft_fill_hdoc(line, err_n, hdoc))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
