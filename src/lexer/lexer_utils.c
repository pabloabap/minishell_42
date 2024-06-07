// CABECERA

#include "../../include/minishell.h"
#include "../../include/lexer.h"

/** Comprueba si el caracter del argumento es algún tipo de espacio.
 * 
 * @return 1 si es espacio, 0 si no.
*/
int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

/** Imprime los elementos de una lista de t_lexems.
 * 
 * @param lexems_list_iter Puntero al primer elemento de la lista
 * 			lexem para recorrerla.
 *
 * @returns Nada. Imprime cada elemento de la lista por stdout.
 **/
void	print_lexem_list(t_lexem *lexems_list_iter)
{
	int	i;

	i = 0;
	while (lexems_list_iter != NULL)
	{
		printf("ITEM %i - %s | TOKEN: %i\n", i++, lexems_list_iter->str, lexems_list_iter->token);
		lexems_list_iter = lexems_list_iter->next;
	}
}

/** Rellena los atributos str y token de las struct s_lexem de 
 * los lexemas especiales (pipes y redirecciones), en adelante ITEM.
 * 
 * @param str String de los caracteres que componen el ITEM .
 * @param lexem_item Puntero al puntero de la estrucura lexem para
 *         modificarlo desde la función.
 * @param token elemento de enum e_token que identifica el tipo 
 * 			de ITEM en el atributo token.
 *
 * @returns Número de caracteres que tiene el simbolo de redirección.
 **/
int	token_lex_fill(char *str, t_lexem **lexem_item, t_tokens token)
{
	int	chars;

	chars = ft_strlen(str);
	(*lexem_item)->str = str;
	(*lexem_item)->token = token;
	return (chars);
}

void	free_cleaner(t_lexem *list_lexem)
{
	t_lexem	*tmp;

	while (list_lexem)
	{
		tmp = list_lexem;
		list_lexem = list_lexem->next;
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}