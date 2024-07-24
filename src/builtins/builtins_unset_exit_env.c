/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset_exit_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:24:14 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:24:15 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Implementación del comando 'unset'
void builtin_unset(char **args) {
    int i = 1;
    while (args[i] != NULL) {
        unsetenv(args[i]);
        i++;
    }
}

// Implementación del comando 'exit'
//void builtin_exit(char **args) {
void builtin_exit(void) {
    exit(0);
}

// Implementación del comando 'env'
//void builtin_env(char **args) {
void builtin_env(char **environ) {
    //extern char **environ;
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

