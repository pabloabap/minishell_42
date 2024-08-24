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
static void	update_pwd(t_env *env, char *pwd)
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
static void	update_oldpwd(t_env *env, char *old_pwd)
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

// Actualiza la variable de entorno `PWD` y `OLDPWD` en `envp`.
void	add_path_to_env(t_env *env, char *pwd, char *old_pwd)
{
	update_pwd(env, pwd);
	update_oldpwd(env, old_pwd);
}
