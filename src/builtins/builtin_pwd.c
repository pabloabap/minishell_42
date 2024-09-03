/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:23:51 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 20:37:56 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Implementación del comando `pwd`, que muestra el directorio de trabajo 
 * actual en la salida estándar. La función utiliza `getcwd` para obtener 
 * la ruta absoluta del directorio actual y la imprime. Si `getcwd` falla, 
 * se muestra un mensaje de error y se establece el código de salida en 1.
 */
void	builtin_pwd(char **args, t_env *env, int *last_exit)
{
	char		cwd[1024];
	char		*result;
	const char	*error_msg;

	(void)args;
	(void)env;
	result = getcwd(cwd, sizeof(cwd));
	if (result != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
	{
		error_msg = "-minishell: pwd: Failure getting the current directory\n";
		write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
		*last_exit = 1;
	}
}
