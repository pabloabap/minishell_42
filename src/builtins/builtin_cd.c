#include "../../include/minishell.h"

// Función auxiliar para encontrar la ruta en las variables de entorno
char *find_path_ret(char *str, char **envp)
{
    int i = 0;

    while (envp[i]) {
        if (!ft_strncmp(envp[i], str, ft_strlen(str))) {
            return ft_substr(envp[i], ft_strlen(str), ft_strlen(envp[i]) - ft_strlen(str));
        }
        i++;
    }
    return NULL;
}

// Función para cambiar a una ruta específica basada en una variable de entorno
int specific_path(char **envp, char *str)
{
    char *tmp;
    int ret;

    tmp = find_path_ret(str, envp);
    ret = chdir(tmp);
    free(tmp);
    if (ret != 0) {
        str = ft_substr(str, 0, ft_strlen(str) - 1);
        ft_putstr_fd(str, STDERR_FILENO);
        free(str);
        ft_putendl_fd(" not set", STDERR_FILENO);
    }
    return ret;
}

// Función para actualizar las rutas en las variables de entorno
void add_path_to_env(char **envp, char *new_pwd, char *old_pwd)
{
    int i = 0;
    char *tmp;

    while (envp[i]) {
        if (!ft_strncmp(envp[i], "PWD=", 4)) {
            tmp = ft_strjoin("PWD=", new_pwd);
            free(envp[i]);
            envp[i] = tmp;
        } else if (!ft_strncmp(envp[i], "OLDPWD=", 7) && old_pwd) {
            tmp = ft_strjoin("OLDPWD=", old_pwd);
            free(envp[i]);
            envp[i] = tmp;
        }
        i++;
    }
}

// Implementación del comando 'cd'
int builtin_cd(char **args, char **envp)
{
    int ret;
    char *old_pwd = getcwd(NULL, 0);
    char *new_pwd;

    if (!args[1]) {
        ret = specific_path(envp, "HOME=");
    } else if (ft_strncmp(args[1], "-", 1) == 0) {
        ret = specific_path(envp, "OLDPWD=");
    } else {
        ret = chdir(args[1]);
        if (ret != 0) {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(args[1], STDERR_FILENO);
            perror(" ");
        }
    }

    if (ret == 0) {
        new_pwd = getcwd(NULL, 0);
        add_path_to_env(envp, new_pwd, old_pwd);
        free(new_pwd);
    }

    free(old_pwd);
    return ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

