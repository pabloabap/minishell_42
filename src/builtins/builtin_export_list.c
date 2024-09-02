/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguil-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:24:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/30 11:34:39 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Actualiza la lista de variables de entorno exportadas.
 * 
 * Esta función agrega una nueva variable de entorno a la lista exportada.
 * Si la lista aún no existe, la crea y agrega la variable.
 * En caso de que ocurra un error durante la adición, se imprime un mensaje
 * de error y se finaliza el programa.
 * 
 * @param env Estructura que contiene las variables de entorno.
 * @param str La variable de entorno a agregar en formato "NOMBRE=valor".
 */
void	update_export_list(t_env *env, char *str)
{
	char	**new_export_cpy;

	if (!env->export_cpy)
	{
		new_export_cpy = add_var(NULL, str);
		if (!new_export_cpy)
		{
			perror("Failure adding envirnomental variable");
			exit(EXIT_FAILURE);
		}
		env->export_cpy = new_export_cpy;
		return ;
	}
	new_export_cpy = add_var(env->export_cpy, str);
	if (!new_export_cpy)
	{
		perror("Failure adding envirnomental variable");
		exit(EXIT_FAILURE);
	}
	env->export_cpy = replace_envp(env->export_cpy, new_export_cpy);
}

/**
 * Imprime la lista de variables de entorno exportadas.
 * 
 * Esta función recorre y muestra todas las variables de la lista exportada,
 * excepto la cadena "export". Imprime cada variable en formato "declare -x NOMBRE=valor".
 * Si la lista export_cpy es NULL, se notifica al usuario.
 * 
 * @param env Estructura que contiene las variables de entorno.
 */
void	print_export_list(t_env *env)
{
	int	i;

	if (env->export_cpy == NULL)
	{
		printf("export_cpy is NULL\n");
		return ;
	}
	i = 0;
	while (env->export_cpy[i])
	{
		if (strcmp(env->export_cpy[i], "export") != 0)
			printf("declare -x %s\n", env->export_cpy[i]);
		i++;
	}
}
