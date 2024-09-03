/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_update_export_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguil-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:24:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/30 11:34:39 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_fill_empty_export_cpy(t_env *env, char ***new_export_cpy, \
	char *str);
static int	ft_update_var_without_value(t_env *env, char *str, \
	size_t name_len);

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
	int		i;
	char	*equal_sign;

	i = 0;
	if (1 == ft_fill_empty_export_cpy(env, &new_export_cpy, str))
		return ;
	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL \
		&& 1 == ft_update_var_without_value(env, str, equal_sign - str))
		return ;
	else
	{
		while (env->export_cpy[i] != NULL)
		{
			if (ft_strncmp(env->export_cpy[i], str, \
				ft_strlen(env->export_cpy[i])) == 0)
				return ;
			i++;
		}
	}
	new_export_cpy = add_var(env->export_cpy, str);
	if (!new_export_cpy)
		return (err_malloc_fail(NULL), exit(EXIT_FAILURE));
	env->export_cpy = replace_envp(env->export_cpy, new_export_cpy);
}

static int	ft_fill_empty_export_cpy(t_env *env, char ***new_export_cpy, \
	char *str)
{
	if (!env->export_cpy)
	{
		*new_export_cpy = add_var(NULL, str);
		if (!(*new_export_cpy))
			return (perror("Failure adding environmental variable"), \
				exit(EXIT_FAILURE), 0);
		env->export_cpy = *new_export_cpy;
		return (1);
	}
	return (0);
}

static int	ft_update_var_without_value(t_env *env, char *str, size_t name_len)
{
	int		i;
	char	*name;

	i = 0;
	name = ft_substr(str, 0, name_len);
	if (!name)
		return (perror("Failure duplicating string"), \
			exit(EXIT_FAILURE), 0);
	while (env->export_cpy[i] != NULL)
	{
		if (ft_strncmp(env->export_cpy[i], name, name_len) == 0 \
			&& (env->export_cpy[i][name_len] == '=' \
				|| env->export_cpy[i][name_len] == '\0'))
		{
			free(env->export_cpy[i]);
			env->export_cpy[i] = ft_strdup(str);
			if (!env->export_cpy[i])
				return (err_malloc_fail(NULL), exit(EXIT_FAILURE), 0);
			return (free(name), 1);
		}
		i++;
	}
	return (free(name), 0);
}
