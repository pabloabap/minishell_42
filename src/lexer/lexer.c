/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:22:42 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:22:48 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Se puede usar el argumento envp para acceder
	a las variables de entorno del sistema pero al
	no ser un standar de C se recomenda usar la
	función getenv para obtener estas variables
*/
#include "../../include/minishell.h"

static int	new_lexem(char **str, t_lexem **lexem_list_last);
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
 *
 * @return Estado de salida de la función.
 **/
int	lexer(char *str, t_lexem **head_lex_list)
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
		status = new_lexem(&trim_str, head_lex_list);
		lex_list_fst = (*head_lex_list);
		while (*trim_str && status == EXIT_SUCCESS)
			status = new_lexem(&trim_str, head_lex_list);
		if (lex_list_fst && status == EXIT_SUCCESS)
			print_lexem_list(lex_list_fst);
	}
	free(head_trim);
	(*head_lex_list) = lex_list_fst;
	return (status);
}

/** Configura el lexema y lo añade a la lista de lexemas.
 *
 * @param str  Puntero al str de readline para poder modificarlo.
 *
 * @param lexem_list Puntero al puntero al primer elemento de la lista.
 *
 * @return Estado de salida de la función. Añade el nuevo nodo al final
 * de la lista de lexemas.
 * */
static int	new_lexem(char **str, t_lexem **lexem_list_last)
{
	t_lexem	*lexem_item;
	int		status;

	lexem_item = (t_lexem *)malloc(sizeof(t_lexem));
	status = EXIT_SUCCESS;
	if (lexem_item == NULL)
	{
		perror("Minishell: t_lexem malloc fails");
		return (EXIT_FAILURE);
	}
	while (is_whitespace(**str))
		(*str)++;
	if (*str && (**str == '"' || **str == '\''))
		status = quoted_lexer(**str, str, &lexem_item);
	else if (*str)
		status = unquoted_lexer(str, &lexem_item);
	if ((*lexem_list_last))
		(*lexem_list_last)->next = lexem_item;
	lexem_item->prev = (*lexem_list_last);
	lexem_item->next = NULL;
	(*lexem_list_last) = lexem_item;
	printf("??POST - str: %s\n", *str);
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
	printf("quote_type: %c | str: %s | end_quote: %p \n", quote_type, *str, end_quote);
	if (end_quote == NULL)
	{
		ft_putendl_fd("minishell: syntax error: quotes not closed", \
		STDERR_FILENO);
		return ((*lexem_item)->str = NULL, EXIT_FAILURE);
	}
	(*lexem_item)->str = ft_substr(*str, 0, end_quote - *str);
	if (quote_type == '"')
		(*lexem_item)->token = DOUBLE_QUOTES;
	else
		(*lexem_item)->token = SINGLE_QUOTES;
	*str = (*str + (end_quote - *str + 1)); // Mueve el puntero str al caracter posterior al cierre de comillas
	printf("POST - str: %s  | ITEM: %s\n", *str, (*lexem_item)->str);
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
		while ((*str)[i] && !(is_whitespace((*str)[i])) \
		&& !(ft_strchr(delimiters, (*str)[i])))
			i++;
		(*lexem_item)->str = ft_substr(*str, 0, i);
		(*lexem_item)->token = WORD;
		printf("_STR: %s\n", (*lexem_item)->str);
		*str += i;
		if ((*lexem_item)->str == NULL)
		{
			ft_putendl_fd("minishell: ft_substr fail", STDERR_FILENO);
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
