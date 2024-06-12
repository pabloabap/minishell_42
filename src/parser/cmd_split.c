// CABECERA!!!

#include "../../include/minishell.h"

static void ft_add_cmd(t_lexem **lex_list, t_single_cmd **cmd_list);
static void ft_handle_redirections(t_lexem **lex_list, \
t_single_cmd *lst_cmd);
static void ft_handle_str(t_lexem **lex_list, \
t_single_cmd *lst_cmd);

t_single_cmd *ft_cmd_list_builder(t_lexem **lex_list)
{
	t_single_cmd	*cmds_head;
	t_lexem			*fst_lex;

	fst_lex = *lex_list;
	cmds_head = NULL;
	if (*lex_list)
	{
		while (*lex_list && (*lex_list)->token != PIPE)
		{
			ft_add_cmd(lex_list, &cmds_head);
			///?(*lex_list) = (*lex_list)->next;
		}
	}
	(*lex_list) = fst_lex;
	return (cmds_head);
}

/** Funcion para crear la lista de comandos simples pasados
 *  por el usuario. 
 * 
 * @param lex_list lista de structuras de lexemas
 * @param cmd_list lista de structuras de comandos. Se modificará desde
 * dentro de la función.
 * 
 * @return No devuelve nada. Modifica el contenido de cmd_list.
 */
static void ft_add_cmd(t_lexem **lex_list, t_single_cmd **cmd_list)
{
	t_single_cmd	*new_cmd;
	t_single_cmd	*lst_cmd;

	new_cmd = (t_single_cmd *)malloc(sizeof(t_single_cmd));
	if(!new_cmd)
		exit(EXIT_FAILURE);
	new_cmd->next = NULL;
	if ((*cmd_list) == NULL)
	{
		lst_cmd = new_cmd;
		lst_cmd->redirection = NULL;
		(*cmd_list) = lst_cmd;
	}
	else
	{
		lst_cmd = ft_lstcmd(*cmd_list);
		lst_cmd->next = new_cmd;
		lst_cmd = lst_cmd->next;
	}
	if ((*lex_list)->token == IN_REDIR \
		|| (*lex_list)->token == OUT_REDIR \
		|| (*lex_list)->token == HERE_DOC \
		|| (*lex_list)->token == APPEND_REDIR)
		ft_handle_redirections(lex_list, lst_cmd);
	else
		ft_handle_str(lex_list, lst_cmd);
}

static void ft_handle_redirections(t_lexem **lex_list, \
t_single_cmd *lst_cmd)
{
	t_lexem			*redirection_lexem;

	redirection_lexem = (*lex_list); //Crea un puntero para no perder la referencia del nodo de redireccionamiento.
	if (!(*lex_list)->prev)
		exit(EXIT_FAILURE);
	(*lex_list) = (*lex_list)->prev; //Mueve el puntero de lex_list al elemento anterior de la lista de lexemas.
	if (!(redirection_lexem->next))
		perror("Redirection must be precced by a command");
	(*lex_list)->next = (*lex_list)->next->next->next; //Enlaza el lexema anterior a la redirección con el elemto posterior al fichero de redirección
	(*lex_list) = (*lex_list)->next; //Situa el puntero lex_list en el nodo posterior al fichero de redirección para la siguiente iteración.
	free(redirection_lexem->str); //Libera memoria dinámica reservada para el str de redireccionamient. Con tener el token ya podemos identificar el tipo de redireccionamiento;
	redirection_lexem->str = redirection_lexem->next->str; //Trae el str del fichero de redirección al nodo con el token de redirección para unificarlos en un solo nodo;
	redirection_lexem->prev = NULL; //Definimos la redirecicón previa a NULL
	free(redirection_lexem->next->str); //Libera memoria dinámica reservada para el str del fichero de redireccionamiento.
	free(redirection_lexem->next); //Libera memoria dinámica del nodo asignado al fichero de redireccionamineto.
	redirection_lexem->next = NULL; //Definimos la redirecicón siguiente a NULL
	ft_add_redirection(lst_cmd, redirection_lexem); //añadie redirección a la lista de redirecciones.
}

static void ft_handle_str(t_lexem **lex_list, \
t_single_cmd *lst_cmd)
{
	if (lex_list)
		return;
	else if (lst_cmd)
		return;
	else
		return;
}