/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:11:14 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 20:14:04 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
 * Implementación del comando `env`, que imprime todas las variables de 
 * entorno almacenadas en `env->envp_cpy`. La función itera a través de la 
 * copia del entorno y escribe cada variable en la salida estándar, una por 
 * línea. No toma en cuenta los argumentos pasados, ya que simplemente 
 * muestra el entorno actual.
 */
void	builtin_env(char **args, t_env *env, int *last_exit)
{
	int	i;

	(void)args;
	i = 0 * *last_exit;
	while (env->envp_cpy[i])
	{
		ft_putendl_fd(env->envp_cpy[i], STDOUT_FILENO);
		i++;
	}
}
