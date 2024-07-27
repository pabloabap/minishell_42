/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:22:53 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/27 23:23:22 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

int	ft_executor(t_single_cmd *head, char **envp, int *err_n);
int	ft_prepare_redirections(t_lexem *redirs, int *err_n);
int	ft_set_pipes(t_single_cmd *current_cmd, int std_out, int *err_n);
int	ft_heredoc_creation(t_lexem *redir, int *err_n);

#endif
