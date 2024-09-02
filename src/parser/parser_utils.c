/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:23:37 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/26 10:43:40 by anguil-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** Devuelve un puntero a la última estrucutura de una  lista de estructuras 
 * `t_single_cmd`.
 * 
 * @param lst Punteoro a cualquier elemento de la lista.
 * 
 * @return Puntero al último elemento de la lista.
 */
t_single_cmd	*ft_lstcmd(t_single_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/** Añade redirección `r` a la lista de redirecciones de `cmd`.
 * 
 * @param cmd Puntero estructura del comando en el que se quiere trabajar.
 * @param r Puntero a estructura lexema que contiene la redirección.
 * 
 * @return Nada, añade la redirección al final de la lista de redirecciones
 * del commando mediante punteros.
 */
void	ft_add_redirection(t_single_cmd *cmd, t_lexem *r)
{
	t_lexem	*iter_redir;

	iter_redir = cmd->redirection;
	if (cmd->redirection == NULL)
		cmd->redirection = r;
	else
	{
		iter_redir = ft_lstlex(cmd->redirection);
		iter_redir->next = r;
		r->prev = iter_redir;
	}
}

/** Comprueba si, tras lexear el input, el texto recibido tiene coerencia para
 * ser procesado (que no empiece por PIPE y que las REDIRECCIONES y PIPES 
 * vengan acompañados de un nombre de fichero o comando).
 * 
 * @param lex_list Puntero al comienzo de una lista de lexemas.
 * 
 * @return Resultado de la ejecución.
 */
int	grammar_checks(t_lexem *lex_list)
{
	if (!lex_list)
		return (EXIT_FAILURE);
	if (lex_list->token == PIPE)
		return (err_pipe_start(), EXIT_FAILURE);
	while (lex_list)
	{
		if ((lex_list->token >= IN_REDIR \
			&& lex_list->token <= HERE_DOC) \
			&& (!(lex_list->next) || \
			lex_list->next->token > DOUBLE_QUOTES))
			return (err_red_no_file(), EXIT_FAILURE);
		if (lex_list->token == PIPE && !(lex_list->next))
			return (err_pipe(), EXIT_FAILURE);
		lex_list = lex_list->next;
	}
	return (EXIT_SUCCESS);
}

/** Conteo de nombre del comando y sus argumentos.
 * 
 * @param lex_list Puntero a la estructura que contiene el nombre del comando
 * en unalista de lexemas para realizar el recuento.
 * 
 * @return Recuento del nombre del comando y sus argumentos.
 */
int	cmd_len(t_lexem *lex_list)
{
	int	red_count;
	int	cmd_count;

	red_count = 0;
	cmd_count = 0;
	while (lex_list && lex_list->token != PIPE)
	{
		if (lex_list->token > DOUBLE_QUOTES)
		{
			red_count ++;
			lex_list = lex_list->next->next;
		}
		else
		{
			cmd_count ++;
			lex_list = lex_list->next;
		}
	}
	return (cmd_count);
}

/** Función para gestionar los casos en los que lo escrito en el 
 * terminal empiece con redirección.
 */
int	ft_lex_to_cmd(t_lexem **lex_list, t_single_cmd **cmd, int *err_n)
{
	t_lexem	*cmds_start;

	cmds_start = *lex_list;
	if (grammar_checks(*lex_list) == EXIT_SUCCESS)
	{
		while (cmds_start && cmds_start->token >= IN_REDIR \
		&& cmds_start->next->token <= DOUBLE_QUOTES)
			cmds_start = cmds_start->next->next;
		if (ft_cmd_list_builder (*lex_list, cmd, err_n) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		*lex_list = cmds_start;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
