/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:09:15 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/30 00:19:43 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while ((i < len) && (haystack[i] != '\0'))
	{
		c = 0;
		while (haystack[i + c] != '\0' && needle[c] != '\0' \
				&& haystack[i + c] == needle[c] \
				&& (i + c) < len)
			c ++;
		if (ft_strlen(needle) == c)
			return ((char *)(haystack + i));
		i ++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char **argv)
{
	if (argc == 4)
		printf("%s",ft_strnstr(argv[1], argv[2], atoi(argv[3])));
	return (0);
}
*/
