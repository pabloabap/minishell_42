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

static void	ft_regular_chars_fill(char *dst, char *src, int *idx_chars);
static int	ft_exp_fill(char *dst, char *src, int *idx_chars, t_data *data);
static int	ft_exit_fill(char *dst, int *exit, int *idx_chars);
static int	ft_fill_var(char *dst, char *src, int *idx_chars, t_data *data);

/** Rellena la memoria reservada para la string expandida.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero a structura a a expandir.
 * @param buff Puntero a entero que almacena la cantidad de espacio reservado
 * para la nueva string.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 *
 * @returns Estado de salida de la función. 
 **/
int	ft_fill_expansion(char *dst, t_lexem *src, int *buff, t_data *data)
{
	int	idx_chars[2];

	idx_chars[0] = 0;
	idx_chars[1] = 0;
	while (src->str && src->str[idx_chars[0]])
	{
		if (src->str[idx_chars[0]] && src->str[idx_chars[0]] != '$')
			ft_regular_chars_fill(dst, (src->str + idx_chars[0]), idx_chars);
		if (src->token < 0 && *buff < 0 && !(src->str[idx_chars[0]]))
			idx_chars[0]++;
		if (src->str[idx_chars[0]] == '$')
		{
			idx_chars[0]++;
			if (src->token == SINGLE_QUOTES || src->token > SINGLE_QUO_RED)
				ft_strlcat(dst, "$", ++idx_chars[1] + 1);
			else if ('?' == src->str[idx_chars[0]])
				ft_exit_fill(dst, &(data->last_exit), idx_chars);
			else if (ft_exp_fill(dst, src->str, idx_chars, data) == 1)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/** Pasa los caracteres que no forman parte de las variables a la nueva string.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero al string original (con expansiones sin expandir).
 * @param idx_chars Array de enteros con el índice de caracter que se esta 
 * 			procesando (se actualizará para moverlo el número de posiciones
 * 			que se hayan avanzado en la función) y el contador de caracteres
 * 			ya existentes en destino (se utilizará para sumar el número de 
 * 			nuevos caracteres añadidos en dst).
 *
 * @returns Estado de salida de la función. 
 **/
static void	ft_regular_chars_fill(char *dst, char *src, int *idx_chars)
{
	int	new_chars;
	int	buffer;

	new_chars = 0;
	buffer = idx_chars[1] + 1;
	while (src[new_chars] && src[new_chars] != '$')
		new_chars ++;
	buffer += new_chars;
	ft_strlcat(dst, src, buffer);
	idx_chars[1] = idx_chars[1] + new_chars;
	idx_chars[0] = idx_chars[0] + new_chars;
}

/** Gestor de las expansion $? (exit status de la anterior ejecucion.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param chars Puntero al contador de caracteres ya existentes en destino.
 * 			Se utilizará para sumar el número de nuevos caracteres añadidos
 * 			en dst.
 * @param exit Puntero a direccion de memoria que almacena último error de
 * ejecución.
 * @param idx_chars Array de enteros con el índice de caracter que se esta 
 * 			procesando (se actualizará para moverlo el número de posiciones
 * 			que se hayan avanzado en la función) y el contador de caracteres
 * 			ya existentes en destino (se utilizará para sumar el número de 
 * 			nuevos caracteres añadidos en dst).
 *
 * @returns Estado de salida de la función.
 * */
static int	ft_exit_fill(char *dst, int *exit, int *idx_chars)
{
	char	*lst_exit_to_char;

	lst_exit_to_char = ft_itoa(*exit);
	if (!lst_exit_to_char)
		return (err_malloc_fail(exit), EXIT_FAILURE);
	idx_chars[1] = idx_chars[1] + ft_strlen(lst_exit_to_char);
	ft_strlcat(dst, lst_exit_to_char, idx_chars[1] + 1);
	free(lst_exit_to_char);
	idx_chars[0] = idx_chars[0] + 1;
	return (EXIT_SUCCESS);
}

/** Gestor de las distintas opciones de expansión.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero al string original (con expansiones sin expandir).
 * @param idx_chars Array de enteros con el índice de caracter que se esta 
 * 			procesando (se actualizará para moverlo el número de posiciones
 * 			que se hayan avanzado en la función) y el contador de caracteres
 * 			ya existentes en destino (se utilizará para sumar el número de 
 * 			nuevos caracteres añadidos en dst).
 * @param data Puntero a la estructura data con datos generales del programa
 * 			para utilizar o modificar los atributos last_exit y env.
 *
 * @returns Estado de salida de la función. 
 **/
static int	ft_exp_fill(char *dst, char *src, int *idx_chars, t_data *data)
{
	if (ft_isalnum(src[idx_chars[0]]) || src[idx_chars[0]] == '_')
		ft_fill_var(dst, src + idx_chars[0], idx_chars, data);
	else if (!src[idx_chars[0]] \
		|| (!ft_isalnum(src[idx_chars[0]]) && src[idx_chars[0]] != '_'))
	{
		idx_chars[1] = idx_chars[1] + 1;
		ft_strlcat(dst, "$", idx_chars[1] + 1);
	}
	return (EXIT_SUCCESS);
}

/** Añade el valor de las variables al nuevo string.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero al string original (con expansiones sin expandir).
 * @param idx_chars Array de enteros con el índice de caracter que se esta 
 * 			procesando (se actualizará para moverlo el número de posiciones
 * 			que se hayan avanzado en la función) y el contador de caracteres
 * 			ya existentes en destino (se utilizará para sumar el número de 
 * 			nuevos caracteres añadidos en dst).
 * @param data Puntero a la estructura data con datos generales del programa
 * 			para utilizar o modificar los atributos last_exit y env.
 *
 * @returns Estado de salida de la función. 
 **/
static int	ft_fill_var(char *dst, char *src, int *idx_chars, t_data *data)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = 0;
	while (ft_isalnum(src[j]) || src[j] == '_')
		j++;
	var_name = ft_substr(src, 0, j);
	if (var_name == NULL)
		return (err_malloc_fail(&j), EXIT_FAILURE);
	idx_chars[0] = idx_chars[0] + j;
	j = 0;
	var_value = ft_getenv(var_name, data->env->envp_cpy);
	free(var_name);
	while (var_value && var_value[j])
		j++;
	idx_chars[1] = idx_chars[1] + j;
	if (var_value)
		ft_strlcat(dst, var_value, idx_chars[1] + 1);
	return (EXIT_SUCCESS);
}
