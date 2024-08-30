/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:22:57 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:23:01 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** Comprueba si el caracter del argumento es algún tipo de espacio.
 * 
 * @return 1 si es espacio, 0 si no.
*/
int	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= 8 && c < 14));
}

/** Rellena los atributos str y token de las struct s_lexem de 
 * los lexemas especiales (pipes y redirecciones), en adelante ITEM.
 * 
 * @param str String de los caracteres que componen el ITEM .
 * @param lexem_item Puntero al puntero de la estrucura lexem para
 *         modificarlo desde la función.
 * @param token elemento de enum e_token que identifica el tipo 
 * 			de ITEM en el atributo token.
 *
 * @returns Número de caracteres que tiene el simbolo de redirección.
 **/
int	token_lex_fill(char *str, t_lexem **lexem_item, t_tokens token)
{
	int	chars;

	chars = ft_strlen(str);
	(*lexem_item)->str = str;
	(*lexem_item)->token = token;
	return (chars);
}

t_lexem	*ft_lstlex(t_lexem *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
