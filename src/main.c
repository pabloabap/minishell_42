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

//int	g_last_exit = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int iters=0; //ELIMINAR ANTES DE ENTREGAR, SOLO PARA TEST
	int status;

	if (1 || (argc == 1 && 0 == ft_strncmp(argv[0], "./minishell", 11)))
	{
		status = init_data(&data);
		data->last_exit = 0;
		while (iters < 10 && EXIT_SUCCESS == status)
		{
			data->input = readline("\033[31mMinishell\033[0m > ");
			add_history(data->input);
			if (data->input && *(data->input) != '\0')
			{
				if((EXIT_FAILURE == lexer(data->input, &(data->head_lex_list))) || \
					(EXIT_FAILURE == ft_lex_to_cmd(&(data->head_lex_list), \
						&(data->head_cmd_list))) ||
					(EXIT_FAILURE == ft_expander(data->head_lex_list, \
					data->head_cmd_list, data->last_exit)))
					data->last_exit = EXIT_FAILURE;
				else
					if (EXIT_FAILURE == ft_executor(data->head_cmd_list, envp))
						data->last_exit = errno;
			}
			clean_data(data);
			iters ++;
		}
		free(data);
	}
	return (status);
}
