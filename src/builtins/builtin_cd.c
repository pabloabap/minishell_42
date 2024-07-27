#include "../../include/minishell.h"

// Declaraciones de funciones internas
static char *find_path_ret(char *str, char **envp);
static int specific_path(char **envp, char *str);
static void add_path_to_env(t_data *data);
static void change_path(t_data *data);

// Encuentra el valor de una variable de entorno especificada por `str` en `envp`.
static char *find_path_ret(char *str, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], str, ft_strlen(str)))
            return (ft_substr(envp[i], ft_strlen(str),
                    ft_strlen(envp[i]) - ft_strlen(str)));
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
    free(tmp);
    if (ret != 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(str, STDERR_FILENO);
        ft_putendl_fd(" not set", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// Actualiza la variable de entorno `PWD` y `OLDPWD` en `data->envp`.
static void add_path_to_env(t_data *data)
{
    int i;
    char *tmp;

    i = 0;
    while (data->envp[i])
    {
        if (!ft_strncmp(data->envp[i], "PWD=", 4))
        {
            tmp = ft_strjoin("PWD=", data->pwd);
            free(data->envp[i]);
            data->envp[i] = tmp;
        }
        else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7) && data->old_pwd)
        {
            tmp = ft_strjoin("OLDPWD=", data->old_pwd);
            free(data->envp[i]);
            data->envp[i] = tmp;
        }
        i++;
    }
}

// Maneja el comando `cd`, cambiando el directorio actual y actualizando el entorno.
void builtin_cd(char **args)
{
    int ret;
    t_data *data; // Asegúrate de que esta variable esté correctamente inicializada en otro lugar

    if (!args[1])
        ret = specific_path(data->envp, "HOME=");
    else if (ft_strncmp(args[1], "-", 1) == 0)
        ret = specific_path(data->envp, "OLDPWD=");
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

    change_path(data);
    add_path_to_env(data);
}

