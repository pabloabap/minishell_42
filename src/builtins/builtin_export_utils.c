/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguil-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:03:49 by anguil-l          #+#    #+#             */
/*   Updated: 2024/08/23 13:03:55 by anguil-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Frees the memory allocated for an array of strings.
 * 
 * Iterates through the array, frees each string, and then 
 * frees the array itself.
 * 
 * @param arr The array of strings to free.
 * @param len The number of elements in the array.
 * @return NULL.
 */

char	**free_arr(char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}


/**
 * Finds the index of the first '=' character in a string.
 * 
 * @param str The string to search.
 * @return The index of the '=' character, or -1 if not found.
 */

int	equal_sign(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/**
 * Removes all occurrences of a specified quote character from a string.
 * 
 * This function modifies the string in place and adjusts its length.
 * 
 * @param str The string from which to remove quotes.
 * @param quote_char The quote character to remove.
 */

void	delete_quotes(char *str, char quote_char)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != quote_char)
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

/**
 * Checks if a string is a valid identifier for an environment variable.
 * 
 * A valid identifier must start with a letter and may contain letters,
 * digits, and underscores.
 * 
 * @param str The string to check.
 * @return 1 if the string is a valid identifier, 0 otherwise.
 */

int	is_valid_identifier(const char *str)
{
	int	i;

	if (str == NULL || !ft_isalpha(str[0]))
		return (0);
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Handles errors related to invalid environment variable identifiers.
 * 
 * Prints an error message if the provided string is not a valid identifier.
 * 
 * @param str The string to check and print errors for.
 */

void	handle_export_errors(char *str)
{
	if (!is_valid_identifier(str))
		printf("export: '%s': not a valid identifier\n", str);
}
