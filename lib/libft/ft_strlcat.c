/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:12:03 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/25 20:32:36 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_pos;
	size_t	src_pos;
	size_t	original_dst_size;

	dst_pos = ft_strlen(dst);
	src_pos = 0;
	original_dst_size = ft_strlen(dst);
	if (!dstsize || ft_strlen(dst) > dstsize)
		return (dstsize + ft_strlen(src));
	while (src[src_pos] && dst_pos < (dstsize - 1))
	{
		dst[dst_pos] = src[src_pos];
		dst_pos ++;
		src_pos ++;
	}
	dst[dst_pos] = '\0';
	return (original_dst_size + ft_strlen(src));
}
