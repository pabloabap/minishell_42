#include "../../include/minishell.h"

static void	clean_lex_list(t_lexem *list_lexem);
static void	clean_cmd_list(t_single_cmd *cmd);

/**
 * @brief Libera toda la memoria reservada con malloc de
 * de la estrucutura data y sus atributos si contienen
 * información.
 * 
 * @param data t_data struct que centraliza todas las
 * subestructuras utilizadas en el programa.
 * 
 * @return Nada. Trabaja directamente sobre la estructura
 * pasada como argumento a través de puntero.
 */
void clean_data(t_data *data)
{
	if(data->head_lex_list)
		clean_lex_list(data->head_lex_list);
	if(data->head_cmd_list)
		clean_cmd_list(data->head_cmd_list);
	if(data->input)
		free(data->input);
	data->head_lex_list = NULL;
	data->head_cmd_list = NULL;
	data->input = NULL;	

}
static void	clean_lex_list(t_lexem *list_lexem)
{
	t_lexem	*tmp;

	while (list_lexem)
	{
		tmp = list_lexem;
		list_lexem = list_lexem->next;
		free(tmp->str);
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}
static void	clean_cmd_list(t_single_cmd *cmd)
{
	t_single_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		while (cmd->redirection)
			clean_lex_list(cmd->redirection);
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}