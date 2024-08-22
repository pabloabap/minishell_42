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
static char	*find_path_ret(char *str, t_env *env);
static int	specific_path(t_env *env, char *str);
static int	change_directory(char *path, char *dir);
static void	update_paths(t_env *env, char *old_pwd, char *pwd);

// Encuentra el valor de una var de env especificada por `str` en `envp`.
static char	*find_path_ret(char *str, t_env *env)
{
	int		i;
	char	**envp;

	i = 0;
	envp = env->envp_cpy;
	if (!envp)
	{
		ft_putendl_fd("minishell: envp is NULL", STDERR_FILENO);
		return (NULL);
	}
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			return (
				ft_strdup(envp[i] + ft_strlen(str))
			);
		i++;
	}
	return (NULL);
}

/* Cambia el directorio actual al valor de la variable de entorno 
 * especificada por `str`.
 */
static int	specific_path(t_env *env, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, env);
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

/* Maneja el comando `cd`, cambiando el directorio actual y actualizando el 
 * entorno.
 */
void	builtin_cd(char **args, t_env *env)
{
	char	*pwd;
	char	*old_pwd;

	pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		ft_putendl_fd("minishell: error obteniendo old_pwd", STDERR_FILENO);
		return ;
	}
	if (!args[1])
		specific_path(env, "HOME=");
	else if (ft_strncmp(args[1], "-", 1) == 0)
		specific_path(env, "OLDPWD=");
	else
		change_directory(args[1], old_pwd);
	pwd = getcwd(NULL, 0);
	if (pwd && old_pwd)
		update_paths(env, old_pwd, pwd);
	free(pwd);
	free(old_pwd);
}

/* Cambia el directorio a una ruta específica y maneja errores.
 */
static int	change_directory(char *path, char *dir)
{
	int	ret;

	ret = chdir(path);
	if (ret != 0)
	{
		ft_putstr_fd("minishell: error cambiando de directorio a ", \
			STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		perror("");
		free(dir);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* Actualiza las variables de entorno `PWD` y `OLDPWD` en `env`.
 */
static void	update_paths(t_env *env, char *old_pwd, char *pwd)
{
	if (pwd && old_pwd)
		add_path_to_env(env, pwd, old_pwd);
}
