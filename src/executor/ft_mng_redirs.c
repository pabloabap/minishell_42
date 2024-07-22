//CABECERA

#include "../../include/minishell.h"

static int	ft_open_redirs(t_lexem *redir);
static int	ft_dup_manage(int fd, t_lexem *redir);
static int	ft_heredoc_creation(t_lexem *redir);

/** Función principal de gestion de las redirecciones.
 * 
 * @param redirs Puntero a la cabecera de la lista `t_lexem`
 * que contine las redirecciones a aplicar a un comando.
 * 
 * @return Resultado de ejecución de la función.
 */

int	ft_prepare_redirections(t_lexem *redirs)
{
	while (redirs)
	{
		if (EXIT_FAILURE == ft_open_redirs(redirs))
			return (EXIT_FAILURE);
		redirs = redirs->next;
	}
	return (EXIT_SUCCESS);
}

/** Función para abrir los ficheros de redirección con las configuraciones
 * especificas para cada uno.
 * 
 * @param redirs Puntero la redirecci'on a tratar.
 *  * 
 * @return Resultado de ejecución e impresioón de error si existe. 
 */
static int	ft_open_redirs(t_lexem *redir)
{
	int	fd;

	if (redir->token == IN_REDIR)
		fd = open(redir->str, O_RDONLY);
	if (redir->token == OUT_REDIR)
		fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (redir->token == APPEND_REDIR)
		fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, \
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (redir->token >= HERE_DOC)
		fd = ft_heredoc_creation(redir);
	if (fd < 0)
		return (perror("12_Minishell "), EXIT_FAILURE);
	else
	{
		if (EXIT_FAILURE == ft_dup_manage(fd, redir))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/** Ajuste de STDIN y STDOUT para que apunten a los ficheros de redirección
 * que les corresponde.
 * 
 * @param fd File descriptor del que duplicar la referencia.
 * @param redirs Puntero la redirecci'on a tratar.
 * 
 * @return Resultado de ejecución de la función.
 */

static int	ft_dup_manage(int fd, t_lexem *redir)
{
	if (redir->token == IN_REDIR || redir->token >= HERE_DOC)
	{
		if (0 > dup2(fd, STDIN_FILENO))
			return (close (fd), perror("13_Minishell "), EXIT_FAILURE);
	}
	else if (redir->token == OUT_REDIR || redir->token >= APPEND_REDIR)
	{
		if (0 > dup2(fd, STDOUT_FILENO))
			return (close (fd), perror("14_Minishell "), EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}

/** Función para tratar los heredoc.
 *  
 * @param redir Puntero a la redirección a tratar.
 * 
 * @return Resultado de la ejecución.
 */

static int	ft_heredoc_creation(t_lexem *redir)
{
	printf ("HDOC DEL - %s\n", redir->str);
	return (EXIT_FAILURE);
}
