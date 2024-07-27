/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:23:43 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:23:46 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Array de funciones built-in
builtin_func builtin_arr(char *str)
{
    static struct {
        char *name;
        builtin_func func;
    } builtins[] = {
        {"echo", builtin_echo},
        {"cd", builtin_cd},
        {"pwd", builtin_pwd},
        {"export", builtin_export},
        {"unset", builtin_unset},
        {"env", builtin_env},
        {"exit", builtin_exit}
    };

    size_t num_builtins = sizeof(builtins) / sizeof(builtins[0]);
    size_t i = 0;
    while (i < num_builtins) {
        if (str && !ft_strncmp(builtins[i].name, str, ft_strlen(builtins[i].name) + 1)) {
            return builtins[i].func;
        }
        i++;
    }
    return NULL;
}

// Verifica si el comando es una función interna
int is_builtin(char *command) {
    return (builtin_arr(command) != NULL);
}

// Ejecuta el comando interno correspondiente
void execute_builtin(char **args, char **envp) {
    builtin_func builtin_func = builtin_arr(args[0]);

    if (builtin_func != NULL) {
        builtin_func(args, envp);
    }
}
