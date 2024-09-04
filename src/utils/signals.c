/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:10:13 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 19:10:29 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	main_handler(int signal);
static void	child_handler(int signal);

/** Gestor de señales SIGINT y SIGQUIT, que tendrán distinto comportamineto
 * al que tienen por defecto. Dependiendo de si el programa está en el 
 * proceso principal o hijo, las señales tendrán distinto comportamiento.
 * 
 * @param main_process Indicador de si la función ha sido invocada desde el
 * proceso principal o un proceos hijo para establecer la configuración. 
 */
void	wait_signal(int main_process)
{
	struct sigaction	sa;

	g_error = 0;
	if (main_process)
		sa.sa_handler = &main_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/** Función que define el comportamiento personalizado de las señales a
 * modificar en el proceso principal.
 * 
 * @param signal Número de la señal recibida.
 * 
 * @return No devuelve nada directamente pero atualiza el valor de la
 * variable global g_error en caso de necesitarlo. 
 */
static void	main_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_error = SIGINT;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

/** Función que define el comportamiento personalizado de las señales a
 * modificar en procesos hijo.
 * 
 * @param signal Número de la señal recibida.
 * 
 * @return No devuelve nada directamente pero atualiza el valor de la
 * variable global g_error en caso de necesitarlo. 
 */
static void	child_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_error = SIGINT;
	}
	else if (signal == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
		g_error = SIGQUIT;
	}
	return ;
}
