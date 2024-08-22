#include "../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Actualiza la variable de entorno `PWD` y `OLDPWD` en `envp`.
void	add_path_to_env(t_env *env, char *pwd, char *old_pwd)
{
    int		i;
    char	*tmp;
    char	**envp;

    i = 0;
    envp = env->envp_cpy;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], "PWD=", 4))
        {
            tmp = ft_strjoin("PWD=", pwd);
            if (tmp)
            {
                free(envp[i]);
                envp[i] = tmp;
            }
        }
        else if (!ft_strncmp(envp[i], "OLDPWD=", 7) && old_pwd)
        {
            tmp = ft_strjoin("OLDPWD=", old_pwd);
            if (tmp)
            {
                free(envp[i]);
                envp[i] = tmp;
            }
        }
        i++;
    }
}