#include "../../include/minishell.h"

// Función auxiliar para eliminar una variable del array
char **whileloop_del_var(char **arr, char **rtn, char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (arr[i] != NULL) {
        // Verifica si la variable actual no coincide con la variable a eliminar
        if (!(ft_strncmp(arr[i], str, equal_sign(arr[i]) - 1) == 0
                && str[equal_sign(arr[i])] == '\0'
                && arr[i][ft_strlen(str)] == '=')) {
            rtn[j] = ft_strdup(arr[i]);
            if (rtn[j] == NULL) {
                free_arr(rtn);
                return (rtn);
            }
            j++;
        }    
        i++;
    }
    return (rtn);
}

// Función para eliminar una variable del array de variables de entorno
char **del_var(char **arr, char *str)
{
    char **rtn;
    size_t i;

    i = 0;
    while (arr[i] != NULL)
        i++;
    rtn = ft_calloc(sizeof(char *), i);
    if (!rtn)
        return (NULL);
    rtn = whileloop_del_var(arr, rtn, str);
    return (rtn);
}

// Función para manejar errores en el comando unset
int unset_error(t_simple_cmds *simple_cmd)
{
    int i;

    i = 0;
    if (!simple_cmd->str[1]) {
        ft_putendl_fd("minishell: unset: not enough arguments", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    while (simple_cmd->str[1][i]) {
        if (simple_cmd->str[1][i++] == '/') {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(simple_cmd->str[1], STDERR_FILENO);
            ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
            return (EXIT_FAILURE);
        }
    }
    if (equal_sign(simple_cmd->str[1]) != 0) {
        ft_putendl_fd("minishell: unset: not a valid identifier", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// Implementación del comando 'unset'
int builtin_unset(t_tools *tools, t_simple_cmds *simple_cmd)
{
    char **tmp;

    if (unset_error(simple_cmd) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    else {
        tmp = del_var(tools->envp, simple_cmd->str[1]);
        free_arr(tools->envp);
        tools->envp = tmp;
    }
    return (EXIT_SUCCESS);
}

