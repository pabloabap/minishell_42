/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:07:38 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/06 21:24:01 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/** Detector de expansiones de minishell ( 
 * detecta variable de entorno, cuyo nombre 
 * solo puede conterner carácteres alfanuméricos o `_`, y $?).
 * Las expansiones que empieza por $ y van entre parentesis o
 * llaves no son reconocidas por minishell.
 * 
 * @param str String en el que comprobar si hay expansiones
 * a reconocer por minishell.  
 * 
 * @returns Número de expansiones que tiene un string.
 **/
int	ft_has_expansion(char *str)
{
	int	i;
	int	expansiones;

	i = 0;
	expansiones = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) \
		|| str[i + 1] == '_' || str[i + 1] == '?' ))
			expansiones ++;
		i ++;
	}
	return (expansiones);
}

/** Reemplazo la string antigua por la string expandida y
 * liberacion de la memoria reservada para la string antigua.
 * 
 * @param exp_malloc String expandida.  
 * @param lex_list Estructura que contiene el string sin expandir.  
 * 
 * @returns Resultado de la funcion.
 **/
int	ft_expansion_replace(char *exp_malloc, t_lexem *lex_list)
{
	free(lex_list->str);
	if (!exp_malloc[0])
	{
		lex_list->str = NULL;
		free(exp_malloc);
	}
	else
		lex_list->str = exp_malloc;
	return (EXIT_SUCCESS);
}
