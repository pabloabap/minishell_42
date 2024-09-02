/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:23:43 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 21:00:11 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Ejecuta el comando interno correspondiente, si existe.
 * 
 * @param args Arreglo de cadenas que contiene el comando y sus argumentos.
 * @param env Puntero a la estructura de entorno, que contiene las variables
 * de entorno actuales.
 * @param last_exit Puntero a un entero que almacena el estado de salida del 
 * último comando ejecutado.
 * 
 * @return EXIT_SUCCESS si el comando se ejecuta exitosamente o no cambia el 
 * valor de last_exit,
 *         y EXIT_FAILURE si el comando falla y cambia el valor de last_exit.
 */
int	execute_builtin(char **args, t_env *env, int *last_exit)
{
	t_builtin_func	builtin_func;
	int				tmp_last_exit;

	tmp_last_exit = *last_exit;
	builtin_func = builtin_arr(args[0]);
	if (builtin_func != NULL)
		builtin_func(args, env, last_exit);
	if (tmp_last_exit == 0 && tmp_last_exit != *last_exit)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

/**
 * Devuelve la función correspondiente al comando interno especificado.
 * 
 * @param str Cadena que contiene el nombre del comando interno.
 * 
 * @return Un puntero a la función del comando interno si se encuentra, 
 *         o NULL si no se encuentra.
 */
t_builtin_func	builtin_arr(char *str)
{
	static t_builtin	builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit}
	};
	size_t				num_builtins;
	size_t				i;

	num_builtins = sizeof(builtins) / sizeof(builtins[0]);
	i = 0;
	while (i < num_builtins)
	{
		if (str && !ft_strncmp(builtins[i].name, str,
				ft_strlen(builtins[i].name) + 1))
		{
			return (builtins[i].func);
		}
		i++;
	}
	return (NULL);
}

/**
 * Verifica si el comando proporcionado es una función interna (builtin).
 * 
 * @param command Cadena que contiene el nombre del comando a verificar.
 * 
 * @return 1 si el comando es una función interna, o 0 si no lo es.
 */
int	is_builtin(char *command)
{
	return (builtin_arr(command) != NULL);
}
