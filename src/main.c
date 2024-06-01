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

#include "../include/main.h"
//#ifndef READLINE_LIBRARY
//# define READLINE_LIBRARY
//#endif
//#include <stdio.h>
////#include "../lib/readline/history.h"
////#include "../lib/readline/readline.h"
//#include <readline/readline.h>
//#include <readline/history.h>

int main(void)
{
	char *text;

	text = readline("Introduce texto");
	printf("HAS ESCRITO: %s\n", text);
	return (0);
}
