/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consecutive_quotes_split.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:39:34 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/27 20:39:49 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	str_array_len(char const *s, char c);
static char	**fill_array(char **pp, char const *s, char c);
static int	fill_logic(char **pp, char const *s, int w_pos[2], int *i);
static char	**ft_free(char **pp, int i);

char	**ft_consecutive_split(char const *s, char c)
{
	char	**pp;

	pp = NULL;
	if (str_array_len(s, c) > 1)
	{
		pp = malloc((str_array_len(s, c) + 1) * sizeof(char *));
		if (pp == NULL)
		{
			free(pp);
			return (NULL);
		}
		pp = fill_array(pp, s, c);
	}
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
		if (s[i] == c)
			i ++;
		if (s[i])
			words ++;
		while (s[i] != c && s[i] != '\0')
			i ++;
	}
	return (words);
}

static char	**fill_array(char **pp, char const *s, char c)
{
	int	i;
	int	word_position[2];

	i = 0;
	word_position[1] = 0;
	while (s[word_position[1]] != '\0')
	{
		if (s[word_position[1]] == c)
			word_position[1] += 1;
		word_position[0] = word_position[1];
		while (s[word_position[1]] != '\0' && s[word_position[1]] != c)
			word_position[1] += 1;
		if (EXIT_FAILURE == fill_logic(pp, s, word_position, &i))
			return (NULL);
	}
	pp[i] = NULL;
	return (pp);
}

static int	fill_logic(char **pp, char const *s, int w_pos[2], int *i)
{
	if (w_pos[0] < w_pos[1])
	{
		pp[*i] = ft_substr(s, w_pos[0], (w_pos[1] - w_pos[0]));
		if (pp[*i] == NULL)
			return (ft_free(pp, *i), EXIT_FAILURE);
		*i += 1;
	}
	else if (s[w_pos[1]] != '\0')
	{
		pp[*i] = "";
		*i += 1;
	}
	return (EXIT_SUCCESS);
}

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
