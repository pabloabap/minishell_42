//CABECERA!!!

#include "../../include/minishell.h"

static void	ft_regular_chars_fill(char *dst, char *src, int *i, int *chars);
static int	ft_expansions_fill(char *dst, char *src, int *i, int *chars);
static int	ft_fill_var(char *dst, char *src, int *i, int *chars);

/** Rellena la memoria reservada para la string expandida.
 * 
 * @param dst Puntero al espacio de memoria reservado para la nueva string.
 * @param src Puntero al string original (con expansiones sin expandir).
 * @param token Indicador del tipo de string, para no expandir string de
 * 			tipo comillas simple.
 * @param buff Puntero a entero que almacena la cantidad de espacio reservado
 * para la nueva string.
 *
 * @returns Estado de salida de la función. 
 **/
int	ft_fill_expansion(char *dst, char *src, int token, int *buff)
{
	int	i;
	int	chars;

	i = 0;
	chars = 0;
	while (src && src[i])
	{
		if (src[i] && src[i] != '$')
			ft_regular_chars_fill(dst, (src + i), &i, &chars);
		if (token < 0 && *buff < 0 && !(src[i]))
			i++;
		if (src[i] == '$')
		{
			i ++;
			if (token == SINGLE_QUOTES || token > SINGLE_QUO_RED)
				ft_strlcat(dst, "$", ++chars + 1);
			else if (ft_expansions_fill(dst, src, &i, &chars) == EXIT_FAILURE)
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
static int	ft_expansions_fill(char *dst, char *src, int *i, int *chars)
{
	char	*lst_exit_to_char;

	lst_exit_to_char = ft_itoa(g_last_exit);
	if (!lst_exit_to_char)
		return (err_malloc_fail(), EXIT_FAILURE);
	if (src[*i] == '?')
	{
		*chars = *chars + ft_strlen(lst_exit_to_char);
		ft_strlcat(dst, lst_exit_to_char, *chars + 1);
		*i = *i + 1;
	}
	else if (ft_isalnum(src[*i]) || src[*i] == '_')
		ft_fill_var(dst, src + *i, i, chars);
	else if (!src[*i] || (!ft_isalnum(src[*i]) && src[*i] != '_'))
	{
		*chars = *chars + 1;
		ft_strlcat(dst, "$", *chars + 1);
	}
	free(lst_exit_to_char);
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
