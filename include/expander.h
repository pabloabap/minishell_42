/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:16:02 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/06 21:16:06 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "minishell.h"

/*Funciones propias de la expansion*/

//Expander
int	ft_expander(t_lexem *lex_list, t_single_cmd *cmd_list);
int	ft_has_expansion(char *str);
int	ft_expansion_malloc(char **exp_malloc, char *str, int token, int *buffer);
int	ft_fill_expansion(char *new_str, char *old_str, int token, int *buff);
int	ft_expansion_replace(char *exp_malloc, t_lexem *lex_list);

#endif