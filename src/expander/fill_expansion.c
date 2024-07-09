/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:08:11 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/06 21:08:18 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_regular_chars_fill(char *dst, char *src, int *i, int *chars);
static int	ft_exp_fill(char *dst, char *src, int *i, int *chars);
static int	ft_exit_fill(char *dst, int *chars, int exit, int *i);
static int	ft_fill_var(char *dst, char *src, int *i, int *chars);

/** Rellena la memoria reservada para la string expandida.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero a structura a a expandir.
 * @param buff Puntero a entero que almacena la cantidad de espacio reservado
 * para la nueva string.
 * @param exit Exit status de la enterior ejecucion.
 *
 * @returns Estado de salida de la función. 
 **/
int	ft_fill_expansion(char *dst, t_lexem *src, int *buff, int exit)
{
	int	i;
	int	chars;

	i = 0;
	chars = 0;
	while (src->str && src->str[i])
	{
		if (src->str[i] && src->str[i] != '$')
			ft_regular_chars_fill(dst, (src->str + i), &i, &chars);
		if (src->token < 0 && *buff < 0 && !(src->str[i]))
			i++;
		if (src->str[i] == '$')
		{
			i ++;
			if (src->token == SINGLE_QUOTES || src->token > SINGLE_QUO_RED)
				ft_strlcat(dst, "$", ++chars + 1);
			else if ('?' == src->str[i])
				ft_exit_fill(dst, &chars, exit, &i);
			else if (ft_exp_fill(dst, src->str, &i, &chars) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	printf("___dst - %s\n", dst);
	return (EXIT_SUCCESS);
}

/** Pasa los caracteres que no forman parte de las variables a la nueva string.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero al string original (con expansiones sin expandir).
 * @param i Puntero al entero con el índice de caracter que se esta procesando.
 * 			Se actualizará para moverlo el número de posiciones que se hayan
 * 			avanzado en la función.
 * @param chars Puntero al contador de caracteres ya existentes en destino.
 * 			Se utilizará para sumar el número de nuevos caracteres añadidos
 * 			en dst.
 *
 * @returns Estado de salida de la función. 
 **/
static void	ft_regular_chars_fill(char *dst, char *src, int *i, int *chars)
{
	int	new_chars;
	int	buffer;

	new_chars = 0;
	buffer = *chars + 1;
	while (src[new_chars] && src[new_chars] != '$')
		new_chars ++;
	buffer += new_chars;
	ft_strlcat(dst, src, buffer);
	*chars = *chars + new_chars;
	*i = *i + new_chars;
}

/** Gestor de las expansion $? (exit status de la anterior ejecucion.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero al string original (con expansiones sin expandir).
 * @param chars Puntero al contador de caracteres ya existentes en destino.
 * 			Se utilizará para sumar el número de nuevos caracteres añadidos
 * 			en dst.
 * @param exit Exit status de la enterior ejecucion.
 *
 * @returns Estado de salida de la función.
 * */
static int	ft_exit_fill(char *dst, int *chars, int exit, int *i)
{
	char	*lst_exit_to_char;

	lst_exit_to_char = ft_itoa(exit);
	if (!lst_exit_to_char)
		return (err_malloc_fail(), EXIT_FAILURE);
	*chars = *chars + ft_strlen(lst_exit_to_char);
	ft_strlcat(dst, lst_exit_to_char, *chars + 1);
	free(lst_exit_to_char);
	*i = *i + 1;
	return (EXIT_SUCCESS);
}

/** Gestor de las distintas opciones de expansión.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero al string original (con expansiones sin expandir).
 * @param i Puntero al entero con el índice de caracter que se esta procesando.
 * 			Se actualizará para moverlo el número de posiciones que se hayan
 * 			avanzado en la función.
 * @param chars Puntero al contador de caracteres ya existentes en destino.
 * 			Se utilizará para sumar el número de nuevos caracteres añadidos
 * 			en dst.s.
 *
 * @returns Estado de salida de la función. 
 **/
static int	ft_exp_fill(char *dst, char *src, int *i, int *chars)
{
	if (ft_isalnum(src[*i]) || src[*i] == '_')
		ft_fill_var(dst, src + *i, i, chars);
	else if (!src[*i] || (!ft_isalnum(src[*i]) && src[*i] != '_'))
	{
		*chars = *chars + 1;
		ft_strlcat(dst, "$", *chars + 1);
	}
	return (EXIT_SUCCESS);
}

/** Añade el valor de las variables al nuevo string.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero al string original (con expansiones sin expandir).
 * @param i Puntero al entero con el índice de caracter que se esta procesando.
 * 			Se actualizará para moverlo el número de posiciones que se hayan
 * 			avanzado en la función.
 * @param chars Puntero al contador de caracteres ya existentes en destino.
 * 			Se utilizará para sumar el número de nuevos caracteres añadidos
 * 			en dst.s
 *
 * @returns Estado de salida de la función. 
 **/
static int	ft_fill_var(char *dst, char *src, int *i, int *chars)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = 0;
	while (ft_isalnum(src[j]) || src[j] == '_')
		j++;
	var_name = ft_substr(src, 0, j);
	if (var_name == NULL)
		return (err_malloc_fail(), EXIT_FAILURE);
	*i = *i + j;
	printf("EXPANSION: %s LEN: %d\n", var_name, j);
	j = 0;
	var_value = getenv(var_name);
	free(var_name);
	while (var_value && var_value[j])
		j++;
	*chars = *chars + j;
	if (var_value)
		ft_strlcat(dst, var_value, *chars + 1);
	printf("EXPANSION: %s LEN: %d\n", dst, *i);
	return (EXIT_SUCCESS);
}
