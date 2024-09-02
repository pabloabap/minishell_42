/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:38:19 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 20:43:46 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Prototipos de funciones internas
static void	remove_env_var(char ***envp, int index);
static int	find_env_var_index(char **envp, const char *var);

/*
 * Implementación del comando `unset`, que elimina variables de entorno 
 * y de exportación. La función recorre los argumentos proporcionados y 
 * elimina las variables correspondientes de ambos arrays de entorno 
 * (`envp_cpy` y `export_cpy`). Si una variable está presente en cualquiera 
 * de los arrays, se elimina de dicho array.
 */
void	builtin_unset(char **args, t_env *env, int *last_exit)
{
	int		i;
	int		index;

	i = 1 + 0 * *last_exit;
	while (args[i])
	{
		index = find_env_var_index(env->envp_cpy, args[i]);
		if (index != -1)
			remove_env_var(&env->envp_cpy, index);
		index = find_env_var_index(env->export_cpy, args[i]);
		if (index != -1)
			remove_env_var(&env->export_cpy, index);
		i++;
	}
}

/*
 * Encuentra el índice de la variable especificada en el array de entorno `envp`.
 * Compara el nombre de la variable con cada entrada en el array y devuelve el 
 * índice si hay una coincidencia. Si no se encuentra la variable, devuelve -1.
 * @Parámetros:
 *  - envp: array de cadenas que representan las variables de entorno.
 *  - var: nombre de la variable a buscar.
 * @Devuelve:
 *  - El índice de la variable en el array si se encuentra; -1 si no se
 * 	encuentra.
 */
static int	find_env_var_index(char **envp, const char *var)
{
	int		i;
	int		var_len;

	var_len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], var, var_len) == 0
				&& envp[i][var_len] == '=') ||
			(ft_strncmp(envp[i], var, var_len) == 0
			&& envp[i][var_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

/*
 * Elimina una variable de entorno en el índice especificado del array `envp`.
 * La función crea un nuevo array de entorno sin la variable eliminada, libera 
 * la memoria del array original y asigna el nuevo array al puntero de entorno.
 * 
 * @Parámetros:
 *  - envp: puntero al array de variables de entorno que se modificará.
 *  - index: índice de la variable que se eliminará del array.
 */
static void	remove_env_var(char ***envp, int index)
{
	int		len;
	int		i;
	char	**new_envp;

	len = 0;
	while ((*envp)[len])
		len++;
	new_envp = (char **)malloc(sizeof(char *) * len);
	if (!new_envp)
		return ;
	i = 0;
	while (i < index)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	while (i < len - 1)
	{
		new_envp[i] = (*envp)[i + 1];
		i++;
	}
	new_envp[len - 1] = NULL;
	free((*envp)[index]);
	free(*envp);
	*envp = new_envp;
}
