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
# include <sys/wait.h>          //wait, waitpid
# include <stdio.h>             //printf, perror
# include <readline/readline.h> //readline, add_history, rl_clear_history
# include <readline/history.h>
# include <stdlib.h>            //malloc, free, exit, getenv
# include <unistd.h>            //write, access, read, close, fork, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, isatty ttyname
# include <dirent.h>            //opendir, readdir, closedir
# include <fcntl.h>             //open
# include <signal.h>            //signal, sigaction, kill
# include <string.h>            //strerror
# include <errno.h>             //Define la varibale entera errno con el numero de un error

# include "lexer.h"
# include "parser.h"
# include "../lib/libft/libft.h"

/**Estructura principal desde la que podamos liberar
 * memoría alojada dinámicamente.
*/
typedef struct s_data
{
	t_lexem			*head_lex_list;
	t_single_cmd	*head_cmd_list;
	char			*input;	
}	t_data;

int		init_data(t_data **data);
int		is_whitespace(char c);
void	clean_data(t_data *data);

//Error handling
void	err_red_no_file(void);
void	err_pipe_start(void);
void	err_pipe(void);
void	err_malloc_fail(void);

#endif