#include "../../include/minishell.h"

// Declaraciones de funciones internas
static char *find_path_ret(char *str, char **envp);
static int specific_path(char **envp, char *str);
static void add_path_to_env(char **envp, char *pwd, char *old_pwd);

// Encuentra el valor de una variable de entorno especificada por `str` en `envp`.
static char *find_path_ret(char *str, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], str, ft_strlen(str)))
            return (ft_strdup(envp[i] + ft_strlen(str))); // Usa ft_strdup para duplicar la cadena
        i++;
    }
    return (NULL);
}

// Cambia el directorio actual al valor de la variable de entorno especificada por `str`.
static int specific_path(char **envp, char *str)
{
    char *tmp;
    int ret;

    tmp = find_path_ret(str, envp);
    if (!tmp)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(str, STDERR_FILENO);
        ft_putendl_fd(" not found", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    ret = chdir(tmp);
    free(tmp);  // Usa free para liberar memoria
    if (ret != 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(str, STDERR_FILENO);
        ft_putendl_fd(" not set", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// Actualiza la variable de entorno `PWD` y `OLDPWD` en `envp`.
static void add_path_to_env(char **envp, char *pwd, char *old_pwd)
{
    int i;
    char *tmp;

    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], "PWD=", 4))
        {
            tmp = ft_strjoin("PWD=", pwd);
            free(envp[i]);
            envp[i] = tmp;
        }
        else if (!ft_strncmp(envp[i], "OLDPWD=", 7) && old_pwd)
        {
            tmp = ft_strjoin("OLDPWD=", old_pwd);
            free(envp[i]);
            envp[i] = tmp;
        }
        i++;
    }
}

// Maneja el comando `cd`, cambiando el directorio actual y actualizando el entorno.
void builtin_cd(char **args, char **envp)
{
    int ret;
    char *pwd = NULL;    // Define `pwd` y `old_pwd` como NULL o valores por defecto
    char *old_pwd = NULL;

    if (!args[1])
        ret = specific_path(envp, "HOME=");
    else if (ft_strncmp(args[1], "-", 1) == 0)
        ret = specific_path(envp, "OLDPWD=");
    else
    {
        ret = chdir(args[1]);
        if (ret != 0)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(args[1], STDERR_FILENO);
            perror(" ");
        }
    }
    if (ret != 0)
        return;
    // Aquí deberías obtener `pwd` y `old_pwd` antes de llamar a `add_path_to_env`
    // Suponiendo que `pwd` y `old_pwd` se obtienen de alguna manera.
    add_path_to_env(envp, pwd, old_pwd);
}

