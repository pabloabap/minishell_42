/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:39:08 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/27 20:39:10 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** Junta el resultado de la expansión de las partes de una 
 * string compleja en el atrinbuto str de su lexema correspondiente.
 * 
 * @param src Array de strings expandidas de las partes de la string
 * compleja.
 * @param dst Punteor al puntero a la estructura en en la que queremos
 * actualizar el tributo str.
 * @param data Puntero a la estructura con información general del programa.
 * Necesaria para actualizar el valor `last_error` si procede.
 * 
 * @return Resultado de la ejecución.
 */
int	ft_join_parts(char **src, t_lexem **dst, t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	while (*(src + i))
	{
		tmp = (*dst)->str;
		if (!tmp)
			(*dst)->str = ft_strdup(src[i]);
		else
			(*dst)->str = ft_strjoin((*dst)->str, src[i]);
		if ((*dst)->str == NULL)
			return (err_malloc_fail(&(data->last_exit)), EXIT_FAILURE);
		if (tmp)
			free(tmp);
		free(src[i]);
		i++;
	}
	free(src);
	return (EXIT_SUCCESS);
}
