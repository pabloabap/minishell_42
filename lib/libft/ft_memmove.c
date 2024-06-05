/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 00:20:34 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/30 00:20:42 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*tmp_src;
	size_t	pos;

	tmp_src = (void *)src;
	pos = 0;
	if (!dest && !src)
		return (NULL);
	else if (tmp_src < dest)
		while (n --)
			((unsigned char *)dest)[n] = ((unsigned char *)tmp_src)[n];
	else
	{
		while (pos < n)
		{
			((unsigned char *)dest)[pos] = ((unsigned char *)tmp_src)[pos];
			pos ++;
		}
	}
	return (dest);
}
