// CABECERA

/**
 * Funciones para inicializar la estructura en la que
 * centralizaremos todos los elemenetos que usan memoría dinámica
 * para liberarlos facilmentel a la finalización de una ejecución.
 * */

#include "../../include/minishell.h"

int init_data(t_data **data)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("Minishell: t_data malloc fails");
		return (EXIT_FAILURE);
	}
	(*data)->head_lex_list = NULL;
	(*data)->head_cmd_list = NULL;
	(*data)->input = NULL;
	return (EXIT_SUCCESS);	
}