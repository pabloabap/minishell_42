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

static int	ft_str_expander(t_lexem *lex_list, t_data *data);
static void	ft_add_cmd_expansions(t_single_cmd *cmd_list, t_lexem **cmd_args);

/** Expansion de strings del atributo str de los t_single_cmd (equivalente
 *  a lex_list) y del atributo redirection (otra lex_list de redirecciones).
 * 
 * @param lex_list Puntero al primer elemento de la lista de lexemas.
 * @param cmd_list Puntero al primer elemento de la lista de t_single_cmd.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 *
 * @returns Estado de salida de la función. 
 **/
int	ft_expander(t_lexem *lex_list, t_single_cmd *cmd_list, t_data *data)
{
	t_lexem	*curr_cmd_args;

	curr_cmd_args = lex_list;
	if (ft_str_expander(lex_list, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (cmd_list)
	{
		ft_add_cmd_expansions(cmd_list, &curr_cmd_args);
		if (ft_str_expander(cmd_list->redirection, data) \
		== EXIT_FAILURE)
			return (EXIT_FAILURE);
		cmd_list = cmd_list->next;
	}
	return (EXIT_SUCCESS);
}

/** Funcion de apoyo para expandir el atributo str de estructuras t_lexem.
 * @param lex_list Puntero al primer elemento de la lista de lexemas.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 * 
 * @returns Estado de salida de la función. 
 **/
static int	ft_str_expander(t_lexem *lex_list, t_data *data)
{
	char	*exp_malloc;
	int		buffer;

	exp_malloc = NULL;
	while (lex_list)
	{
		if ((lex_list->token != HERE_DOC && lex_list->token != SINGLE_QUOTES \
			&& lex_list->token != COMPLEX_WORD \
			&& lex_list->token < SINGLE_QUO_RED) \
			&& ft_has_expansion(lex_list->str))
		{
			if ((ft_expansion_malloc(&exp_malloc, lex_list, \
				&buffer, data) == EXIT_FAILURE) || \
				(ft_fill_expansion(exp_malloc, lex_list, \
				&buffer, data) == EXIT_FAILURE) || \
				(ft_expansion_replace(exp_malloc, lex_list) == EXIT_FAILURE))
				return (EXIT_FAILURE);
			if (lex_list->token > SINGLE_QUO_RED)
				lex_list->token -= SINGLE_QUO_RED;
		}
		lex_list = lex_list->next;
	}
	return (EXIT_SUCCESS);
}

/** Actualiza los argumentos del comando con expansiones a su expansion.
 * 
 * @param cmd_list Puntero al comando a transformar.
 * @param cmd_args Puntero al primer arguento de la lista de comandos ya 
 * expandidos
 * 
 * @return Nada, actualiza los valores del comando y de cmd_args a través
 * de los punteros.
 */
static void	ft_add_cmd_expansions(t_single_cmd *cmd_list, t_lexem **cmd_args)
{
	int	i;
	int	args_count;

	i = 0;
	if ((*cmd_args) && (*cmd_args)->token == PIPE)
		(*cmd_args) = (*cmd_args)->next;
	args_count = cmd_len(*cmd_args);
	while (i < args_count)
	{
		cmd_list->str[i] = (*cmd_args)->str;
		(*cmd_args) = (*cmd_args)->next;
		i ++;
	}
}
