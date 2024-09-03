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
void update_export_list(t_env *env, char *str)
{
	char	**new_export_cpy;
	int		i;
	char	*equal_sign;
	char	*name;
	size_t	name_len;

	if (!env->export_cpy)
	{
		new_export_cpy = add_var(NULL, str);
		if (!new_export_cpy)
		{
			perror("Failure adding environmental variable");
			exit(EXIT_FAILURE);
		}
		env->export_cpy = new_export_cpy;
		return ;
	}
	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
	{
		name_len = equal_sign - str;
		name = ft_substr(str, 0, name_len);
		if (!name)
		{
			perror("Failure duplicating string");
			exit(EXIT_FAILURE);
		}
		for (i = 0; env->export_cpy[i] != NULL; i++)
		{
			if (ft_strncmp(env->export_cpy[i], name, name_len) == 0 && 
				(env->export_cpy[i][name_len] == '=' || env->export_cpy[i][name_len] == '\0'))
			{
				free(env->export_cpy[i]);
				env->export_cpy[i] = ft_strdup(str);
				if (!env->export_cpy[i])
				{
					perror("Failure updating environmental variable");
					exit(EXIT_FAILURE);
				}
				free(name);
				return ;
			}
		}
		free(name);
	}
	else
	{
		for (i = 0; env->export_cpy[i] != NULL; i++)
		{
			if (ft_strncmp(env->export_cpy[i], str, ft_strlen(env->export_cpy[i])) == 0)
				return ;
		}	
	}
	new_export_cpy = add_var(env->export_cpy, str);
	if (!new_export_cpy)
	{
		perror("Failure adding environmental variable");
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
void print_export_list(t_env *env)
{
	int		i;
	char	*entry;
	char	*equal_sign;
	char	*name;
	char	*value;

	if (env->export_cpy == NULL)
	{
		printf("export_cpy is NULL\n");
		return ;
	}
	i = 0;
	while (env->export_cpy[i])
	{
	    if (ft_strncmp(env->export_cpy[i], "export", 6) != 0)
	    {
	        entry = env->export_cpy[i];
	        equal_sign = ft_strchr(entry, '=');
	        if (equal_sign != NULL)
	        {
	            *equal_sign = '\0';
	            name = entry;
	            value = equal_sign + 1;
	            if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
	            {
	                char    *escaped_value;
	                char    *src;
	                char    *dst;
	                escaped_value = malloc(ft_strlen(value) * 2 + 1);
	                if (!escaped_value)
	                {
	                    perror("Failure allocating memory");
	                    exit(EXIT_FAILURE);
	                }
	                src = value;
	                dst = escaped_value;
	                while (*src)
	                {
	                    if (*src == '"')
	                        *dst++ = '\\';
	                    *dst++ = *src++;
	                }
	                *dst = '\0';
	                printf("declare -x %s=\"%s\"\n", name, escaped_value);
	                free(escaped_value);
	            }
	            else
	                printf("declare -x %s=\"%s\"\n", name, value);
	            *equal_sign = '=';
	        }
	        else
	            printf("declare -x %s\n", entry);
	    }
	    i++;
	}
}
