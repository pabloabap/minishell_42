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
	char	*input;
	t_lexem	*lexem_list;
	int iters=0;

	while (iters < 2)
	{
		input = readline("\033[31mMinishell\033[0m > ");
		add_history(input);
		if (*input)
		{
			lexem_list = lexer(input);
			free(input);
			free_cleaner(lexem_list);
		}
		iters ++;
	}
	return (0);
}