/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:23:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 20:02:20 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Declaraciones de funciones internas
static char	*find_path_ret(char *str, char **envp);
static int	specific_path(char **envp, char *str);
static void	add_path_to_env(char **envp, char *pwd, char *old_pwd);

// Encuentra el valor de una variable de entorno especificada por `str` en `envp`.
static char	*find_path_ret(char *str, char **envp)
{
    int	i;

    i = 0;
    if (!envp) // Verifica que envp no sea NULL
    {
        ft_putendl_fd("minishell: envp is NULL", STDERR_FILENO);
        return (NULL);
    }
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], str, ft_strlen(str)))
            return (ft_strdup(envp[i] + ft_strlen(str))); // Usa ft_strdup para duplicar la cadena
        i++;
    }
    return (NULL);
}

/** Cambia el directorio actual al valor de la variable de entorno 
 * especificada por `str`.
**/

static int	specific_path(char **envp, char *str)
{
    char	*tmp;
    int		ret;

    tmp = find_path_ret(str, envp);
    if (!tmp)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(str, STDERR_FILENO);
        ft_putendl_fd(" not found", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    ret = chdir(tmp);
    free(tmp); // Usa free para liberar memoria
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
static void	add_path_to_env(char **envp, char *pwd, char *old_pwd)
{
    int		i;
    char	*tmp;

    i = 0;
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

/** Maneja el comando `cd`, cambiando el directorio actual y actualizando el 
 * entorno.
 */

void builtin_cd(char **args, char **envp)
{
    int ret;
    char *pwd = NULL;
    char *old_pwd = NULL;

    // Mensajes de depuración
    ft_putendl_fd("minishell: entrando en builtin_cd", STDERR_FILENO);

    if (!envp) // Verifica que envp no sea NULL
    {
        ft_putendl_fd("minishell: envp es NULL", STDERR_FILENO);
        return;
    }

    // Obtén el directorio actual antes de cambiar de directorio
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        ft_putendl_fd("minishell: error obteniendo old_pwd", STDERR_FILENO);
        return; // Salir temprano si no se pudo obtener old_pwd
    }
    else
        ft_putendl_fd("minishell: old_pwd obtenido correctamente", STDERR_FILENO);

    if (!args[1])
        ret = specific_path(envp, "HOME=");
    else if (ft_strncmp(args[1], "-", 1) == 0)
        ret = specific_path(envp, "OLDPWD=");
    else
    {
        ret = chdir(args[1]);
        if (ret != 0)
        {
            ft_putstr_fd("minishell: error cambiando de directorio a ", STDERR_FILENO);
            ft_putstr_fd(args[1], STDERR_FILENO);
            perror(" ");
            free(old_pwd); // Liberar old_pwd antes de salir temprano
            return; // Salir temprano si chdir falló
        }
    }

    // Obtén el nuevo directorio después de cambiar de directorio
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        ft_putendl_fd("minishell: error obteniendo pwd", STDERR_FILENO);
        free(old_pwd); // Liberar old_pwd antes de salir temprano
        return; // Salir temprano si no se pudo obtener pwd
    }
    else
        ft_putendl_fd("minishell: pwd obtenido correctamente", STDERR_FILENO);

    if (pwd && old_pwd)
        add_path_to_env(envp, pwd, old_pwd);

    // Libera la memoria después de usar pwd y old_pwd
    if (pwd != NULL)
    {
        free(pwd);
        pwd = NULL; // Buena práctica para evitar usar un puntero liberado
    }
    if (old_pwd != NULL)
    {
        free(old_pwd);
        old_pwd = NULL; // Buena práctica para evitar usar un puntero liberado
    }

    ft_putendl_fd("minishell: builtin_cd completado correctamente", STDERR_FILENO);
}