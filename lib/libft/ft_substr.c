/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:37:26 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/10/06 04:06:23 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((start + len) <= ft_strlen(s))
		p = malloc((len + 1) * sizeof(char));
	else if (ft_strlen(s) < start)
		p = malloc(sizeof(char));
	else
		p = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (start < ft_strlen(s) && i < len)
	{
		p[i] = s[start];
		start ++;
		i ++;
	}
	p[i] = '\0';
	return (p);
}
/*
//#include <stdio.h>
int main(int argc, char **argv) {

   if (argc == 4)
   	   printf("%s",ft_substr(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3])));
  return 0;
}
*/
