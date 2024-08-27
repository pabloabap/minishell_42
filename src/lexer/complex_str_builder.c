/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_str_builder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:38:47 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/27 20:38:51 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_expand_parts(char **str, char **dst, t_data *data);
static int	ft_build_squote_part(char **str, char **dst, int *error);
static int	ft_build_dquote_part(char **str, char **dst, t_data *data);
static int	ft_builf_word_part(char **str, char **dst, t_data *data);

/** Realiza las transformaciones necesarias (expansiones)para strings 
 * complejas.
 * 
 * @param str Puntero a una copia de la string recibida del usuario
 * para actualizar su valor al primer caracter no procesado en la función.
 * @param parts Entero que indica la cantidad de partes/saltos de tipo de
 * string que existen en la string compleja.
 * @param lexem_item Puntero al lexema a rellenar.
 * @param data Puntero a la estructura con información general del programa.
 * Necesaria para actualizar el valor `last_error` o pasarlo como parámetro
 * a funciones que lo necesitan.
 * 
 * @return Resultado de la ejeción. 
 */
int	ft_handle_complex_str(char **str, int parts, t_lexem **lexem_item, \
	t_data *data)
{
	int		i;
	char	**str_parts;

	i = 0;
	(*lexem_item)->token = COMPLEX_WORD;
	(*lexem_item)->str = NULL;
	if (parts < 0)
		return (EXIT_FAILURE);
	else
		str_parts = (char **)malloc((parts + 1) * sizeof(char *));
	if (str_parts == NULL)
		return (err_malloc_fail(&(data->last_exit)), EXIT_FAILURE);
	str_parts[parts] = NULL;
	while (i < parts)
	{
		if (EXIT_FAILURE == ft_expand_parts(str, &(str_parts[i]), data))
			return (EXIT_FAILURE);
		i ++;
	}
	if (EXIT_FAILURE == ft_join_parts(str_parts, lexem_item, data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Distribuye cada parte de la string compleja a la función encargada de
 * su expansión.
 * 
 * @param str Puntero a una copia de la string recibida del usuario
 * para actualizar su valor al primer caracter no procesado en la función..
 * @param dst Puntero al espacio de memoria donde se almacenará el string
 * transformado.
 * @param data Puntero a la estructura con información general del programa.
 * Necesaria para actualizar el valor `last_error` o pasarlo como parámetro
 * a funciones que lo necesitan.
 * 
 * @return Resultado de la ejecución.
 */
static int	ft_expand_parts(char **str, char **dst, t_data *data)
{
	int		status;

	status = EXIT_SUCCESS;
	if (**str == '\'')
		status = ft_build_squote_part(str, dst, &(data->last_exit));
	else if (**str == '"')
		status = ft_build_dquote_part(str, dst, data);
	else
		status = ft_builf_word_part(str, dst, data);
	return (status);
}

/** Realiza la expansión de partes de la string compleja de tipo comillas 
 * simples, actualiza el puntero al último caracter procesado y el
 * `last_error`si es necesario.
 * 
 * @param str Puntero a una copia de la string recibida del usuario
 * para actualizar su valor al primer caracter no procesado en la función.
 * @param dst Puntero al espacio de memoria donde se almacenará el string
 * transformado.
 * @param error Puntero al entero que almacena el último error de ejecución
 * para acutalizarlo si es necesario.
 * 
 * @return Resultado de la ejecución.
 */
static int	ft_build_squote_part(char **str, char **dst, int *error)
{
	char	*quote_end;

	*str = (*str + 1);
	quote_end = ft_strchr(*str, '\'');
	*dst = ft_substr(*str, 0, quote_end - *str);
	if (*dst == NULL)
		return (err_malloc_fail(error), EXIT_FAILURE);
	*str = (*str + (quote_end - *str) + 1);
	return (EXIT_SUCCESS);
}

/** Realiza la expansión de partes de la string compleja de tipo comillas 
 * dobles, actualiza el puntero al último caracter procesado y el
 * `last_error`si es necesario.
 * 
 * @param str Puntero a una copia de la string recibida del usuario
 * para actualizar su valor al primer caracter no procesado en la función.
 * @param dst Puntero al espacio de memoria donde se almacenará el string
 * transformado.
 * @param data Puntero a la estructura con información general del programa.
 * Necesaria como parámetro de funciones.
 * 
 * @return Resultado de la ejecución. 
 */
static int	ft_build_dquote_part(char **str, char **dst, t_data *data)
{
	int		buff;
	char	*quote_end;
	t_lexem	tmp;

	*str = (*str + 1);
	quote_end = ft_strchr(*str, '"');
	tmp.str = ft_substr(*str, 0, quote_end - *str);
	if (tmp.str == NULL)
		return (EXIT_FAILURE);
	if ((ft_expansion_malloc(dst, &tmp, \
		&buff, data) == EXIT_FAILURE) || \
		(ft_fill_expansion(*dst, &tmp, \
		&buff, data) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	*str = (*str + (quote_end - *str) + 1);
	free(tmp.str);
	return (EXIT_SUCCESS);
}

/** Realiza la expansión de partes de la string compleja de tipo palabra 
 * sin entrecomillar, actualiza el puntero al último caracter procesado y el
 * `last_error`si es necesario.
 * 
 * @param str Puntero a una copia de la string recibida del usuario
 * para actualizar su valor al primer caracter no procesado en la función.
 * @param dst Puntero al espacio de memoria donde se almacenará el string
 * transformado.
 * @param data Puntero a la estructura con información general del programa.
 * Necesaria como parámetro de funciones.
 * 
 * @return Resultado de la ejecución. 
 */
static int	ft_builf_word_part(char **str, char **dst, t_data *data)
{
	int		i;
	char	*delimiters;
	char	*string_end;
	int		buff;
	t_lexem	tmp;

	i = 0;
	delimiters = "|<>\"'\b\t\n\v\f\r ";
	string_end = NULL;
	while ((*str)[i] && string_end == NULL)
	{
		if (ft_strchr(delimiters, (*str)[i]) != NULL)
			string_end = (*str + i);
		i++;
	}
	tmp.str = ft_substr(*str, 0, string_end - *str);
	if (tmp.str == NULL)
		return (EXIT_FAILURE);
	if ((ft_expansion_malloc(dst, &tmp, \
		&buff, data) == EXIT_FAILURE) || \
		(ft_fill_expansion(*dst, &tmp, \
		&buff, data) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	*str = (*str + (string_end - *str));
	return (free(tmp.str), EXIT_SUCCESS);
}
