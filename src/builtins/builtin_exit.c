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

static void	free_arr_exit(char **arr);
static int	ft_is_str_zero(char *str);
static void	determine_exit_code(char **args);

/**
 * Implementación del comando `exit`. 
 * Verifica si hay demasiados argumentos; si es así, imprime un error y 
 * establece el código de salida en 1. Si no, llama a determine_exit_code() 
 * para calcular el código de salida y termina la ejecución.
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
	ft_putendl_fd("exit", STDOUT_FILENO);
	determine_exit_code(args);
}

// Función que determina el código de salida basado en los argumentos.
// Si el primer argumento es un número, se usa como código de salida. 
// Si es cero, se verifica si es un cero válido usando ft_is_str_zero().
// Maneja errores como demasiados argumentos o argumentos no numéricos.
static void	determine_exit_code(char **args)
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
		ft_putstr_fd("-minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	free_arr_exit(args);
	exit(exit_code);
}

/* Función que verifica si una cadena de caracteres representa
* el valor numérico cero.
* Ignora los espacios en blanco y los signos '+' o '-'. 
* Si todos los caracteres 
* restantes son '0', devuelve 1, indicando que es cero; de lo contrario,
* devuelve 0.
*/
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

// Función que libera la memoria ocupada por un array de cadenas de caracteres.
// Recorre cada elemento del array y lo libera individualmente antes de liberar
// el propio array.
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
