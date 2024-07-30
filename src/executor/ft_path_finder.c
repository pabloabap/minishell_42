// CABECERA

#include "../../include/minishell.h"

/** Localiza la ruta del comando.
 * 
 * @param cmd_name Nombre del comando a buscar.
 * 
 * @return Ruta absoluta al fichero del comando. 
 */
char	*ft_path_finder(char *cmd_name)
{
	char			**dirs;
	int				i;
	DIR				*actual;
	struct dirent	*subdir;
	dirs = ft_split(getenv("PATH"), ':');
	i = 0;
	while (dirs && dirs[i])
	{
		actual = opendir(dirs[i]);
		if (actual != NULL)
		{
			subdir = readdir(actual);
			while (subdir)
			{
				if (!ft_strncmp(subdir->d_name, cmd_name, ft_strlen(cmd_name)) \
					&& ft_strlen(subdir->d_name) == ft_strlen(cmd_name))
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