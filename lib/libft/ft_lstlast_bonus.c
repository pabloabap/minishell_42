/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:03:47 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/10/10 20:35:49 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
int   main(void)
{
	t_list  *a;

	a = NULL;
	a = (t_list*)malloc(sizeof(t_list));
	if (a == NULL)
	{
		free(a);
		return (1);
	}
	a->content = "HOLA";
	a->next = (t_list*)malloc(sizeof(t_list));
	if(a->next == NULL)
	{
		free(a->next);
		free(a);
		return (1);
	}
	a->next->content = "ADIOS";
	a->next->next = (t_list*)malloc(sizeof(t_list));
	if(a->next->next == NULL)
	{
		free(a->next->next);
		free(a->next);
		free(a);
		return (1);
	}
	a->next->next->content = "ADIOS2";
	a->next->next->next = NULL;
	printf("%s\n", (char *)ft_lstlast(a)->content);
	free (a-> next);
	free (a);
	return (0);
}
*/
