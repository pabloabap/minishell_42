/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:32:21 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/10/01 20:54:05 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	sign;

	sign = '+';
	if (n < 0)
	{
		sign = '-';
		ft_putchar_fd(sign, fd);
		if (n == -2147483648)
		{
			n = -147483648;
			ft_putchar_fd('2', fd);
		}
		n *= -1;
	}
	if (n / 10 == 0)
		n %= 10;
	else
	{
		ft_putnbr_fd(n / 10, fd);
		n = n % 10;
	}
	ft_putchar_fd((n % 10) + 48, fd);
}
