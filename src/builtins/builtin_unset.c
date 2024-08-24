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

// Encuentra el índice del signo '=' en la variable
int	find_env_var_index(char **envp, const char *var)
{
	int		i;
	int		eq_idx;
	char	*var_name;

	eq_idx = equal_sign(var);
	if (eq_idx == -1)
		return (-1);
	var_name = strndup(var, eq_idx);
	if (!var_name)
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], var_name, eq_idx) == 0 && envp[i][eq_idx] == '=')
		{
			free(var_name);
			return (i);
		}
		i++;
	}
	free(var_name);
	return (-1);
}

// Elimina una variable del array de entorno
void	remove_env_var(char ***envp, int index)
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

// Implementación de builtin_unset
void	builtin_unset(char **args, t_env *env)
{
	int		i;
	int		index;

	i = 1;
	while (args[i])
	{
		index = find_env_var_index(env->envp_cpy, args[i]);
		if (index != -1)
			remove_env_var(&env->envp_cpy, index);
		else
			printf("unset: '%s': not found\n", args[i]);
		i++;
	}
}
