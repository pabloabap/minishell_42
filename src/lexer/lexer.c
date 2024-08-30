/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:22:42 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/06 21:19:46 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	new_lexem(char **str, t_lexem **lexem_list_last, t_data *data);
static int	quoted_lexer(char quote_type, char **str, \
	t_lexem **lexem_item);
static int	unquoted_lexer(char **str, t_lexem **lexem_item);
static void	token_lexem(char **str, t_lexem **lexem_item);

/** ___Separa la str de readline en una lista de lexemas.___
 * 
 * Creamos trim_str para eliminar espacios a principio y final.
 * Como las funciones mueven el puntero trim_str a siguientes caracteres
 * creamos la variable head_trim para no perder la cabecera y poder
 * liberar el malloc que se ha creado con ft_strtrim.
 * 
 * @param str Char * con el input dado por la función readline
 * @param head_lex_list Puntero al puntero del primer elemento de
 * 			la lista de lexemas. Se va moviendo cuando se añaden
 * 			nuevos nodos a la lista. Por ello se almacena la posición
 * 			inicial el lex_list_fst para al final de la ejecución
 * 			reubicarlo al principio de la lista.
 * @param data Puntero a la estructura con información general del programa.
 * 			Necesaria para actualizar el valor `last_error` o pasarlo como
 * 			parámetro a funciones que lo necesitan.
 *
 * @return Estado de salida de la función.
 **/
int	lexer(char *str, t_lexem **head_lex_list, t_data *data)
{
	int		status;
	t_lexem	*lex_list_fst;
	char	*trim_str;
	char	*head_trim;

	status = EXIT_SUCCESS;
	trim_str = ft_strtrim(str, " \f\n\r\t\v");
	head_trim = trim_str;
	if (!trim_str || *trim_str == '\0')
		return (free(trim_str), EXIT_FAILURE);
	if (*trim_str)
	{
		status = new_lexem(&trim_str, head_lex_list, data);
		lex_list_fst = (*head_lex_list);
		while (trim_str && *trim_str && status == EXIT_SUCCESS)
			status = new_lexem(&trim_str, head_lex_list, data);
		if (status < 0)
			status = EXIT_FAILURE;
	}
	free(head_trim);
	(*head_lex_list) = lex_list_fst;
	return (status);
}

/** Configura el lexema y lo añade a la lista de lexemas.
 *
 * @param str  Puntero al str de readline para poder modificarlo.
 * @param lexem_list Puntero al puntero al primer elemento de la lista.
 * @param data Puntero a la estructura con información general del programa.
 * Necesaria para actualizar el valor `last_error` o pasarlo como parámetro
 * a funciones que lo necesitan.
 * 
 * @return Estado de salida de la función. Añade el nuevo nodo al final
 * de la lista de lexemas.
 */
static int	new_lexem(char **str, t_lexem **lexem_list_last, t_data *data)
{
	t_lexem	*lexem_item;
	int		status;

	lexem_item = (t_lexem *)malloc(sizeof(t_lexem));
	if (lexem_item == NULL)
		return (err_malloc_fail(&(data->last_exit)), EXIT_FAILURE);
	while (ft_is_whitespace(**str))
		(*str)++;
	status = ft_check_complex_str(*str);
	if (1 != status)
		status = ft_handle_complex_str(str, status, &lexem_item, data);
	else if (1 == status)
	{
		if (*str && (**str == '"' || **str == '\''))
			status = quoted_lexer(**str, str, &lexem_item);
		else if (*str)
			status = unquoted_lexer(str, &lexem_item);
	}
	if ((*lexem_list_last))
		(*lexem_list_last)->next = lexem_item;
	lexem_item->prev = (*lexem_list_last);
	lexem_item->next = NULL;
	(*lexem_list_last) = lexem_item;
	return (status);
}

