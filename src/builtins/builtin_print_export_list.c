/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_export_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguil-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:24:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/30 11:34:39 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_null_export_copy(t_env *env);
static void	ft_double_quotes_export_write(char *value, char	*name, \
	char *equal_sign);

/**
 * Imprime la lista de variables de entorno exportadas.
 * 
 * Esta función recorre y muestra todas las variables de la lista exportada,
 * excepto la cadena "export". Imprime cada variable en formato 
 * "declare -x NOMBRE=valor". Si la lista export_cpy es NULL, se notifica al
 * usuario. 
 * @param env Estructura que contiene las variables de entorno.
 */
void	print_export_list(t_env *env)
{
	int		i;
	char	*entry;
	char	*equal_sign;

	i = ft_null_export_copy(env);
	while (i >= 0 && env->export_cpy[i])
	{
		if (ft_strncmp(env->export_cpy[i], "export", 6) != 0)
		{
			entry = env->export_cpy[i];
			equal_sign = ft_strchr(entry, '=');
			if (equal_sign != NULL)
			{
				*equal_sign = '\0';
				ft_double_quotes_export_write((equal_sign + 1), entry, \
					equal_sign);
			}
			else
				printf("declare -x %s\n", entry);
		}
		i++;
	}
}

/**
 * Comprueba si export_cpy es NULL para imprimir un mensaje informativo.
 * @return Devuelve -1 en caso de que sea NULL o 0. Esto permite ahorrar
 * lineas en la funcion principal y que solo se entre en el bucle de 
 * operaciones cuando la salida de esta función sea 0.
 */
static int	ft_null_export_copy(t_env *env)
{
	if (env->export_cpy == NULL)
	{
		printf("export_cpy is NULL\n");
		return (-1);
	}
	return (0);
}

/** 
 * Comprueba si el valor de una variable tiene comillas para 
 * convertirlas en \" para la lista de export. En caso contrario
 * imprime el valor de la variable tal y como es.
 */
static void	ft_double_quotes_export_write(char *value, char	*name, \
	char	*equal_sign)
{
	char	*escaped_value;
	char	*src;
	char	*dst;

	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
	{
		escaped_value = malloc(ft_strlen(value) * 2 + 1);
		if (!escaped_value)
			return (perror("Failure allocating memory"), \
				exit(EXIT_FAILURE));
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
	equal_sign[0] = '=';
}
