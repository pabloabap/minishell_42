/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:23:51 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/07/24 20:23:55 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void builtin_pwd(char **args, char **envp)
{
    (void)args;  // Ignora args ya que no se utiliza en esta función
    (void)envp;  // Ignora envp ya que no se utiliza en esta función

    char cwd[1024];
    char *result;

    // Obtén el directorio de trabajo actual
    result = getcwd(cwd, sizeof(cwd));

    if (result != NULL)
    {
        // Usa `ft_putendl_fd` para escribir el directorio y añadir una nueva línea
        ft_putendl_fd(cwd, STDOUT_FILENO);
    }
    else
    {
        // Imprime un mensaje de error en caso de fallo
        const char *error_msg = "minishell: pwd: Error al obtener el directorio actual\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
    }
}
