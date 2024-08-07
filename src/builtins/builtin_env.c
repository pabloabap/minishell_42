#include "../../include/minishell.h"

// Implementación del comando 'env'
void builtin_env(char **args, char **envp) {
    int i = 0;
    (void)args; // Ignoramos args ya que no se utiliza en esta función
    
    while (envp[i]) {
        ft_putendl_fd(envp[i], STDOUT_FILENO);
        i++;
    }
}
