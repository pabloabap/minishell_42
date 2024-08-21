/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:57:04 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 19:04:15 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

// Declaraciones de las funciones internas
void		builtin_cd(char **args, t_env *env);
void		builtin_pwd(char **args, t_env *env);
void		builtin_unset(char **args, t_env *env);
void		builtin_exit(char **args, t_env *env);
void		builtin_env(char **args, t_env *env);
void		builtin_export(char **args, t_env *env);
void		builtin_echo(char **args, t_env *env);

typedef void	(*builtin_func)(char **args, t_env *env);

builtin_func		builtin_arr(char *str);

int			is_builtin(char *command);
void		execute_builtin(char **args, t_env *env);
char		**add_var(char **arr, char *str);
void		whileloop_add_var(char **arr, char **rtn, char *str);

// Declaraciones de las funciones faltantes
int			equal_sign(char *str);
void		delete_quotes(char *str, char quote_char);
void		mini_env(t_env *env, t_single_cmd *simple_cmd);

int variable_exist(t_env *env, char *str);

#endif
