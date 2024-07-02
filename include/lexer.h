/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:21:05 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:21:12 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

/*Enumeración de posibles tokens a utilizar*/
typedef enum e_tokens
{
	WORD			,
	SINGLE_QUOTES	,
	DOUBLE_QUOTES	,
	PIPE			,
	IN_REDIR		,
	OUT_REDIR		,
	HERE_DOC		,
	APPEND_REDIR
}	t_tokens;

/*Estructures para almacenar info de los lexemas*/
typedef struct s_lexem
{
	char			*str; //word or token
	int				token; //classify the item
	struct s_lexem	*prev; //Pointer to previous item of lexer list
	struct s_lexem	*next; //Pointer to next item of lexer list    
}	t_lexem;

int		token_lex_fill(char *str, t_lexem **lexem_item, t_tokens token);
void	print_lexem_list(t_lexem *lexems_list_iter);
int		lexer(char *str, t_lexem **head_lex_list);
t_lexem	*ft_lstlex(t_lexem *lst);

#endif
