/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:23:43 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 21:00:11 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int variable_exist(char **envp, char *str)
{
    int i;
    int eq_idx;

    eq_idx = equal_sign(str);
    if (eq_idx != -1 && (str[eq_idx + 1] == '\"' || str[eq_idx + 1] == '\''))
        delete_quotes(&str[eq_idx + 1], str[eq_idx + 1]);

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], str, equal_sign(envp[i])) == 0)
        {
            free(envp[i]);
            envp[i] = ft_strdup(str);
            return (1);
        }
        i++;
    }
    return (0);
}
#include "../../include/minishell.h"

// Array de funciones built-in
builtin_func	builtin_arr(char *str)
{
	static struct 
	{
		char		*name;
		builtin_func	func;
	}	builtins[] = {
		{"echo", builtin_echo},
		{"cd", builtin_cd},
		{"pwd", builtin_pwd},
		{"export", builtin_export},
		{"unset", builtin_unset},
		{"env", builtin_env},
		{"exit", builtin_exit}
	};
	size_t	num_builtins;
	size_t	i;

	num_builtins = sizeof(builtins) / sizeof(builtins[0]);
	i = 0;
	while (i < num_builtins)
	{
		if (str && !ft_strncmp(builtins[i].name, str, \
					ft_strlen(builtins[i].name) + 1))
			return (builtins[i].func);
		i++;
	}
	return (NULL);
}

// Verifica si el comando es una función interna
int	is_builtin(char *command)
{
	return (builtin_arr(command) != NULL);
}

// Ejecuta el comando interno correspondiente
/*
void	execute_builtin(char **args, char **envp)
{
	builtin_func	builtin_func;

	builtin_func = builtin_arr(args[0]);
	if (builtin_func != NULL)
		builtin_func(args, envp);
}
*/
void execute_builtin(char **args, char **envp)
{
    builtin_func builtin_func;

    builtin_func = builtin_arr(args[0]);
    if (builtin_func != NULL)
    {
        builtin_func(args, envp); // Se ejecuta la función builtin con envp (que será data->envp_cpy)
    }
}