// CABECERA

#include "../../include/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

void	print_lexem_list(t_lexem *lexems_list_iter)
{
	int	i;

	i = 0;
	while (lexems_list_iter != NULL)
	{
		printf("ITEM %i - %s\n", i++, lexems_list_iter->str);
		lexems_list_iter = lexems_list_iter->next;
	}
}
