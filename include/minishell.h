/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:21:20 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 14:21:28 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>

# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtins.h"
# include "../lib/libft/libft.h"

/*Variable global que almacena el exit status del último comando ejecutado*/
extern int	g_error;

typedef struct s_env
{
    char    **envp_cpy;
}   t_env;

/**Estructura principal desde la que podamos liberar
 * memoría alojada dinámicamente.
*/
typedef struct s_data
{
	t_lexem			*head_lex_list;
	t_single_cmd	*head_cmd_list;
	char			*input;
	t_env			*env;
	int				last_exit;	
}	t_data;

int		init_data(t_data **data);
int		is_whitespace(char c);
void	clean_data(t_data *data);
int		ft_close(int fd, int *err_n);
void	wait_signal(int main_process);
int		ft_parent_exit(int wstatus, int *err_n);

//Error handling
void	err_red_no_file(void);
void	err_pipe_start(void);
void	err_pipe(void);
void	err_malloc_fail(int *err_n);
void	ft_hdoc_close_check(t_lexem *redir, char *line, int *err_n);

#endif