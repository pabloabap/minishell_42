/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:12:10 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/25 14:36:14 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)s1)[pos] == ((unsigned char *)s2)[pos] \
			&& pos < (n - 1))
		pos ++;
	return (((unsigned char *)s1)[pos] - ((unsigned char *)s2)[pos]);
}
