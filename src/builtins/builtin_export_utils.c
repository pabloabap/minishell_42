/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguil-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:03:49 by anguil-l          #+#    #+#             */
/*   Updated: 2024/08/23 13:03:55 by anguil-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Libera la memoria asignada para un arreglo de cadenas.
 * 
 * Itera a través del arreglo, libera cada cadena, y luego
 * libera el arreglo en sí.
 * 
 * @param arr El arreglo de cadenas a liberar.
 * @param len El número de elementos en el arreglo.
 * @return NULL.
 */
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

/**
 * Encuentra el índice del primer carácter '=' en una cadena.
 * 
 * @param str La cadena en la que buscar.
 * @return El índice del carácter '=', o -1 si no se encuentra.
 */
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

/**
 * Elimina todas las ocurrencias de un carácter de comilla específico de una 
 * cadena.
 * 
 * Esta función modifica la cadena en el lugar y ajusta su longitud.
 * 
 * @param str La cadena de la cual eliminar las comillas.
 * @param quote_char El carácter de comilla a eliminar.
 */
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

/**
 * Verifica si una cadena es un identificador válido para una variable de 
 * entorno.
 * 
 * Un identificador válido debe comenzar con una letra y puede contener letras,
 * dígitos y guiones bajos.
 * 
 * @param str La cadena a verificar.
 * @return 1 si la cadena es un identificador válido, 0 en caso contrario.
 */
int	is_valid_identifier(const char *str)
{
	int	i;

	if (str == NULL || (!ft_isalpha(str[0]) && str[0] != '_'))
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

/**
 * Maneja los errores relacionados con identificadores no válidos de variables
 * de entorno.  
 * Imprime un mensaje de error si la cadena proporcionada no es un 
 * identificador válido.
 * 
 * @param str La cadena a verificar e imprimir errores.
 */
void	handle_export_errors(char *str, int *last_exit)
{
	if (!is_valid_identifier(str))
	{
		*last_exit = 1;
		ft_putstr_fd("-minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
}
