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
	if (cmd->redirection == NULL)
		cmd->redirection = r;
	else
	{
		while(cmd->redirection)
		{
			cmd->redirection->next = r;
			cmd->redirection->next->prev = cmd->redirection;
			cmd->redirection = cmd->redirection->next;
		}
	}
}

int	grammar_checks(t_lexem *lex_list)
{
	if (!lex_list)
		eturn(EXIT_FAILURE);
	if (lex_list->token == PIPE)
		return (err_pipe_start(), EXIT_FAILURE);
	while (lex_list)
	{
		if ((lex_list->str >= IN_REDIR \
			&& lex_list->str <= APPEND_REDIR) \
			&& (!(lex_list->next) || \
			lex_list->next->str > DOUBLE_QUOTES))
			return (err_red_no_file(), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}