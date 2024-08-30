/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:24:52 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:24:57 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**dup_envp(char **envp);

/** Inicializa la estructura en la que centralizaremos todos los elemenetos que
 * usan memoría dinámica para liberarlos facilmente a la finalización de una 
 * ejecución. También configura el gestor de señales del programa principal.
 * 
 * @param data Estructura que contiene los elementos con memoria dinámica del
 * programa
 * @param envp Doble puntero a las variables de entorno recibidas al inicio
 * del programa.
 * 
 * @return Resultado de la ejecución de la función.
*/
int	init_data(t_data **data, char **envp)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
		return (perror("-minishell: t_data malloc fails"), EXIT_FAILURE);
	(*data)->head_lex_list = NULL;
	(*data)->head_cmd_list = NULL;
	(*data)->input = NULL;
	(*data)->env = malloc(sizeof(t_env));
	if (!(*data)->env)
		return (EXIT_FAILURE);
	(*data)->env->envp_cpy = dup_envp(envp);
	if (!(*data)->env->envp_cpy)
		return (free((*data)->env), free(*data), EXIT_FAILURE);
	(*data)->env->export_cpy = dup_envp(envp);
	if (!(*data)->env->export_cpy)
	{
		free((*data)->env->envp_cpy);
		free((*data)->env);
		free(*data);
		return (EXIT_FAILURE);
	}
	(*data)->last_exit = 0;
	wait_signal(1);
	return (EXIT_SUCCESS);
}

static char	**dup_envp(char **envp)
{
	int		i;
	char	**envp_copy;

	i = 0;
	while (envp[i])
		i++;
	envp_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			while (i-- > 0)
				free(envp_copy[i]);
			free(envp_copy);
			return (NULL);
		}
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}
