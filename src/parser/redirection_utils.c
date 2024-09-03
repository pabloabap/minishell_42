/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:27:40 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:27:47 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** Al juntar la struct t_lexem de una redireccion
 * con la siguiente struct que continen el destino de la redireccion
 * se pierde el tipo de str del destino, pero es necesario saberlo
 * futuras expansiones y comportamientos especialesd el HEREDOC.
 * 
 * El HEREDOC si se escribe una $VAR_NAME entre comillas como delimitador,
 * en el contenido del fichero no se expandiran las $VAR_NAME.
 *  
 * En el resto de redirecciones las $VAR_NAME entre comillas simple
 * tampoco se expanden.
 * 
 * @param lex_list Puntero a `t_lexem struct` que contine la redirección.
 */
void	ft_redirection_quotes(t_lexem *lex_list)
{
	if (lex_list->next->token == SINGLE_QUOTES || \
		(lex_list->token == HERE_DOC \
		&& (lex_list->next->token == DOUBLE_QUOTES || \
		lex_list->next->token == SINGLE_QUOTES)))
		lex_list->token += SINGLE_QUO_RED;
}
