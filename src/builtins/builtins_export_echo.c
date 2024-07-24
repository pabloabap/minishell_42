/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:24:07 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:24:08 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Implementación del comando 'export'
void builtin_export(char **args) {
    int i = 1;
    while (args[i] != NULL) {
        char *env_var = strdup(args[i]);
        putenv(env_var);
        i++;
    }
}

// Implementación del comando 'echo'
void builtin_echo(char **args) {
    int i = 1;
    int newline = 1;
    if (strcmp(args[1], "-n") == 0) {
        newline = 0;
        i++;
    }
    while (args[i] != NULL) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL) {
            printf(" ");
        }
        i++;
    }
    if (newline) {
        printf("\n");
    }
}

