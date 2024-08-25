/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguil-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:03:21 by anguil-l          #+#    #+#             */
/*   Updated: 2024/08/23 13:03:27 by anguil-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Actualiza la variable de entorno `PWD` en `envp`.
void	update_pwd(t_env *env, char *pwd)
{
	int		i;
	char	*tmp;
	char	**envp;

	i = 0;
	envp = env->envp_cpy;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", pwd);
			if (tmp)
			{
				free(envp[i]);
				envp[i] = tmp;
			}
		}
		i++;
	}
}

// Actualiza la variable de entorno `OLDPWD` en `envp`.
void	update_oldpwd(t_env *env, char *old_pwd)
{
	int		i;
	char	*tmp;
	char	**envp;

	i = 0;
	envp = env->envp_cpy;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD=", 7) && old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", old_pwd);
			if (tmp)
			{
				free(envp[i]);
				envp[i] = tmp;
			}
		}
		i++;
	}
}

/**
 * Finds the index of the first occurrence of a character in a string.
 * @param str The string to search.
 * @param c The character to find.
 * @return The index of the character, or -1 if not found.
 */
int	find_char_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * Validates if a given environment variable is valid.
 * @param line The environment variable string.
 * @return 1 if valid, 0 otherwise.
 */
int	is_valid_environment_variable(const char *line)
{
	int			eq_idx;
	const char	*value;

	if (line == NULL || *line == '\0')
		return (0);
	eq_idx = find_char_index(line, '=');
	if (eq_idx == -1)
		return (0);
	value = &line[eq_idx + 1];
	if (value == NULL || *value == '\0')
		return (0);
	return (1);
}
