/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:30:47 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/10/01 18:34:24 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	unsigned int	i;

	i = 0;
	p = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		p[i] = f(i, s[i]);
		i ++;
	}
	return (p);
}
