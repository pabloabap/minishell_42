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
static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Función para liberar un array de cadenas
static void	free_arr(char **arr)
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

	if (!args[1]) // Si no hay argumentos adicionales, el código de salida es 0
		exit_code = 0;
	else if (is_str_digit(args[1])) // Verifica si el argumento es numérico
		exit_code = ft_atoi(args[1]); // Convierte el argumento a un código de salida
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 255; // Código de salida para argumentos no numéricos
	}
	free_arr(args); // Libera el array de argumentos
	exit(exit_code); // Sale del programa con el código de salida determinado
}

/** Implementación del comando 'exit' ajustada para aceptar args como argumento
 *  global o externo.
*/
void	builtin_exit(char **args, t_env *env)
{
	(void)env; //Ignora envp ya que no se utiliza en esta función

	if (args[1] && args[2])
	{ // Verifica si hay demasiados argumentos
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return ; // Retorna sin salir si hay demasiados argumentos
	}
	determine_exit_code(args); // Determina el código de salida y sale del programa
}
