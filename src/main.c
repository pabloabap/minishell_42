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

int	main(void)
{
	t_data	*data;
	int iters=0; //ELIMINAR ANTES DE ENTREGAR, SOLO PARA TEST
	int status;

	last_exit = 0;
	status = init_data(&data);
	while (iters < 5 && EXIT_SUCCESS == status)
	{
		data->input = readline("\033[31mMinishell\033[0m > ");
		add_history(data->input);
		if (data->input && *(data->input) != '\0')
		{
			if(EXIT_SUCCESS == lexer(data->input, &(data->head_lex_list)))
				printf("OK\n");
			ft_lex_to_cmd(&(data->head_lex_list), &(data->head_cmd_list));
			print_cmd(data->head_cmd_list);
		}
		clean_data(data);
		iters ++;
	}
	return (status);
}
