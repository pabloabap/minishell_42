#include "../../include/minishell.h"
#include <stdlib.h>
#include <stdio.h>

// Función auxiliar para liberar recursos
void free_tools(t_tools *tools)
{
    free_arr(tools->paths);
    free_arr(tools->envp);
    free(tools->args);
    ft_simple_cmdsclear(&tools->simple_cmds);
    free(tools->pwd);
    free(tools->old_pwd);
    if (tools->pipes)
        free(tools->pid);
}

// Función para verificar si una cadena es numérica
int is_str_digit(char *str)
{
    int i = 0;
    while (str[i]) {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

// Función para determinar el código de salida y salir del programa
void determine_exit_code(char **str)
{
    int exit_code;

    if (!str[1])
        exit_code = 0;
    else if (is_str_digit(str[1]))
        exit_code = ft_atoi(str[1]);
    else {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(str[1], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        exit_code = 255;
    }
    free_arr(str);
    exit(exit_code);
}

// Implementación del comando 'exit'
void builtin_exit(void) {
    if (args[1] && args[2]) {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return;
    }
    
    int exit_code = 0;
    if (args[1]) {
        if (is_str_digit(args[1])) {
            exit_code = ft_atoi(args[1]);
        } else {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(args[1], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            exit_code = 255;
        }
    }
    free_arr(envp); // Asegúrate de liberar recursos apropiadamente
    exit(exit_code);
}
