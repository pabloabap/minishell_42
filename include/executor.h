//CABECERA

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

int ft_executor(t_single_cmd *head, char **envp);
int	ft_prepare_redirections(t_lexem *redirs);

#endif