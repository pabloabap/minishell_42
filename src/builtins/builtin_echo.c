/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:08:00 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 20:11:02 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Función auxiliar para imprimir líneas
static void	print_lines(int start_index, char **args, int fd)
{
	int	i;

	i = start_index;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', fd);
		i++;
	}
}

// Implementación del comando 'echo'
void	builtin_echo(char **args, char **envp)
{
	(void)envp; // Ignoramos envp ya que no se utiliza en esta función
	int	i;
	int	j;
	int	n_option;

	i = 1;
	n_option = 0;
	// Manejo de la opción '-n'
	while (args[i] != NULL && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			n_option = 1;
		else
			break ;
		i++;
	}
	// Imprimir los argumentos
	print_lines(i, args, STDOUT_FILENO);
	// Imprimir salto de línea si no se ha especificado la opción '-n'
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
