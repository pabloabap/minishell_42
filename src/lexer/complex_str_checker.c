/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_str_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:38:57 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/27 20:39:01 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_move_to_close(char *str, int *i, char character);
static void	ft_move_to_delimiter(char *str, int *i, int *counter);

/** Comprueba si el usuario ha pasado algun string complejo (string
 * con texto sin entrecomillar, comillado simple y comillado doble).
 * 
 *  @param str String recibido por el usuario.
 * 
 * @return En caso de comillas no cerradas -1, en los otros casos
 * devuelve el número de partes de la string de cada tipo
 * (quotes[0] cuenta partes sin entrecomillar, quotes[1]
 * partes entre comillas simples y quotes[2] partes entre
 * comillas dobles).
 */
int	ft_check_complex_str(char	*str)
{
	int	quotes[3];
	int	i;

	quotes[0] = 0;
	quotes[1] = 0;
	quotes[2] = 0;
	i = 0;
	if (ft_strchr("|<>", str[i]) != NULL && str[i] != '\0')
		return (1);
	while (str && str[i] != '\0' && !ft_is_whitespace(str[i]) && \
		ft_strchr("|<>", str[i]) == NULL)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (EXIT_FAILURE == ft_move_to_close(str, &i, str[i]))
				return (-1);
			quotes[(str[i] == '"') + 1]++;
			i++;
		}
		else
			ft_move_to_delimiter(str, &i, &quotes[0]);
	}
	return (quotes[0] + quotes[1] + quotes[2]);
}

/** Incrementa el contador i las posiciones necesarias hasta
 * que encuetre el siguiente `character` en la string o devuelve error.
 * 
 * @param str String recibida por el usuario.
 * @param character Caracter de cierre a buscar.
 * 
 * @return Resultado de la ejecución.
 */
static int	ft_move_to_close(char *str, int *i, char character)
{
	char	*end_char;

	end_char = ft_strchr((str + *i + 1), character);
	if (end_char == NULL)
	{
		ft_putendl_fd("-minishell: syntax error: quotes not closed", \
		STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		*i += end_char - (str + *i);
	return (EXIT_SUCCESS);
}

/** Incrementa el contador i las posiciones necesarias hasta
 * el delimitador de una cadena sin entrecomillar (final de string  '\0',
 * espacios o simbolos de PIPE o redirección).
 * 
 * @param str String recibida por el usuario.
 * @param character Caracter de cierre a buscar.
 * 
 * @return No retorna nada. Acutaliza el indice (i) y aumenta en 1
 * el contador, `counter`, de partes sin entrecomillar. 
 */
static void	ft_move_to_delimiter(char *str, int *i, int *counter)
{
	while (str && str[*i] != '\0' && !ft_is_whitespace(str[*i]) && \
		ft_strchr("|<>'\"", str[*i]) == NULL)
		*i += 1;
	*counter += 1;
}
