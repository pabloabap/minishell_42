/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:23:37 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:23:40 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_single_cmd	*ft_lstcmd(t_single_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_redirection(t_single_cmd *cmd, t_lexem *r)
{
	t_lexem *iter_redir;
	
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

int	grammar_checks(t_lexem *lex_list)
{
	if (!lex_list)
		return(EXIT_FAILURE);
	if (lex_list->token == PIPE)
		return (err_pipe_start(), EXIT_FAILURE);
	while (lex_list)
	{
		if ((lex_list->token >= IN_REDIR \
			&& lex_list->token <= APPEND_REDIR) \
			&& (!(lex_list->next) || \
			lex_list->next->token > DOUBLE_QUOTES))
			return (err_red_no_file(), EXIT_FAILURE);
		if (lex_list->token == PIPE && !(lex_list->next))
			return (err_pipe(), EXIT_FAILURE);
		lex_list = lex_list->next;
	}
	return (EXIT_SUCCESS);
}

int cmd_len(t_lexem *lex_list)
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
	printf("REDIRS: %i	|	CMDS: %i\n", red_count, cmd_count);
	return (cmd_count);
}


/** Función para gestionar los casos en los que los escrito en el 
 * terminal empiece con redirección.
 */
int ft_lex_to_cmd(t_lexem **lex_list, t_single_cmd **cmd)
{
	t_lexem *cmds_start;

	cmds_start = *lex_list;
	if (grammar_checks(*lex_list) == EXIT_SUCCESS)
	{
		while (cmds_start && cmds_start->token >= IN_REDIR \
		&& cmds_start->next->token <= DOUBLE_QUOTES)
			cmds_start = cmds_start->next->next;
		if (ft_cmd_list_builder (*lex_list, cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		*lex_list = cmds_start;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}