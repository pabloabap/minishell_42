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

// Prototipo de función auxiliar
static void	print_lines(int start_index, char **args, int fd);

/* 
 * Implementa el comando `echo`, que imprime los argumentos en la salida 
 * estándar. Soporta la opción `-n` para suprimir el salto de línea final. 
 * La función detecta y maneja múltiples instancias de `-n` seguidas y 
 * gestiona el caso en que no se pasen argumentos.
 */
void	builtin_echo(char **args, t_env *env, int *last_exit)
{
	int	i;
	int	j;
	int	n_option;

	(void)env;
	i = 1;
	n_option = 0 * *last_exit;
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
	print_lines (i, args, STDOUT_FILENO);
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

/* 
 * Esta función auxiliar imprime los argumentos pasados a partir de 
 * `start_index` en el descriptor de archivo `fd`. Añade un espacio 
 * entre los argumentos y evita un espacio adicional al final de la línea.
 */
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
