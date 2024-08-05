/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:07:58 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/06 21:08:04 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_regular_char_count(int *i, int *chars);
static int	ft_exp_logic(char *str, int *i, int *chars, int *exit);
static int	ft_exp_len(char *str, int *i, int *chars, int *exit);

/** Aprovisiona memoria para la nueva string con expansiones expandida.
 * 
 * @param dst Puntero a un puntero char que se modificara para que
 * apunte al espacio de memoria aprovisionado para la nueva string.
 * @param src Puntero a structura a a expandir.
 * @param buffer Puntero a entero que almacena la cantidad de espacio reservado
 * para la nueva string.
 * @param exit Puntero a direccion de memoria que almacena último error de
 * ejecución.
 *
 * @returns Estado de salida de la función. 
 **/
int	ft_expansion_malloc(char **dst, t_lexem *src, int *buff, int *exit)
{
	int	i;
	int	chars;

	i = 0;
	chars = 0;
	while (src->str && src->str [i])
	{
		while (src->str [i] && src->str [i] != '$')
			ft_regular_char_count(&i, &chars);
		if (src->str [i] == '$')
		{
			i ++;
			if (ft_exp_logic(src->str, &i, &chars, exit) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	*dst = (char *)ft_calloc(chars + 1, sizeof(char));
	if (!(*dst))
		return (err_malloc_fail(exit), EXIT_FAILURE);
	*buff = chars;
	return (EXIT_SUCCESS);
}

/** Actualiza el contador de caracters y el indice de una string*/
static void	ft_regular_char_count(int *i, int *chars)
{
	*i = *i + 1;
	*chars = *chars + 1;
}

/** Gestor de las distintas opciones de expansión.
 * $? - Devuelve el estado de salida de la anterior ejecución
 * $VAR_NAME - El valor de esa variable de entorno.
 * En cualquier otro caso escribirá el signo dolar.
 * 
 * @param str String que contiene expansiones.
 * @param i Puntero a indice de carácteres para modificarlo al
 * hacer avances sobre los carácteres del string.
 * @param chars Puntero al contador de carácteres de la string
 * expandida para podificarlo conforme vaya habiendo expansiones.
  * @param exit Puntero a direccion de memoria que almacena último error de
 * ejecución.
 *
 * @returns Estado de salida de la función. 
 **/
static int	ft_exp_logic(char *str, int *i, int *chars, int *exit)
{
	char	*lst_exit_to_char;

	lst_exit_to_char = ft_itoa(*exit);
	if (!lst_exit_to_char)
		return (err_malloc_fail(exit), EXIT_FAILURE);
	if (str[*i] == '?')
	{
		*chars += ft_strlen(lst_exit_to_char);
		*i = *i + 1;
	}
	else if (ft_isalnum(str[*i]) || str[*i] == '_')
		ft_exp_len(str + *i, i, chars, exit);
	else
		*chars = *chars + 1;
	free(lst_exit_to_char);
	return (EXIT_SUCCESS);
}

/** Contador de caracteres del valor (VAR_VALUE) de la variable a expandir
 * expansion(VAR_NAME).
 * 
 * @param str String que contiene expansiones.
 * @param i Puntero a indice de carácteres. Se modificará al
 * hacer avances sobre los carácteres del string.
 * @param chars Puntero al contador de carácteres de la string
 * expandida para podificarlo conforme vaya habiendo expansiones.
  * @param exit Puntero a direccion de memoria que almacena último error de
 * ejecución.
 *
 * @returns Estado de salida de la función. 
 **/
static int	ft_exp_len(char *str, int *i, int *chars, int *exit)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = 0;
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	var_name = ft_substr(str, 0, j);
	if (var_name == NULL)
		return (err_malloc_fail(exit), EXIT_FAILURE);
	*i = *i + j;
	j = 0;
	var_value = getenv(var_name);
	free(var_name);
	while (var_value && var_value[j])
		j++;
	*chars = *chars + j;
	return (EXIT_SUCCESS);
}
