#include "../../include/minishell.h"

t_single_cmd	*ft_lstcmd(t_single_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_redirection(t_single_cmd *cmd, t_lexem *r)
{
	if (cmd->redirection == NULL)
		cmd->redirection = r;
	else
	{
		while(cmd->redirection)
		{
			cmd->redirection->next = r;
			cmd->redirection->next->prev = cmd->redirection;
			cmd->redirection = cmd->redirection->next;
		}
	}
}