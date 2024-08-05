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

static int	ft_create_cmd(t_single_cmd **cmd_list, int *en);
static int	ft_fill_cmd(t_lexem **lex_list, t_single_cmd *cmd_list, int *en);
static int	ft_handle_redirections(t_lexem **lex_list, \
t_single_cmd *lst_cmd);
static int	ft_handle_str(t_lexem **lex_list, t_single_cmd *lst_cmd, int *en);

/** Constructor de la lista de estructuras de comandos.
 * En cada estructura se apunta el comando y argumentos localizados
 * en la lex_list. Y las redirecciones se sacan de la lex_list y
 * se crea otra lex_list que contiene las redirecciones asociadas al
 * commando.
 * 
 * @param lex_list Primer elemento de la lista de lexemas no procesado.
 * @param cmd Puntero a puntero a la estructura t_single_cmd.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 * 
 * @returns Estado de salida de la función.  Durante el proceso
 * se modifica la lex_list para que solo tenga comandos y sus argumentos
 * y se generan las estructuras de comandos en la lista de comandos.
 **/
int	ft_cmd_list_builder(t_lexem *lex_list, t_single_cmd **cmd, int *err_n)
{
	t_single_cmd	*cmds_head;

	if (grammar_checks(lex_list) == EXIT_SUCCESS)
	{
		while (lex_list && ft_create_cmd(cmd, err_n) == EXIT_SUCCESS)
		{
			if ((*cmd) && (*cmd)->prev == NULL)
				cmds_head = (*cmd);
			while (lex_list && lex_list->token != PIPE && \
			ft_fill_cmd(&lex_list, *cmd, err_n) == EXIT_SUCCESS)
				;
			if (lex_list && lex_list->token == PIPE)
				lex_list = lex_list->next;
		}
		(*cmd) = cmds_head;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/** Constructor de nuevas estructuras t_single_cmd.
 * Si no hay estructuras en la lista de estructuras de comandos,
 * la nueva estructura será el primer elemento de la lista. 
 * En caso contrario, se añadirá como último elemento de la lista.
 * 
 * @param cmd_list Doble puntero al primer elemento de la lista de
 * comandos no procesado.
  * @param err_n Puntero a direccion de memoria que almacena último error de
 * ejecución.

 * @returns Estado de salida de la función. Durante el proceso
 * se fijan los atributos de la nueva estructura a NULL para que 
 * empicen vacios y en caso de que existir elementos en la lista
 * de comandos damos valor a los punteros prev de la nueva 
 * estructura y next de la estructura que anteriormente era la 
 * última de la lista.
 **/
static int	ft_create_cmd(t_single_cmd **cmd_list, int *err_n)
{
	t_single_cmd	*new_cmd;

	new_cmd = (t_single_cmd *)malloc(sizeof(t_single_cmd));
	if (!new_cmd)
		return (err_malloc_fail(err_n), EXIT_FAILURE);
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	new_cmd->redirection = NULL;
	new_cmd->str = NULL;
	new_cmd->cmd_path = NULL;
	if ((*cmd_list) == NULL)
		(*cmd_list) = new_cmd;
	else
	{
		(*cmd_list) = ft_lstcmd(*cmd_list);
		(*cmd_list)->next = new_cmd;
		new_cmd->prev = (*cmd_list);
		(*cmd_list) = new_cmd;
	}
	return (EXIT_SUCCESS);
}

/** Funcion para rellenar los atributos de una estructura comando.
 * 
 * @param lex_list lista de structuras de lexemas.
 * @param cmd_list lista de structuras de comandos. Se modificará 
 * desde dentro de la función.
 * @param en Puntero a direccion de memoria que almacena último error de
 * ejecución.
 * 
 * @return Devuelve el estado de salida de la función. 
 * Modifica el contenido de cmd_list.
 */
static int	ft_fill_cmd(t_lexem **lex_list, t_single_cmd *cmd_list, int *en)
{
	if ((*lex_list)->token >= IN_REDIR \
		&& (*lex_list)->token <= HERE_DOC)
		return (ft_handle_redirections(lex_list, cmd_list));
	else
		return (ft_handle_str(lex_list, cmd_list, en));
}

/** Rellena el atributo redirection de la estructura comando 
 * apuntanda por `lst_cmd` y quita de `lex_list` los elementos 
 * que componen la redireccion. 
 * 
 * @param lex_list Doble puntero al primer elemento de la lista de 
 * lexemas no procesado.
 * @param lst_cmd Puntero a item de la lista de t_single_cmd.
 *
 * @returns Estado de salida de la función.
 **/
static int	ft_handle_redirections(t_lexem **lex_list, \
t_single_cmd *lst_cmd)
{
	t_lexem	*redirection_lexem;

	redirection_lexem = (*lex_list);
	if (redirection_lexem->next->token > DOUBLE_QUOTES)
		return (err_red_no_file(), EXIT_FAILURE);
	(*lex_list) = (*lex_list)->next->next;
	if (*lex_list)
	{
		(*lex_list)->prev = (*lex_list)->prev->prev->prev;
		if ((*lex_list)->prev)
			(*lex_list)->prev->next = (*lex_list);
	}
	else if (redirection_lexem->prev)
		redirection_lexem->prev->next = NULL;
	redirection_lexem->str = ft_strdup(redirection_lexem->next->str);
	ft_redirection_quotes (redirection_lexem);
	redirection_lexem->prev = NULL;
	free(redirection_lexem->next->str);
	free(redirection_lexem->next);
	redirection_lexem->next = NULL;
	ft_add_redirection(lst_cmd, redirection_lexem);
	return (EXIT_SUCCESS);
}

/** Rellena el atributo **str de la estructura comando apuntanda por
 * lst_cmd. Como es un array de strings, primero se reserva el
 * espacio dinámico necesario y luego se apunta al comando y 
 * argumentos localizados en la lex_list. 
 * 
 * @param lex_list Doble puntero al primer elemento de la lista de 
 * lexemas no procesado.
 * @param lst_cmd Puntero a item de la lista de t_single_cmd.
 * @param en Puntero a direccion de memoria que almacena último error de
 * ejecución.

 *
 * @returns Estado de salida de la función.  Durante el proceso
 * se van añadiendo punteros a strings de la lex_list en el
 * array de t_single_cmd->str.
 **/
static int	ft_handle_str(t_lexem **lex_list, t_single_cmd *lst_cmd, int *en)
{
	int	i;
	int	cmds_count;

	i = 0;
	cmds_count = cmd_len(*lex_list);
	if (lst_cmd->str == NULL)
	{
		lst_cmd->str = (char **)malloc(sizeof(char *) \
			* (cmds_count + 1));
		if (lst_cmd->str == NULL)
			return (err_malloc_fail(en), EXIT_FAILURE);
		while (i < cmds_count + 1)
			(lst_cmd->str)[i++] = NULL;
		i = 0;
	}
	while ((lst_cmd->str)[i] != NULL)
		i ++;
	while ((*lex_list) && (*lex_list)->token <= DOUBLE_QUOTES)
	{
		(lst_cmd->str)[i++] = (*lex_list)->str;
		(*lex_list) = (*lex_list)->next;
	}
	return (EXIT_SUCCESS);
}
