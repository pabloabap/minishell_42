#include "../../include/minishell.h"

// Implementación del comando 'env'
int builtin_env(t_tools *tools, t_simple_cmds *simple_cmd)
{
    int i = 0;

    (void) simple_cmd; // Ignoramos simple_cmd ya que no se utiliza en esta función

    while (tools->envp[i]) {
        ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
        i++;
    }

    return (EXIT_SUCCESS);
}

