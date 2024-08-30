/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:20:04 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 20:59:25 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include <stdio.h>

// Función para verificar si una cadena es numérica
static int	ft_is_str_zero(char *str)
{
	int	i;

	i = 0;
	while (ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

// Función para liberar un array de cadenas
static void	free_arr_exit(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] != NULL)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

// Función para determinar el código de salida y salir del programa
void	determine_exit_code(char **args)
{
	int	exit_code;

	if (!args[1])
		exit_code = 0;
	else if (ft_atoi(args[1]) != 0 \
		|| (ft_atoi(args[1]) == 0 && ft_is_str_zero(args[1])))
	{
		if (ft_atoi(args[1]) < 0)
			exit_code = 255 + (ft_atoi(args[1])) + 1;
		else if (ft_atoi(args[1]) > 255)
			exit_code = 0 + ft_atoi(args[1]) % 255;
		else
			exit_code = ft_atoi(args[1]);
	}
	else
	{
		ft_putendl_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	free_arr_exit(args);
	exit(exit_code);
}

/** Implementación del comando 'exit' ajustada para aceptar args como argumento
 *  global o externo.
*/
void	builtin_exit(char **args, t_env *env, int *last_exit)
{
	(void)env;
	if (args[1] && args[2])
	{
		*last_exit = 1;
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("-minishell: exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
	determine_exit_code(args);
}
