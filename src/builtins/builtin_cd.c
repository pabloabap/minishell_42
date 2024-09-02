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
static void	print_error(char *msg);
static char	*find_path_ret(char *str, t_env *env);
static int	specific_path(t_env *env, char *str);
static int	change_directory(char *path, char *dir, int *last_exit);

/* Implementa la funcionalidad del comando `cd`. Cambia el directorio 
 * actual según los argumentos proporcionados y actualiza las variables 
 * de entorno correspondientes (`PWD` y `OLDPWD`). Maneja también errores 
 * potenciales en el proceso de cambio de directorio.
 */
void	builtin_cd(char **args, t_env *env, int *last_exit)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (print_error("-minishell: Failure getting old_pwd"));
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

/* Imprime un mensaje de error en la salida estándar de error (STDERR). 
 * Se utiliza para notificar al usuario sobre fallos en la ejecución del 
 * comando `cd`.
 */
static void	print_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
}

/* Cambia el directorio actual utilizando el valor de una variable de 
 * entorno específica (como `HOME` u `OLDPWD`). Si la variable no se 
 * encuentra o no está definida, maneja los errores de manera apropiada.
 */
static int	specific_path(t_env *env, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, env);
	if (!tmp)
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(" not found", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(" not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* Busca y devuelve el valor de la variable de entorno especificada por 
 * `str` dentro del entorno proporcionado `env`. Retorna una copia del 
 * valor encontrado o NULL si no se encuentra la variable.
 */
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

/* Cambia el directorio actual a una ruta específica `path`. Maneja los 
 * errores en caso de que el cambio de directorio falle, actualizando la 
 * variable `last_exit` para reflejar el estado del comando.
 */
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
