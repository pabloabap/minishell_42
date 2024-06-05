/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:34:47 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/17 14:20:29 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	if (n == 0)
		return (0);
	while (s1[pos] != 0 && pos < (n - 1) && s1[pos] == s2[pos])
		pos ++;
	if (!s1[pos] && pos == n)
		return ((unsigned char)(s1[pos -1]) - (unsigned char)(s2[pos - 1]));
	else
		return ((unsigned char)(s1[pos]) - (unsigned char)(s2[pos]));
}
