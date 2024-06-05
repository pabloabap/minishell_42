/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:26:26 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/25 20:31:54 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	str_len;
	size_t	pos;

	str_len = ft_strlen(src);
	pos = 0;
	if (!dstsize || (!src & !dst))
		return (str_len);
	while (src[pos] && pos < (dstsize - 1))
	{
		dst[pos] = src[pos];
		pos ++;
	}
	dst[pos] = '\0';
	return (str_len);
}
