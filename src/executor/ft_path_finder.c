/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:11:42 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 19:11:50 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_initial_checks(t_single_cmd *cmd, t_data *data);
static int	ft_check_path_env(t_single_cmd *cmd, t_data *data);
static int	ft_check_path_dir(t_single_cmd *cmd, char *dir, DIR *actual,
				int *err_n);
static int	ft_check_cmd_not_found(t_single_cmd *cmd, int *err_n);

/** Localiza la ruta del comando.
 *
 * @param cmd_name Nombre del comando a buscar.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 * 
 * @return Ruta absoluta al fichero del comando. 
 */
int	ft_path_finder(t_single_cmd *cmd, t_data *data)
{
	if (EXIT_FAILURE == ft_initial_checks(cmd, data))
		return (EXIT_FAILURE);
	else if (ft_strnstr(cmd->str[0], "/", ft_strlen(cmd->str[0])))
		return (cmd->cmd_path = cmd->str[0], EXIT_SUCCESS);
	else if (!ft_getenv("PATH", data->env->envp_cpy))
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->str[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (data->last_exit = 127, EXIT_FAILURE);
	}
	else if (EXIT_FAILURE == ft_check_path_env(cmd, data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Checks iniciales. Comprueba si el primer argumento del comando simple
 * es un directorio, '.' o '..' para gestionar el error.
 * 
 * @param cmd Puntero a estrucura single command.
 * @param data Puntero a la estrcutura con informacion general
 * del programa, utilizado para actualizar el last_exit status
 * si es necesario.
 * 
 * @return Resultado de la ejecuion. 
*/
static int	ft_initial_checks(t_single_cmd *cmd, t_data *data)
{
	DIR	*dir;

	dir = opendir(cmd->str[0]);
	if (0 == ft_strncmp(cmd->str[0], "..", 3) \
		* ft_strncmp(cmd->str[0], ".", 2))
	{
		ft_putstr_fd(cmd->str[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (free(dir), data->last_exit = 127, EXIT_FAILURE);
	}
	else if (dir || errno == EACCES)
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->str[0], STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		return (free(dir), data->last_exit = 126, EXIT_FAILURE);
	}
	return (free(dir), EXIT_SUCCESS);
}

/** Subfunción de `ft_path_finder` encargada de iterar sobre los directorios
 * de la variable de entorno `$PATH` hasta encontrar el directorio de un
 * comando o terminar de recorrer la lista de directorios.
 *
 * @param cmd Puntero a la estructura con información del comando a procesar.
 * @param data Puntero a la estructura data con datos generales del programa
 * para utilizar o modificar los atributos last_exit y env.
 *
 * @return Resultado de ejecución de la función.
 */
static int	ft_check_path_env(t_single_cmd *cmd, t_data *data)
{
	int		i;
	char	**dirs;
	DIR		*actual;

	if (!is_builtin(cmd->str[0]))
	{
		i = 0;
		dirs = ft_split(ft_getenv("PATH", data->env->envp_cpy), ':');
		if (dirs == NULL)
			err_malloc_fail(&(data->last_exit));
		while (dirs && dirs[i] && cmd->cmd_path == NULL)
		{
			actual = opendir(dirs[i]);
			if (actual == NULL && dirs[i] == NULL)
				return (perror("-minishell "), data->last_exit = errno, 1);
			else if (actual != NULL)
				ft_check_path_dir(cmd, dirs[i], actual, &(data->last_exit));
			free(dirs[i]);
			dirs[i] = NULL;
			i++;
		}
		return (free(dirs), dirs = NULL, ft_check_cmd_not_found(cmd,
				&(data->last_exit)));
	}
	return (EXIT_SUCCESS);
}

/** Subfunción de `ft_check_path_env` encargada iterar sobre los ficheros de
 * 	un directorio para comprobar si contiene el fichero del comando a buscar.
 *
 *  @param cmd Puntero a la estructura con información del comando a procesar.
 *  @param dir String con la ruta del directorio a analizar.
 *  @param actual Estructura dirstream con información de un directorio.
 * 	@param err_n Puntero a int que almacena el errno de la ultima ejecucion
 * 	para modificar el valor si es necesario.
 *
 * 	@return Resultado de ejecución de la función. En caso de encontrarse el
 *  fichero asociado al comando se incluye en el atributo `cmd_path´ de la
 *  estructura del comando.
 */
static int	ft_check_path_dir(t_single_cmd *cmd, char *dir, DIR *actual,
		int *err_n)
{
	struct dirent	*subdir;
	char			*tmp;

	subdir = readdir(actual);
	if (subdir == NULL && *err_n != errno)
		return (perror("-minishell "), *err_n = errno, EXIT_FAILURE);
	while (subdir)
	{
		if (!ft_strncmp(subdir->d_name, cmd->str[0], ft_strlen(cmd->str[0])
				+ 1))
		{
			tmp = ft_strjoin(dir, "/");
			if (!tmp)
				return (err_malloc_fail(err_n), EXIT_FAILURE);
			cmd->cmd_path = ft_strjoin(tmp, subdir->d_name);
			if (!cmd->cmd_path)
				return (free(tmp), err_malloc_fail(err_n), EXIT_FAILURE);
			return (free(tmp), closedir(actual), EXIT_SUCCESS);
		}
		subdir = readdir(actual);
	}
	return (closedir(actual), EXIT_FAILURE);
}

/** Función que comprueba si al final de la busqueda del comando se ha
 * encontrado la ruta del comando. En caso de que no se haya encontrado se
 * imprime el mensaje de error por la salida STDERR y se actualizar el errno
 * de la última ejecución.
 *
 * @param cmd Puntero a la estructura con información del comando a procesar.
 * @param err_n Puntero a int que almacena el errno de la ultima ejecucion
 * para modificar el valor si es necesario.
 *
 * @return Resultado de ejecución de la función.
 */
static int	ft_check_cmd_not_found(t_single_cmd *cmd, int *err_n)
{
	if (cmd->cmd_path == NULL)
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->str[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		*err_n = 127;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
