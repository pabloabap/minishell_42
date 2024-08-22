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
/*
#include "../../include/minishell.h"

char	**replace_envp(char **old_envp, char **new_envp);

int	equal_sign(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (str == NULL || !ft_isalpha(str[0]))
		return (0);
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	delete_quotes(char *str, char quote_char)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != quote_char)
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

void	handle_export_errors(char *str)
{
	if (!is_valid_identifier(str))
		printf("export: '%s': not a valid identifier\n", str);
}

static void	process_and_update_var(char *str, t_env *env)
{
	int		eq_idx;
	char	**new_envp;

	eq_idx = equal_sign(str);
	if (eq_idx != -1 && str[eq_idx + 1] == '\"')
		delete_quotes(&str[eq_idx + 1], '\"');
	if (is_valid_identifier(str))
	{
		if (!variable_exist(env, str))
		{
			new_envp = add_var(env->envp_cpy, str);
			if (new_envp == NULL)
			{
				perror("Error al agregar variable de entorno");
				return ;
			}
			env->envp_cpy = replace_envp(env->envp_cpy, new_envp);
		}
	}
	else
		handle_export_errors(str);
}

void	update_environment(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		process_and_update_var(args[i], env);
		i++;
	}
}

void	builtin_export(char **args, t_env *env)
{
	if (args[1] == NULL)
	{
		builtin_env(args, env);
		return ;
	}
	update_environment(args, env);
}

char	**free_arr(char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

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
*/
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
 * 
 * Frees the memory occupied by the old environment array 
 * and returns the new array.
 * 
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

/**
 * Processes a variable string and updates the environment if necessary.
 * 
 * This function checks if the variable string is valid, removes quotes if
 * necessary, and updates the environment if the variable does not already exist.
 * 
 * @param str The variable string to process.
 * @param env The environment structure to update.
 */
static void	process_and_update_var(char *str, t_env *env)
{
	int		eq_idx;
	char	**new_envp;

	eq_idx = equal_sign(str);
	if (eq_idx != -1 && str[eq_idx + 1] == '\"')
		delete_quotes(&str[eq_idx + 1], '\"');
	if (is_valid_identifier(str))
	{
		if (!variable_exist(env, str))
		{
			new_envp = add_var(env->envp_cpy, str);
			if (new_envp == NULL)
			{
				perror("Error al agregar variable de entorno");
				return ;
			}
			env->envp_cpy = replace_envp(env->envp_cpy, new_envp);
		}
	}
	else
		handle_export_errors(str);
}

/**
 * Updates the environment with variables specified in the arguments.
 * 
 * Iterates over the arguments, starting from the second argument, and
 * processes each one to update the environment.
 * 
 * @param args The arguments containing variable strings.
 * @param env The environment structure to update.
 */
void	update_environment(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		process_and_update_var(args[i], env);
		i++;
	}
}

/**
 * Implements the 'export' command to update environment variables.
 * 
 * If no additional arguments are provided, it lists the current environment.
 * Otherwise, it updates the environment with the provided variable strings.
 * 
 * @param args The arguments passed to the 'export' command.
 * @param env The environment structure to modify.
 */
void	builtin_export(char **args, t_env *env)
{
	if (args[1] == NULL)
	{
		builtin_env(args, env);
		return ;
	}
	update_environment(args, env);
}

/**
 * Adds a new variable to an array of environment variables.
 * 
 * Allocates memory for a new array that includes the additional variable and
 * copies all existing variables to this new array.
 * 
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
