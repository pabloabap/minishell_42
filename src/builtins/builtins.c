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
int (*builtin_arr(char *str))(char **args, char **envp) {
    static struct {
        char *name;
        int (*func)(char **args, char **envp);
    } builtins[] = {
        {"echo", builtin_echo},
        {"cd", builtin_cd},
        {"pwd", builtin_pwd},
        {"export", builtin_export},
        {"unset", builtin_unset},
        {"env", builtin_env},
        {"exit", builtin_exit}
    };

    int i = 0;
    while (i < sizeof(builtins) / sizeof(builtins[0])) {
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
    int (*builtin_func)(char **args, char **envp);

    builtin_func = builtin_arr(args[0]);
    if (builtin_func != NULL) {
        builtin_func(args, envp);
    }
}
Ajustes en el flujo principal
Finalmente, asegúrate de que el flujo principal en executor.c o donde se manejen los comandos revise y ejecute las builtins de esta manera:

c
Copiar código
#include "../../include/minishell.h"

int ft_executor(t_single_cmd *head, char **envp) {
    int main_out;
    int pid;

    if (EXIT_FAILURE == ft_prepare_exec(head, &main_out))
        return (EXIT_FAILURE);
    while (head) {
        // Verificar si el comando es una builtin
        if (is_builtin(head->str[0])) {
            // Ejecutar builtin
            execute_builtin(head->str, envp);
        } else {
            pid = fork();
            if (pid == -1)
                return (perror("02_Minishell"), EXIT_FAILURE);
            if (pid == 0)
                ft_child_mng(head, main_out, envp);
            if (EXIT_FAILURE == ft_parent_mng(&head))
                return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}
