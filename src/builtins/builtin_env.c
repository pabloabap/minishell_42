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

// Implementación del comando 'env'
void	builtin_env(char **args, t_env *env)
{
	int	i;

	(void)args;
	i = 0;
	while (env->envp_cpy[i])
	{
		ft_putendl_fd(env->envp_cpy[i], STDOUT_FILENO);
		i++;
	}
}
