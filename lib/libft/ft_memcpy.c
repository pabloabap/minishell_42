/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:01:51 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/29 21:04:59 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	pos;

	pos = 0;
	if ((unsigned char *)dest == 0 && (unsigned char *)src == 0)
		return (NULL);
	while (pos < n)
	{
		((unsigned char *)dest)[pos] = ((unsigned char *)src)[pos];
		pos ++;
	}
	return ((void *)dest);
}
