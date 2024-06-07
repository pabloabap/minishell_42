/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:15:14 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/16 18:29:49 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	pos;
	int	last_ocurrence;

	pos = 0;
	last_ocurrence = 0;
	while (s[pos])
	{
		if (s[pos] == (char)c)
			last_ocurrence = pos;
		pos ++;
	}
	if ((char)c == '\0')
		return ((char *)(s + pos));
	else if (last_ocurrence == 0 && s[0] != (char)c)
		return (NULL);
	else
		return ((char *)(s + last_ocurrence));
}
