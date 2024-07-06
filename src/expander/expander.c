// CABECERA!!!

#include "../../include/minishell.h"

static int	ft_str_expander(t_lexem *lex_list);

/** Expansion de strings del atributo str de los t_single_cmd (equivalente
 *  a lex_list) y del atributo redirection (otra lex_list de redirecciones).
 * 
 * @param lex_list Puntero al primer elemento de la lista de lexemas.
 * @param cmd_list Puntero al primer elemento de la lista de t_single_cmd.
 *
 * @returns Estado de salida de la función. 
 **/
int	ft_expander(t_lexem *lex_list, t_single_cmd *cmd_list)
{
	printf("___EXPANDIENDO STRS___\n");
	if (ft_str_expander(lex_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("___EXPANDIENDO REDIRS___\n");
	while (cmd_list)
	{
		if (ft_str_expander(cmd_list->redirection) \
		== EXIT_FAILURE)
			return (EXIT_FAILURE);
		cmd_list = cmd_list->next;
	}
	return (EXIT_SUCCESS);
}

/** Funcion de apoyo para expandir el atributo str de estructuras t_lexem.
 * @param lex_list Puntero al primer elemento de la lista de lexemas.
 * 
 * @returns Estado de salida de la función. 
 **/
static int	ft_str_expander(t_lexem *lex_list)
{
	char	*exp_malloc;
	int		buffer;

	exp_malloc = NULL;
	while (lex_list)
	{
		if (ft_has_expansion(lex_list->str))
		{
			if ((ft_expansion_malloc(&exp_malloc, lex_list->str, \
				lex_list->token, &buffer) == EXIT_FAILURE) || \
				(ft_fill_expansion(exp_malloc, lex_list->str, \
				lex_list->token, &buffer) == EXIT_FAILURE) || \
				(ft_expansion_replace(exp_malloc, lex_list) == EXIT_FAILURE))
				return (EXIT_FAILURE);
			if (lex_list->token > SINGLE_QUO_RED)
				lex_list->token -= SINGLE_QUO_RED;
		}
		lex_list = lex_list->next;
		printf("_____\n");
	}
	return (EXIT_SUCCESS);
}
