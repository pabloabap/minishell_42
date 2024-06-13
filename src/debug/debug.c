/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:22:02 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:22:06 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Fichero con funciones para debugear, puede eliminarse al terminar

#include "../../include/minishell.h"

void print_cmd(t_single_cmd *cmd_list)
{
	t_lexem			*red;

	red = cmd_list->redirection;
	while (cmd_list)
	{
		while (red)
		{
			printf("STR: %s | TOKEN: %d\n", red->str, red->token);
		}
		cmd_list = cmd_list->next;
	}

}

/** Imprime los elementos de una lista de t_lexems.
 * 
 * @param lexems_list_iter Puntero al primer elemento de la lista
 * 			lexem para recorrerla.
 *
 * @returns Nada. Imprime cada elemento de la lista por stdout.
 **/
void	print_lexem_list(t_lexem *lexems_list_iter)
{
	int	i;

	i = 0;
	while (lexems_list_iter != NULL)
	{
		printf("ITEM %i - %s | TOKEN: %i\n", i++, lexems_list_iter->str, lexems_list_iter->token);
		lexems_list_iter = lexems_list_iter->next;
	}
}
