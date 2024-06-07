/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:26:54 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/10/01 15:29:28 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	st_buffer(int n, int d)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n /= 10;
			d ++;
		}
		n *= -1;
		d ++;
	}
	if ((n / 10) == 0)
		return ((d ++));
	else
	{
		return (st_buffer((n / 10), d + 1));
	}
}

char	*ft_itoa(int n)
{
	char	*p;
	size_t	buff;
	char	sign;

	sign = '+';
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	buff = st_buffer(n, 1);
	if (n < 0)
	{
		n *= -1;
		sign = '-';
	}
	p = ft_calloc(buff + 1, sizeof(char));
	if (p == NULL)
		return (NULL);
	while (buff > 0)
	{
		p[buff - 1] = (n % 10) + '0';
		n /= 10;
		buff --;
	}
	if (sign == '-')
		p[0] = sign;
	return (p);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%s", ft_itoa(ft_atoi(argv[1])));
	return (0);
}
*/
