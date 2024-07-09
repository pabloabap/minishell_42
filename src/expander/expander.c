/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:07:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/06 21:07:26 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_str_expander(t_lexem *lex_list, int exit);

/** Expansion de strings del atributo str de los t_single_cmd (equivalente
 *  a lex_list) y del atributo redirection (otra lex_list de redirecciones).
 * 
 * @param lex_list Puntero al primer elemento de la lista de lexemas.
 * @param cmd_list Puntero al primer elemento de la lista de t_single_cmd.
 *
 * @returns Estado de salida de la función. 
 **/
int	ft_expander(t_lexem *lex_list, t_single_cmd *cmd_list, int exit)
{
	printf("___EXPANDIENDO STRS___\n");
	if (ft_str_expander(lex_list, exit) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("___EXPANDIENDO REDIRS___\n");
	while (cmd_list)
	{
		if (ft_str_expander(cmd_list->redirection, exit) \
		== EXIT_FAILURE)
			return (EXIT_FAILURE);
		cmd_list = cmd_list->next;
	}
	return (EXIT_SUCCESS);
}

/** Funcion de apoyo para expandir el atributo str de estructuras t_lexem.
 * @param lex_list Puntero al primer elemento de la lista de lexemas.
 * 
 * @returns Estado de salida de la función. 
 **/
static int	ft_str_expander(t_lexem *lex_list, int exit)
{
	char	*exp_malloc;
	int		buffer;

	exp_malloc = NULL;
	while (lex_list)
	{
		if ((lex_list->token != HERE_DOC && lex_list->token != SINGLE_QUOTES \
			&& lex_list->token < SINGLE_QUO_RED) \
			&& ft_has_expansion(lex_list->str))
		{
			if ((ft_expansion_malloc(&exp_malloc, lex_list, \
				&buffer, exit) == EXIT_FAILURE) || \
				(ft_fill_expansion(exp_malloc, lex_list, \
				&buffer, exit) == EXIT_FAILURE) || \
				(ft_expansion_replace(exp_malloc, lex_list) == EXIT_FAILURE))
				return (EXIT_FAILURE);
			if (lex_list->token > SINGLE_QUO_RED)
				lex_list->token -= SINGLE_QUO_RED;
		}
		lex_list = lex_list->next;
		printf("_____\n");
	}
	return (EXIT_SUCCESS);
}
