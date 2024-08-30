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

void	builtin_pwd(char **args, t_env *env)
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
		error_msg = "minishell: pwd: Error al obtener el directorio actual\n";
		write(STDERR_FILENO, error_msg, strlen(error_msg));
	}
}
