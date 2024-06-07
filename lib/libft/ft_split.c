/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:23:00 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/10/08 21:16:35 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	**ft_free(char **pp, int i)
{
	while (i >= 0)
	{
		free(pp[i]);
		i --;
	}
	free(pp);
	return (NULL);
}

static char	**fill_array(char **pp, char const *s, char c)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (s[end] != '\0')
	{
		while (s[end] == c)
			end ++;
		start = end;
		while (s[end] != '\0' && s[end] != c)
			end ++;
		if (start < end)
		{
			pp[i] = ft_substr(s, start, (end - start));
			if (pp[i] == NULL)
				return (ft_free(pp, i));
			i ++;
		}
	}
	pp[i] = NULL;
	return (pp);
}

static int	str_array_len(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i ++;
		if (s[i])
			words ++;
		while (s[i] != c && s[i] != '\0')
			i ++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**pp;

	pp = malloc((str_array_len(s, c) + 1) * sizeof(char *));
	if (pp == NULL)
	{
		free(pp);
		return (NULL);
	}
	pp = fill_array(pp, s, c);
	return (pp);
}
