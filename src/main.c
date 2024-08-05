/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:28 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 12:37:20 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_readline(t_data *data);
static int	ft_preprocesing(t_data *data);
int	g_error = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status;
	int		iters=0; //ELIMINAR ANTES DE ENTREGAR, SOLO PARA TEST

	if (argc == 1 && 0 == ft_strncmp(argv[0], "./minishell", 11))
	{
		status = init_data(&data);
		while (iters < 5 && EXIT_SUCCESS == status)
		{
			ft_readline(data);
			if (data->input && *(data->input) != '\0')
			{
				if (EXIT_SUCCESS == ft_preprocesing(data) && EXIT_SUCCESS == \
				ft_executor(data->head_cmd_list, envp, &data->last_exit))
					data->last_exit = 0;
			}
			else if (!data->input)
				return (ft_putendl_fd("exit", STDERR_FILENO), \
				clean_data(data), free(data), EXIT_SUCCESS);
			clean_data(data);
			iters ++;
		}
		free(data);
	}
	return (status);
}

/** Función que lee y almacena en historial inputs dados por el usuario.
 * En caso de que la variable global de error sea distinta de cero, 
 * actualiza el último estado de salida del programa.
 * 
 * @param data	Puntero a las estructuras de datos utilizadas en el programa.
 * 
 *  @return Nada, actualiza el último estado de salida del programa si
 *  la variable gloabl de error es distinta de cero.
 */
static void	ft_readline(t_data *data)
{
	data->input = readline("Minishell% ");
	if (g_error != 0)
		data->last_exit = g_error + 128;
	add_history(data->input);
}

/** Función que agrupa las aciones de lexing, parsing y actualiza el exit
 * status en caso de error.
 * 
 * 	@param data	Puntero a las estructuras de datos utilizadas en el programa.
 * 
 *  @return Estado de salida de la función.
 */
static int	ft_preprocesing(t_data *data)
{
	if ((EXIT_FAILURE == lexer(data->input, &(data->head_lex_list))) || \
		(EXIT_FAILURE == ft_lex_to_cmd(&(data->head_lex_list), \
		&(data->head_cmd_list))) || \
		(EXIT_FAILURE == ft_expander(data->head_lex_list, \
		data->head_cmd_list, data->last_exit)))
	{
		data->last_exit = 2;
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}
