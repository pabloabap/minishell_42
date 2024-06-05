/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:35:20 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/30 14:02:41 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n;
	char	*p;

	n = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = malloc(n * sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s1, n);
	ft_strlcat(p, s2, n);
	p[n - 1] = '\0';
	return (p);
}
