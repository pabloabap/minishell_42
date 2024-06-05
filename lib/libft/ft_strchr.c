/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:41:48 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/10/06 01:06:33 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	if ((char)c == '\0')
	{
		while (s[pos] != '\0')
			pos ++;
	}
	else
	{
		while (s[pos] && s[pos] != (char)c)
			pos ++;
		if (!s[pos])
			return (NULL);
	}
	return ((char *)(s + pos));
}
