/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:24:07 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/26 10:42:21 by anguil-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	clean_lex_list(t_lexem *list_lexem, int is_redirection);
static void	clean_cmd_list(t_single_cmd *cmd);

/** Limpieza final antes de salir del programa del todo.*/
void	ft_final_clean(t_data *data)
{
	int		i;

	i = 0;
	while (data->env->envp_cpy[i] != NULL)
	{
		free(data->env->envp_cpy[i]);
		i++;
	}
	i = 0;
	while (data->env->export_cpy[i] != NULL)
	{
		free(data->env->export_cpy[i]);
		i++;
	}
	free(data->env->envp_cpy);
	free(data->env->export_cpy);
	free(data->env);
	free(data);
}

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
void	clean_data(t_data *data)
{
	if (data->head_lex_list)
		clean_lex_list(data->head_lex_list, 0);
	if (data->head_cmd_list)
		clean_cmd_list(data->head_cmd_list);
	if (data->input)
		free(data->input);
	data->head_lex_list = NULL;
	data->head_cmd_list = NULL;
	data->input = NULL;
}

/** Liberación de memoria dinámica utilizada para almacenar
 * información de los lexemas recibidos.
 * 
 * @param list_lexem Puntero al inicio de la lista de estructuras con 
 * información de los lexemas.
 * @param is_redirection Flag para identificar si lo recibido es una lista
 * de lexemas de tipo redirección o no. En función de esto hay pequeñas
 * variaciones en el proceso de liberación.
 * 
 * @return Nada, limpia la lista a través de punteros.
 */
static void	clean_lex_list(t_lexem *list_lexem, int is_redirection)
{
	t_lexem	*tmp;

	while (list_lexem)
	{
		tmp = list_lexem;
		list_lexem = list_lexem->next;
		if (tmp->token <= DOUBLE_QUOTES || is_redirection == 1)
			free(tmp->str);
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}

/** Liberación de memoria dinámica utilizada para almacenar
 * atributos de un comando.
 * 
 * @param cmd Puntero al inicio de la lista de estructuras con información
 * de los comandos.
 * 
 * @return Nada, limpia la lista a través de punteros.
 */
static void	clean_cmd_list(t_single_cmd *cmd)
{
	t_single_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp && tmp->redirection)
			clean_lex_list(tmp->redirection, 1);
		free(tmp->str);
		free(tmp->cmd_path);
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}
