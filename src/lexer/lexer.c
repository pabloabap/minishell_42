// CABECERA !!!!
/*
	Se puede usar el argumento envp para acceder
	a las variables de entorno del sistema pero al
	no ser un standar de C se recomenda usar la
	función getenv para obtener estas variables
*/
#include "../../include/minishell.h"
#include "../../include/lexer.h"

t_lexem	*new_lexem(char **str, t_lexem *lexem_list_last);
void	quoted_lexer(char quote_type, char **str, t_lexem **lexem_item);
void	unquoted_lexer(char **str, t_lexem **lexem_item);
void	token_lexem(char **str, t_lexem **lexem_item);

/** Separa la str de readline en una lista de lexemas.
 *
 * @param str Char * con el input dado por la función readline
 *
 * @return Puntero al primer elemento de la lista acabada en NULL
 **/
t_lexem	*lexer(char *str)
{
	t_lexem	*lexems_list_first;
	t_lexem	*lexems_list_last;
	t_lexem	*lexems_list_iter;

	lexems_list_first = new_lexem(&str, NULL);
	lexems_list_iter = lexems_list_first;
	lexems_list_last = lexems_list_first;
	while (*str)
		lexems_list_last = new_lexem(&str, lexems_list_last);
	print_lexem_list(lexems_list_iter);
	return (lexems_list_first);
}

/** Configura el lexema y lo añade a la lista de lexemas.
 *
 * @param str  Puntero al str de readline para poder modificarlo.
 *
 * @param lexem_list Puntero al puntero al primer elemento de la lista.
 *
 * @return No hay. El resultado se aplica directamente
 * a los punteros de los argumentos.
 * */
t_lexem	*new_lexem(char **str, t_lexem *lexem_list_last)
{
	t_lexem	*lexem_item;

	lexem_item = (t_lexem *)malloc(sizeof(t_lexem));
	if (lexem_item == NULL)
		exit(EXIT_FAILURE);
	while (is_whitespace(**str))
		(*str)++;
	if (*str && (**str == '"' || **str == '\''))
		quoted_lexer(**str, str, &lexem_item);
	else if (*str)
		unquoted_lexer(str, &lexem_item);
	if (lexem_list_last)
		lexem_list_last->next = lexem_item;
	lexem_item->prev = lexem_list_last;
	lexem_item->next = NULL;
	printf("??POST - str: %s\n", *str);
	return (lexem_item);
}

/** Crea la estructura lexem para los casos en que un parametro está
 *  entre comillas simples o dobles.
 *
 * Detecta donde está la comilla de cierre. Si no existe
 * anuncia error y sale con EXIST_FAILURE; y si existe añade
 * la substring a la structura y clasifica el token como DOUBLE_QUOTES
 * en caso de comillas dobles para tener en cuenta que hay que identificar
 * el caracter especial $ en el futuro o WORD en caso de comillas simples.
 *
 * @param quote_type The starting quote type, it could be simple or double.
 * @param str Puntero al str de readline para poder leer leer caracteres
 *          hasta cierre de comillas y devolverlo apuntando al siguiente char.
 * @param lexem_item Puntero al puntero de la estrucura lexem para
 *         modificarlo desde la función.
 *
 * @returns Nada. Modifica el puntero del str para que apunte al character
 * posterior al cierre de comillas.
 **/
void	quoted_lexer(char quote_type, char **str, t_lexem **lexem_item)
{
	char	*end_quote;

	end_quote = ft_strchr(++(*str), quote_type);
	printf("quote_type: %c | str: %s | end_quote: %p \n", quote_type, *str, end_quote);
	if (end_quote == NULL)
	{
		printf("STRERROR - %s\n", strerror(EINVAL)); // ERROR DE ARGUMENTO INVALIDO
		perror("EINVAL"); // REVISAR SI HAY QUE METERLO EN STDERR
		exit(EXIT_FAILURE);
	}
	(*lexem_item)->str = ft_substr(*str, 0, end_quote - *str);
	if (quote_type == '"')
		(*lexem_item)->token = DOUBLE_QUOTES;
	else
		(*lexem_item)->token = WORD;
	*str = (*str + (end_quote - *str + 1)); // Mueve el puntero str al caracter posterior al cierre de comillas
	printf("POST - str: %s  | ITEM: %s\n", *str, (*lexem_item)->str);
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
 * @returns Nada. Modifica el puntero del str para que apunte al character
 * posterior al string tratado.
 **/
void	unquoted_lexer(char **str, t_lexem **lexem_item)
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
	}
}

/** Rellena las struct s_lexem de los lexemas especiales 
 * (pipes y redirecciones), en adelante ITEM.
 * 
 * @param lexem_item Puntero al puntero de la estrucura lexem para
 *         modificarlo desde la función.
 
 * @returns Nada. Modifica el puntero del str para que apunte al character
 * posterior al cierre de comillas.
 **/
void	token_lexem(char **str, t_lexem **lexem_item)
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

int	main(void)
{
	char	*input;
	t_lexem	*lexem_list;
	int iters=0;

	while (iters < 2)
	{
		input = readline("\033[31mMinishell\033[0m > ");
		add_history(input);
		if (*input)
		{
			lexem_list = lexer(input);
			free(input);
			free_cleaner(lexem_list);
		}
		iters ++;
	}
	return (0);
}
