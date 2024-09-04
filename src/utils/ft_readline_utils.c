/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:08:11 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/09/04 14:08:16 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_run_to_close_or_end(char *str, int *i);

/** Itera sobre caracteres que no generar una exapnsión.
 * En caso de encontrar comillas simples no cerradas se
 * para la ejecución con EXIT_FAILURE.
 * 
 * @param str String recibida con readline.
 * @param i	Puntero al index de iteración de caracteres.
 * 
 * @return Resultado de la ejecución.
*/
int	ft_jump_irrelevant_character(char *str, int *i)
{
	int	in_d_quotes;

	in_d_quotes = 0;
	while (str[*i] && str[*i] != '$')
	{
		if (in_d_quotes == 0 && str[*i] == '\'')
		{
			if (EXIT_FAILURE == ft_run_to_close_or_end(str, i))
				return (EXIT_FAILURE);
		}
		if (str[*i] == '"')
			in_d_quotes = !in_d_quotes;
		*i = *i + 1;
	}
	return (EXIT_SUCCESS);
}

/** Recorre input hasta el cierre de comillas simples y actualiza `i` 
 * al caracter siguiente al cierre o error si no hay cierre.
 * 
 * @param str String recibida con readline.
 * @param i	Puntero al index de iteración de caracteres.
 * 
 * @return Resultado de la ejecución.
 */
static int	ft_run_to_close_or_end(char *str, int *i)
{
	*i = *i + 1;
	while (str[*i] && str[*i] != '\'')
		*i = *i + 1;
	if (!str[*i])
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
