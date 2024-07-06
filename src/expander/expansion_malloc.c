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
static int	ft_expansion_logic(char *str, int *i, int *chars);
static int	ft_expansion_len(char *str, int *i, int *chars);

/** Aprovisiona memoria para la nueva string con expansiones expandida.
 * 
 * @param exp_malloc Puntero a un puntero char que se modificara para que
 * apunte al espacio de memoria aprovisionado para la nueva string.
 * @param str String que contiene expansiones.
 * @param token Indicador del tipo de string, para no expandir string de
 * tipo comillas simple.
 * @param buffer Puntero a entero que almacena la cantidad de espacio reservado
 * para la nueva string.
 *
 * @returns Estado de salida de la función. 
 **/
int	ft_expansion_malloc(char **exp_malloc, char *str, int token, int *buffer)
{
	int	i;
	int	chars;

	i = 0;
	chars = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] != '$')
			ft_regular_char_count(&i, &chars);
		if (str[i] == '$')
		{
			i ++;
			if (token == SINGLE_QUOTES || token > SINGLE_QUO_RED)
				chars ++;
			else if (ft_expansion_logic(str, &i, &chars) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	printf("NEW STRING CHARS: %d\n", chars);
	*exp_malloc = (char *)ft_calloc(chars + 1, sizeof(char));
	if (!(*exp_malloc))
		return (err_malloc_fail(), EXIT_FAILURE);
	*buffer = chars;
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
 *
 * @returns Estado de salida de la función. 
 **/
static int	ft_expansion_logic(char *str, int *i, int *chars)
{
	char	*lst_exit_to_char;

	lst_exit_to_char = ft_itoa(g_last_exit);
	if (!lst_exit_to_char)
		return (err_malloc_fail(), EXIT_FAILURE);
	if (str[*i] == '?')
	{
		*chars += ft_strlen(lst_exit_to_char);
		*i = *i + 1;
	}
	else if (ft_isalnum(str[*i]) || str[*i] == '_')
		ft_expansion_len(str + *i, i, chars);
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
 *
 * @returns Estado de salida de la función. 
 **/
static int	ft_expansion_len(char *str, int *i, int *chars)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = 0;
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	var_name = ft_substr(str, 0, j);
	if (var_name == NULL)
		return (err_malloc_fail(), EXIT_FAILURE);
	*i = *i + j;
	j = 0;
	printf("EXPANSION: %s LEN: %d\n", var_name, j);
	var_value = getenv(var_name);
	free(var_name);
	while (var_value && var_value[j])
		j++;
	*chars = *chars + j;
	printf("EXPANSION: %s LEN: %d\n", var_value, j);
	return (EXIT_SUCCESS);
}
