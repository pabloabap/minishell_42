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

// Verifica si el comando es una función interna
int is_builtin(char *command) {
    return (strcmp(command, "cd") == 0 ||
            strcmp(command, "pwd") == 0 ||
            strcmp(command, "unset") == 0 ||
            strcmp(command, "exit") == 0 ||
            strcmp(command, "env") == 0 ||
            strcmp(command, "export") == 0 ||
            strcmp(command, "echo") == 0);
}

// Ejecuta el comando interno correspondiente
void execute_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        builtin_cd(args);
    } else if (strcmp(args[0], "pwd") == 0) {
        builtin_pwd();
    } else if (strcmp(args[0], "unset") == 0) {
        builtin_unset(args);
    } else if (strcmp(args[0], "exit") == 0) {
        builtin_exit();
    } else if (strcmp(args[0], "env") == 0) {
        builtin_env(args);
    } else if (strcmp(args[0], "export") == 0) {
        builtin_export(args);
    } else if (strcmp(args[0], "echo") == 0) {
        builtin_echo(args);
    }
}

