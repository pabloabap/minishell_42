/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:21:36 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/27 23:24:15 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

/*Estructures para almacenar info de los comandos de los lexemas*/

typedef struct s_single_cmd
{
	char				**str; //commando
//	char				(*build_func)(<param1Typte> <param1Name>, ...) BUILDING FUNCTION. PDTE DE DEFINIRLAS
	t_lexem				*redirection;
//	char				*hd_file_name; Pendiente de confirmar si lo necesitaremos
	int					pipe_fd[2];
	struct s_single_cmd	*prev; //Pointer to prev item of cmd list
	struct s_single_cmd	*next; //Pointer to next item of cmd list
}	t_single_cmd;

void			print_cmd(t_single_cmd *cmd_list);
int				ft_cmd_list_builder(t_lexem *lex_list, t_single_cmd **cmd);
t_single_cmd	*ft_lstcmd(t_single_cmd *lst);
void			ft_add_redirection(t_single_cmd *cmd, t_lexem *r);
int				grammar_checks(t_lexem *lex_list);
int				cmd_len(t_lexem *lex_list);
int				ft_lex_to_cmd(t_lexem **head_lex_list, t_single_cmd **cmd);
void			ft_redirection_quotes(t_lexem *lex_list);
int				ft_red_err(t_lexem *lex_list);
#endif
