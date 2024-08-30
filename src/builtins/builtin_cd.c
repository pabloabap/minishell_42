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

// Declaraciones de funciones internas
static char	*find_path_ret(char *str, t_env *env);
static int	specific_path(t_env *env, char *str);
static int	change_directory(char *path, char *dir, int *last_exit);

// Encuentra el valor de una var de env especificada por `str` en `envp`.
static char	*find_path_ret(char *str, t_env *env)
{
	int		i;
	char	**envp;

	i = 0;
	envp = env->envp_cpy;
	if (!envp)
	{
		ft_putendl_fd("-minishell: envp is NULL", STDERR_FILENO);
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

static void	print_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
}

/* Maneja el comando `cd`, cambiando el directorio actual y actualizando el 
 * entorno.
 */
void	builtin_cd(char **args, t_env *env, int *last_exit)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (print_error("minishell: error obteniendo old_pwd"));
	if (!args[1])
		specific_path(env, "HOME=");
	else if (ft_strncmp(args[1], "-", 1) == 0)
	{
		specific_path(env, "OLDPWD=");
		builtin_pwd(args, env, last_exit);
	}
	else
		change_directory(args[1], old_pwd, last_exit);
	pwd = getcwd(NULL, 0);
	if (pwd && old_pwd)
	{
		update_pwd(env, pwd);
		update_oldpwd(env, old_pwd);
	}
	free(pwd);
	free(old_pwd);
}

// Cambite vuea el directorio a una ruta específica y maneja errores.

static int	change_directory(char *path, char *dir, int *last_exit)
{
	int	ret;

	(void)dir;
	ret = chdir(path);
	if (ret != 0 && path[0])
	{
		ft_putstr_fd("-minishell: cd: ", STDERR_FILENO);
		perror(path);
		return (*last_exit = 1, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
