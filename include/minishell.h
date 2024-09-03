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

# include "../lib/libft/libft.h"

/*Variable global que almacena el exit status del último comando ejecutado*/
extern int		g_error;

/* Estructura para almacenar la copia de las variables de entorno*/
typedef struct s_env
{
	char	**envp_cpy;
	char	**export_cpy;
}	t_env;

/*Enumeración de posibles tokens a utilizar*/
typedef enum e_tokens
{
	WORD			,
	COMPLEX_WORD	,
	SINGLE_QUOTES	,
	DOUBLE_QUOTES	,
	PIPE			,
	IN_REDIR		,
	OUT_REDIR		,
	APPEND_REDIR	,
	HERE_DOC		,
	SINGLE_QUO_RED
}	t_tokens;

/*Estructures para almacenar info de los lexemas*/
typedef struct s_lexem
{
	char			*str; //word or token
	int				token; //classify the item
	struct s_lexem	*prev; //Pointer to previous item of lexer list
	struct s_lexem	*next; //Pointer to next item of lexer list    
}	t_lexem;

/*Estructures para almacenar info de los comandos de los lexemas*/
typedef struct s_single_cmd
{
	char				**str;
	char				*cmd_path;
	t_lexem				*redirection;
	int					fd_hdoc;
	int					pipe_fd[2];
	struct s_single_cmd	*prev;
	struct s_single_cmd	*next;
}	t_single_cmd;

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

int				init_data(t_data **data, char **envp);
int				ft_is_whitespace(char c);
void			clean_data(t_data *data);
void			ft_final_clean(t_data *data);
int				ft_close(int fd, int *err_n);
void			wait_signal(int main_process);
int				ft_parent_exit(int wstatus, int *err_n);
char			*ft_getenv(char *var_name, char **envp);
void			ft_sleep(int seconds);

//Error handling
void			err_red_no_file(void);
void			err_pipe_start(void);
void			err_pipe(void);
void			err_malloc_fail(int *err_n);
void			ft_hdoc_close_check(t_lexem *redir, char *line, int *err_n);

//__________________FT_READLINE______________
void			ft_readline(t_data *data);
int				ft_jump_irrelevant_character(char *str, int *i);

//___________________LEXER___________________
int				token_lex_fill(char *str, t_lexem **lexem_item, \
					t_tokens token);
int				lexer(char *str, t_lexem **head_lex_list, t_data *data);
t_lexem			*ft_lstlex(t_lexem *lst);
void			ft_consecutive_quotes(char **end_quote, char quote_type);
void			ft_str_lex_check(t_lexem **lexem_item, char quote_type);
char			**ft_consecutive_split(char const *s, char c);
int				ft_check_complex_str(char	*str);
int				ft_handle_complex_str(char **str, int parts, \
					t_lexem **lexem_item, t_data *data);
int				ft_join_parts(char **src, t_lexem **dst, t_data *data);
//___________________PARSER___________________
int				ft_cmd_list_builder(t_lexem *lex_list, t_single_cmd **cmd, \
					int *err_n);
t_single_cmd	*ft_lstcmd(t_single_cmd *lst);
void			ft_add_redirection(t_single_cmd *cmd, t_lexem *r);
int				grammar_checks(t_lexem *lex_list);
int				cmd_len(t_lexem *lex_list);
int				ft_lex_to_cmd(t_lexem **head_lex_list, t_single_cmd **cmd, \
					int *err_n);
void			ft_redirection_quotes(t_lexem *lex_list);

//___________________EXPANDER___________________
int				ft_expander(t_lexem *lex_list, t_single_cmd *cmd_list, \
					t_data *data);
int				ft_has_expansion(char *str);
int				ft_expansion_malloc(char **dst, t_lexem *src, int *buff, \
					t_data *data);
int				ft_fill_expansion(char *dst, t_lexem *src, int *buff, \
					t_data *data);
int				ft_expansion_replace(char *exp_malloc, t_lexem *lex_list);

//___________________EXECUTOR___________________
int				ft_executor(t_single_cmd *head, t_data	*data);
int				ft_prepare_redirections(t_single_cmd *cmd, int *err_n);
int				ft_set_pipes(t_single_cmd *current_cmd, int std_out, \
					int *err_n);
int				ft_check_hdoc(t_single_cmd *cmd, t_data *data);
int				ft_path_finder(t_single_cmd *cmd, t_data *data);

//___________________BUILTINS___________________
// Declaraciones de las funciones internas
void			builtin_cd(char **args, t_env *env, int *last_exit);
void			builtin_pwd(char **args, t_env *env, int *last_exit);
void			builtin_unset(char **args, t_env *env, int *last_exit);
void			builtin_exit(char **args, t_env *env, int *last_exit);
void			builtin_env(char **args, t_env *env, int *last_exit);
void			builtin_export(char **args, t_env *env, int *last_exit);
void			builtin_echo(char **args, t_env *env, int *last_exit);

typedef void	(*t_builtin_func)(char **args, t_env *env, int *last_exit);

/* Estructura para los built-ins */
typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}	t_builtin;

t_builtin_func	builtin_arr(char *str);

int				is_builtin(char *command);
int				execute_builtin(char **args, t_env *env, int *last_exit);
char			**add_var(char **arr, char *str);
void			whileloop_add_var(char **arr, char **rtn, char *str);
void			update_pwd(t_env *env, char *pwd);
void			update_oldpwd(t_env *env, char *old_pwd);
char			**free_arr(char **arr, int len);

// Declaraciones de las funciones faltantes
int				equal_sign(const char *str);
void			delete_quotes(char *str, char quote_char);
void			mini_env(t_env *env, t_single_cmd *simple_cmd);
int				variable_exist(t_env *env, char *str);
void			handle_export_errors(char *str, int *last_exit);
int				is_valid_identifier(const char *str);
char			**replace_envp(char **old_envp, char **new_envp);
int				find_char_index(const char *str, char c);
void			update_export_list(t_env *env, char *str);
void			print_export_list(t_env *env);

#endif
