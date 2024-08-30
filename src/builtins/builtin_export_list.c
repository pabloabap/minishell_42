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

void	update_export_list(t_env *env, char *str)
{
	char	**new_export_cpy;

	if (!env->export_cpy)
	{
		new_export_cpy = add_var(NULL, str);
		if (!new_export_cpy)
		{
			perror("Error al agregar variable de entorno");
			exit(EXIT_FAILURE);
		}
		env->export_cpy = new_export_cpy;
		return ;
	}
	new_export_cpy = add_var(env->export_cpy, str);
	if (!new_export_cpy)
	{
		perror("Error al agregar variable de entorno");
		exit(EXIT_FAILURE);
	}
	env->export_cpy = replace_envp(env->export_cpy, new_export_cpy);
}

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
