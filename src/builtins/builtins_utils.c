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

/*
 * Verifica si una variable de entorno especificada por `str` existe en 
 * el array `envp_cpy` de la estructura `env`. Si la variable existe, 
 * se actualiza con el nuevo valor de `str`. Si no existe, se añade al 
 * array.
 * @Parámetros:
 *  - env: puntero a la estructura `t_env` que contiene el array de entorno 
 *    `envp_cpy`.
 *  - str: cadena que representa la variable de entorno a buscar o actualizar.
 * @Devuelve:
 *  - 1 si la variable de entorno fue encontrada y actualizada, 
 *    0 si no fue encontrada.
 */
int	variable_exist(t_env *env, char *str)
{
	int	i;

	i = 0;
	while (env->envp_cpy[i])
	{
		if (ft_strncmp(env->envp_cpy[i], str,
				equal_sign(env->envp_cpy[i])) == 0)
		{
			free(env->envp_cpy[i]);
			env->envp_cpy[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
 * Actualiza la variable de entorno `PWD` en el array `envp_cpy` con el nuevo 
 * valor `pwd`. Si `PWD` ya existe en `envp_cpy`, se reemplaza su valor 
 * con el nuevo valor.
 * @Parámetros:
 *  - env: puntero a la estructura `t_env` que contiene el array de entorno 
 *    `envp_cpy`.
 *  - pwd: nueva cadena que representa el valor del directorio actual.
 */
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

/*
 * Actualiza la variable de entorno `OLDPWD` en el array `envp_cpy` con el 
 * nuevo valor `old_pwd`. Si `OLDPWD` ya existe en `envp_cpy`, se reemplaza 
 * su valor con el nuevo valor.
 * @Parámetros:
 *  - env: puntero a la estructura `t_env` que contiene el array de entorno 
 *    `envp_cpy`.
 *  - old_pwd: nueva cadena que representa el valor del directorio anterior.
 */
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

/*
 * Encuentra el índice de la primera ocurrencia de un carácter `c` en la 
 * cadena `str`.
 * @Parámetros:
 *  - str: cadena en la que se buscará el carácter.
 *  - c: carácter que se desea encontrar.
 * @Devuelve:
 *  - El índice del carácter en la cadena si se encuentra; 
 *    -1 si el carácter no se encuentra.
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
