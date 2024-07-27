/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:23:51 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:23:55 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Implementación del comando 'pwd'
int builtin_pwd(void) {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        ft_putendl_fd(cwd, STDOUT_FILENO);
        return EXIT_SUCCESS;
    } else {
        perror("pwd");
        return EXIT_FAILURE;
    }
}
