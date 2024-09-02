/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:28 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/26 11:09:42 by anguil-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			g_error = 0;
static int	ft_preprocesing(t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status;

	if (argc == 1 && ft_strlen(argv[0]) > 0)
	{
		status = init_data(&data, envp);
		while (EXIT_SUCCESS == status)
		{
			ft_readline(data);
			if (data->input && *(data->input) != '\0')
			{
				if (EXIT_SUCCESS == ft_preprocesing(data)
					&& EXIT_SUCCESS == ft_executor(data->head_cmd_list, data))
					data->last_exit = 0;
			}
			else if (!data->input)
				return (ft_putendl_fd("exit", STDERR_FILENO), \
				clean_data(data), ft_final_clean(data), EXIT_SUCCESS);
			clean_data(data);
		}
		ft_final_clean(data);
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

/** Función que agrupa las aciones de lexing, parsing y actualiza el exit
 * status en caso de error.
 *
 * 	@param data	Puntero a las estructuras de datos utilizadas en el programa.
 *
 *  @return Estado de salida de la función.
 */
static int	ft_preprocesing(t_data *data)
{
	if ((EXIT_FAILURE == lexer(data->input, &(data->head_lex_list), data)) || \
		(EXIT_FAILURE == ft_lex_to_cmd(&(data->head_lex_list), \
		&(data->head_cmd_list), &data->last_exit)) || \
		(EXIT_FAILURE == ft_expander(data->head_lex_list, \
		data->head_cmd_list, data)))
	{
		data->last_exit = 2;
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}