/** Crea la estructura lexem para los casos en que un parametro está
 *  entre comillas simples o dobles.
 *
 * Detecta donde está la comilla de cierre. Si no existe
 * imprime un mensaje de error STDERR_FILENO, apunta el atribute str a NULL
 * y returna EXIST_FAILURE; y si existe añade la substring a la structura y 
 * clasifica el token como DOUBLE_QUOTES o SINGLE_QUOTES.
 * En caso de comillas dobles hay que identificar el caracter especial $.
 * 
 * @param quote_type Tipo de comilla de inicio, puede ser simple o doble.
 * @param str Puntero al str de readline para poder leer leer caracteres
 *          hasta cierre de comillas y devolverlo apuntando al siguiente char.
 * @param lexem_item Puntero al puntero de la estrucura lexem para
 *         modificarla desde la función.
 *
 * @returns Estado de salida de la función.  Modifica el puntero del 
 * str para que apunte al character posterior al cierre de comillas.
 **/
static int	quoted_lexer(char quote_type, char **str, t_lexem **lexem_item)
{
	char	*end_quote;

	end_quote = ft_strchr(++(*str), quote_type);
	ft_consecutive_quotes(&end_quote, quote_type);
	if (end_quote == NULL)
	{
		ft_putendl_fd("-minishell: syntax error: quotes not closed", \
		STDERR_FILENO);
		return ((*lexem_item)->str = NULL, EXIT_FAILURE);
	}
	if (quote_type == '"')
		(*lexem_item)->token = DOUBLE_QUOTES;
	else
		(*lexem_item)->token = SINGLE_QUOTES;
	(*lexem_item)->str = ft_substr(*str, 0, end_quote - *str + \
		!(*end_quote == quote_type));
	ft_str_lex_check(lexem_item, quote_type);
	if ((*lexem_item)->str == NULL)
		return (EXIT_FAILURE);
	*str = (*str + (end_quote - *str + 1));
	return (EXIT_SUCCESS);
}

/** Crea la estructura lexem para los casos no entrecomillados.
 * Si son pipes o redirecciones se procesaran de una forma y
 * si son palabras de otra.
 *
 * @param str Puntero al str de readline para poder leer leer caracteres
 *          hasta cierre de comillas y devolverlo apuntando al siguiente char.
 * @param lexem_item Puntero al puntero de la estrucura lexem para
 *         modificarlo desde la función.
 *
 * @returns Resultado de la ejecuccion. Modifica el puntero del str para 
 * que apunte al character posterior al string tratado.
 **/
static int	unquoted_lexer(char **str, t_lexem **lexem_item)
{
	char	*delimiters;
	int		i;

	delimiters = "|<>";
	i = 0;
	if (ft_strchr(delimiters, **str))
		token_lexem(str, lexem_item);
	else
	{
		while ((*str)[i] && !(ft_is_whitespace((*str)[i])) \
		&& !(ft_strchr(delimiters, (*str)[i])))
			i++;
		(*lexem_item)->str = ft_substr(*str, 0, i);
		(*lexem_item)->token = WORD;
		*str += i;
		if ((*lexem_item)->str == NULL)
		{
			ft_putendl_fd("-minishell: ft_substr fail", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/** Rellena las struct s_lexem de los lexemas especiales 
 * (pipes y redirecciones), en adelante ITEM.
 * 
 * @param lexem_item Puntero al puntero de la estrucura lexem para
 *         modificarlo desde la función.
 
 * @returns Nada. Modifica el puntero del str para que apunte al character
 * posterior al cierre de comillas.
 **/
static void	token_lexem(char **str, t_lexem **lexem_item)
{
	int	chr_count;

	chr_count = 0;
	if (ft_strnstr(*str, ">>", 2))
		chr_count = token_lex_fill(">>", lexem_item, APPEND_REDIR);
	else if (ft_strnstr(*str, ">", 2))
		chr_count = token_lex_fill(">", lexem_item, OUT_REDIR);
	else if (ft_strnstr(*str, "<<", 2))
		chr_count = token_lex_fill("<<", lexem_item, HERE_DOC);
	else if (ft_strnstr(*str, "<", 2))
		chr_count = token_lex_fill("<", lexem_item, IN_REDIR);
	else if (ft_strnstr(*str, "|", 2))
		chr_count = token_lex_fill("|", lexem_item, PIPE);
	*str += chr_count;
	return ;
}
