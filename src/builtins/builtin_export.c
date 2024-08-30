/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:24:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/22 20:34:39 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/**
 * Replaces an old environment array with a new one.
 * Frees the memory occupied by the old environment array 
 * and returns the new array.
 * @param old_envp The old environment array to free.
 * @param new_envp The new environment array to return.
 * @return The new environment array.
 */

char	**replace_envp(char **old_envp, char **new_envp)
{
	int	i;

	i = 0;
	if (old_envp)
	{
		while (old_envp[i])
			free(old_envp[i++]);
		free(old_envp);
	}
	return (new_envp);
}

static void	ft_update_var(char *str, t_env *env, int eq_idx)
{
	char	**new_envp;

	if (eq_idx == -1)
		update_export_list(env, str);
	else
	{
		if (!variable_exist(env, str))
		{
			new_envp = add_var(env->envp_cpy, str);
			if (new_envp == NULL)
			{
				perror("Failure adding envirnomental variable");
				return ;
			}
			env->envp_cpy = replace_envp(env->envp_cpy, new_envp);
		}
		update_export_list(env, str);
	}
}

static void	process_and_update_var(char *str, t_env *env)
{
	int	eq_idx;

	eq_idx = equal_sign(str);
	if (!is_valid_environment_variable(str))
		return ;
	if (eq_idx != -1 && str[eq_idx + 1] == '\"')
		delete_quotes(&str[eq_idx + 1], '\"');
	if (is_valid_identifier(str))
		ft_update_var(str, env, eq_idx);
	else
		handle_export_errors(str);
}

void	builtin_export(char **args, t_env *env, int *last_exit)
{
	int	i;

	i = 0 * *last_exit;
	if (!args[1])
		print_export_list(env);
	else
	{
		while (args[i])
		{
			process_and_update_var(args[i], env);
			i++;
		}
	}
}

/**
 * Adds a new variable to an array of environment variables.
 * Allocates memory for a new array that includes the additional variable and
 * copies all existing variables to this new array.
 * @param arr The existing array of environment variables.
 * @param str The new variable to add.
 * @return The new array including the new variable, or NULL on failure.
 */

char	**add_var(char **arr, char *str)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	while (arr[len] != NULL)
		len++;
	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			return (free_arr(new_arr, i));
		i++;
	}
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		return (free_arr(new_arr, i));
	new_arr[i + 1] = NULL;
	return (new_arr);
}
