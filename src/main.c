/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:28 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/05/29 18:12:34 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_data	*data;
	int iters=0; //ELIMINAR ANTES DE ENTREGAR, SOLO PARA TEST
	int status;

	status = init_data(&data);
	while (iters < 5)
	{
		data->input = readline("\033[31mMinishell\033[0m > ");
		add_history(data->input);
		if (data->input && *(data->input) != '\0' && status == EXIT_SUCCESS)
		{
			status = lexer(data->input, &(data->head_lex_list));
			//cmd_list = ft_cmd_list_builder (&lexem_list);
			//print_cmd(cmd_list);
		}
		clean_data(data);
		iters ++;
	}
	return (status);
}