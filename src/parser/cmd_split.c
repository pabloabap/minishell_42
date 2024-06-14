/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:23:11 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:23:15 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int ft_create_cmd(t_single_cmd **cmd_list);
static int ft_fill_cmd(t_lexem **lex_list, t_single_cmd *cmd_list);
static int ft_handle_redirections(t_lexem **lex_list, \
t_single_cmd *lst_cmd);
static int ft_handle_str(t_lexem **lex_list, t_single_cmd *lst_cmd);

int	ft_cmd_list_builder(t_lexem *lex_list, t_single_cmd **cmd)
{
	t_single_cmd	*cmds_head;

	if (grammar_checks(lex_list) == EXIT_SUCCESS)
	{
		while (lex_list && ft_create_cmd(cmd) == EXIT_SUCCESS)
		{		
			if ((*cmd)->prev)
				cmds_head = (*cmd);
			while (lex_list && lex_list->token != PIPE && \
			ft_fill_cmd(&lex_list, *cmd) == EXIT_SUCCESS);
			if(lex_list && lex_list->token == PIPE)
				lex_list = lex_list->next;
		}
	}
	(*cmd) = cmds_head;
	return (EXIT_FAILURE);
}

static int ft_create_cmd(t_single_cmd **cmd_list)
{
	t_single_cmd	*new_cmd;

	new_cmd = (t_single_cmd *)malloc(sizeof(t_single_cmd));
	if(!new_cmd)
		return(err_malloc_fail(), EXIT_FAILURE);
	new_cmd->next = NULL;
	if ((*cmd_list) == NULL)
	{
		new_cmd->redirection = NULL;
		new_cmd->str = NULL;
		(*cmd_list) = new_cmd;
	}
	else
	{
		(*cmd_list) = ft_lstcmd(*cmd_list);
		(*cmd_list)->next = new_cmd;
		new_cmd->prev = (*cmd_list);
		(*cmd_list) = new_cmd;
	}
	return (EXIT_SUCCESS);
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
static int ft_fill_cmd(t_lexem **lex_list, t_single_cmd *cmd_list)
{
	if ((*lex_list)->token >= IN_REDIR \
		&& (*lex_list)->token <= APPEND_REDIR)
		return(ft_handle_redirections(lex_list, cmd_list));
	else
		return(ft_handle_str(lex_list, cmd_list));
}

static int ft_handle_redirections(t_lexem **lex_list, \
t_single_cmd *lst_cmd)
{
	t_lexem			*redirection_lexem;

	redirection_lexem = (*lex_list); //Crea un puntero para no perder la referencia del nodo de redireccionamiento.
	if ((*lex_list)->prev)
		(*lex_list) = (*lex_list)->prev; //Mueve el puntero de lex_list al elemento anterior de la lista de lexemas.
	if (redirection_lexem->next->token > DOUBLE_QUOTES)
		return(err_red_no_file(), EXIT_FAILURE);
	(*lex_list)->next = (*lex_list)->next->next->next; //Enlaza el lexema anterior a la redirección con el elemto posterior al fichero de redirección
	(*lex_list) = (*lex_list)->next; //Situa el puntero lex_list en el nodo posterior al fichero de redirección para la siguiente iteración.
	redirection_lexem->str = redirection_lexem->next->str; //Trae el str del fichero de redirección al nodo con el token de redirección para unificarlos en un solo nodo;
	redirection_lexem->prev = NULL; //Definimos la redirecicón previa a NULL
	free(redirection_lexem->next->str); //Libera memoria dinámica reservada para el str del fichero de redireccionamiento.
	free(redirection_lexem->next); //Libera memoria dinámica del nodo asignado al fichero de redireccionamineto.
	redirection_lexem->next = NULL; //Definimos la redirecicón siguiente a NULL
	ft_add_redirection(lst_cmd, redirection_lexem); //añadie redirección a la lista de redirecciones.
	return(EXIT_SUCCESS);
}

static int ft_handle_str(t_lexem **lex_list, t_single_cmd *lst_cmd)
{
	int i;
	int cmds_count;

	i = 0;
	cmds_count = cmd_len(*lex_list);
	if (lst_cmd->str == NULL)
	{
		lst_cmd->str = (char **)malloc(sizeof(char*) \
			* (cmds_count + 1));
		if(lst_cmd->str == NULL)
			return(err_malloc_fail(), EXIT_FAILURE);
		while (i < cmds_count)
			(lst_cmd->str)[i++] = NULL;
		i = 0;
	}
	while ((*lex_list) && (*lex_list)->token <= DOUBLE_QUOTES)
	{
		(lst_cmd->str)[i++] = (*lex_list)->str;
		(*lex_list) = (*lex_list)->next;
	}
	return (EXIT_SUCCESS);
}