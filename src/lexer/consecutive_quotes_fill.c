/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consecutive_quotes_fill.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:39:19 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/27 20:39:23 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_words_join(char **words_array);
static int	ft_count_chars(char **words_array);

/** Realiza operaciones necesarias en caso de que un string
 * entrecomillado tenga comillas intermedias para obtener el string deseado.
 * 
 * @param lexem_item Estructura que contiene la información del lexema.
 * @param quote_tyoe Caracter del tipo de comilla que abre la string.
 * 
 * @return Nada. Modifica el string almacenado en el lexema mediante puteros. 
*/
void	ft_str_lex_check(t_lexem **lexem_item, char quote_type)
{
	char	**words_array;

	words_array = ft_consecutive_split((*lexem_item)->str, quote_type);
	if (words_array)
	{
		if (words_array[1] != NULL)
		{
			free((*lexem_item)->str);
			(*lexem_item)->str = ft_words_join(words_array);
		}
		free (words_array);
	}
}

/** Concatena los strings de un array de strings.
 * 
 * @param words_array Array de strings a concatenar.
 * 
 * @return String resultante de la concatenación. 
*/
static char	*ft_words_join(char **words_array)
{
	int		i;
	int		n_chars;
	char	*final_str;

	i = 0;
	n_chars = ft_count_chars(words_array) + 1;
	final_str = (char *)ft_calloc(n_chars, sizeof(char));
	if (final_str == NULL)
		err_malloc_fail(&i);
	else
	{
		while (words_array && words_array[i])
		{
			ft_strlcat(final_str, words_array[i], n_chars * sizeof(char));
			if (words_array[i][0] != '\0')
				free (words_array[i]);
			i ++;
		}
	}
	return (final_str);
}

/** Cuenta el número de caracteres en un array de strings.
 * 
 * @param words_array Array de strings.
 * 
 * @return Total de caracteres en los strigns.
*/
static int	ft_count_chars(char **words_array)
{
	int	i;
	int	j;
	int	n_chars;

	i = 0;
	j = 0;
	n_chars = 0;
	while (words_array && words_array[i])
	{
		while (words_array[i][j])
			j ++;
		n_chars += j;
		j = 0;
		i ++;
	}
	return (n_chars);
}
