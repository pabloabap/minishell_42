// CABECERA

#include "../../include/minishell.h"

/** Localiza la ruta del comando.
 * 
 * @param cmd_name Nombre del comando a buscar.
 * 
 * @return Ruta absoluta al fichero del comando. 
 */
char	*ft_path_finder(t_single_cmd *cmd, int *err_n)
{
	char			**dirs;
	int				i;
	DIR				*actual;
	struct dirent	*subdir;
	dirs = ft_split(getenv("PATH"), ':');
	i = 0;
	if (0 == 1) //ESCRITO PARA NO DAR ERRROR AL NO USAR ERR_NO - BORRAR
		write(STDIN_FILENO, err_n, 1); //BORRAR
	while (dirs && dirs[i])
	{
		actual = opendir(dirs[i]);
		if (actual != NULL)
		{
			subdir = readdir(actual);
			while (subdir)
			{
				if (!ft_strncmp(subdir->d_name, cmd->str[0], ft_strlen(cmd->str[0])) \
					&& ft_strlen(subdir->d_name) == ft_strlen(cmd->str[0]))
					return (ft_strjoin(ft_strjoin(dirs[i], "/"), subdir->d_name));
				subdir = readdir(actual);
			}
			closedir(actual);
		}
		free(dirs[i]);
		dirs[i] = NULL;
		i++;
	}
	free(dirs);
	dirs = NULL;
	return (NULL);
}
/*
ft_absolut_path_check
{

}
ft_relative_to_absolute
{

}

ft_find_cmd
{

}
*/