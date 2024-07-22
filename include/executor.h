//CABECERA

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

int ft_executor(t_single_cmd *head, char **envp);
int	ft_prepare_redirections(t_lexem *redirs);
int	ft_set_pipes(t_single_cmd *current_cmd, int main_out);

#endif