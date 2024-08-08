/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:24:52 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:24:57 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Funciones para inicializar la estructura en la que
 * centralizaremos todos los elemenetos que usan memoría dinámica
 * para liberarlos facilmente a la finalización de una ejecución.
 * También se configura el gestor de señales del programa principal.
 * 
 * @param data Estructura que contiene los elementos con memoria dinámica del
 * programa
 * 
 * @return Resultado de la ejecución de la función.
 * */

#include "../../include/minishell.h"

int	init_data(t_data **data)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("456-Minishell: t_data malloc fails");
		return (EXIT_FAILURE);
	}
	(*data)->head_lex_list = NULL;
	(*data)->head_cmd_list = NULL;
	(*data)->input = NULL;
	(*data)->last_exit = 0;
	wait_signal(1);
	return (EXIT_SUCCESS);
}
