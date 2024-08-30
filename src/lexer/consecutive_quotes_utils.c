/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consecutive_quotes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:40:06 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/27 20:40:10 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** Cuenta el número de comillas consecutivas antes de un espacio
 * para comprobar si lo entrecomillado tiene comillas pares (input correcto)
 * o impares (input erroneo). 
 * 
 * @param end_quote Puntero al primer cierre encontrado de una
 *  comilla.
 * @param quote_type Caracter del tipo de comilla que ha abierto
 * la string entrecomillada.
 * 
 * @return Nada. En caso de que el input sea erroneo
 * convierte `end_quote` en `NULL` para informar al lexer del error.
 * En caso de que el str entrecomillado acabe con final de str o
 * espacio en blanco también se ajusta `end_quote` para que apunte 
 * al caracter anterior
 * 
*/
void	ft_consecutive_quotes(char **end_quote, char quote_type)
{
	int	i;
	int	quotes_counter;

	i = 0;
	quotes_counter = 1;
	while (*end_quote && (*end_quote)[i] != '\0' \
		&& !ft_is_whitespace((*end_quote)[i]))
	{
		if ((*end_quote)[i] == quote_type)
			quotes_counter ++;
		i ++;
	}
	if (quotes_counter % 2 != 0)
		*end_quote = NULL;
	else if ((*end_quote)[i] == '\0' || ft_is_whitespace((*end_quote)[i]))
		*end_quote = (*end_quote + i - 1);
}
