/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:02:02 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/10/10 20:02:06 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 1;
	if (lst == NULL)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		size ++;
	}
	return (size);
}
//
//int	main(void)
//{
//	t_list	*a;
//	int	s;
//
//	a = NULL;
//	a = (t_list*)malloc(sizeof(t_list));
//	if (a == NULL)
//		return (1);
//	a->content = "HOLA";
//	a->next = (t_list*)malloc(sizeof(t_list));
//	if(a->next == NULL)
//		return (1);
//	a->next->content = "ADIOS";
//	a->next->next = NULL;
//	s = ft_lstsize(a);
//	s = ft_lstsize(NULL);	
//	return (s);
//}
