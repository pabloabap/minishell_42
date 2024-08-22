/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:38:19 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 20:43:46 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Función auxiliar para liberar y eliminar una variable de entorno de envp
/*
void	remove_env_var(char ***envp, int index)
{
	free((*envp)[index]);
	while ((*envp)[index] != NULL)
	{
		(*envp)[index] = (*envp)[index + 1];
		index++;
	}
}

// Función para encontrar el índice de una variable de entorno en envp
int	find_env_var_index(char **envp, const char *var)
{
	int	len;
	int	i;

	len = strlen(var);
	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	builtin_unset(char **args, t_env *env)
{
	int	index;
	int	i; // Comenzar en 1 para omitir el nombre del comando

	i = 1; // Comenzar en 1 para omitir el nombre del comando
	while (args[i] != NULL)
	{
		index = find_env_var_index(env, args[i]);
		if (index != -1)
			remove_env_var(env, index);
		i++;
	}
}
*/
/*
// Encuentra el índice de una variable en el array de entorno
int find_env_var_index(char **envp, const char *var)
{
    int i;
    int eq_idx = equal_sign(var);

    for (i = 0; envp[i]; i++)
    {
        if (ft_strncmp(envp[i], var, eq_idx) == 0)
            return i;
    }
    return -1; // Variable no encontrada
}

// Elimina una variable del array de entorno
void remove_env_var(char ***envp, int index)
{
    char **new_envp;
    int i;
    int len;

    len = 0;
    while ((*envp)[len])
        len++;

    new_envp = (char **)malloc(sizeof(char *) * len);
    if (!new_envp)
        return; // Manejo de errores necesario

    for (i = 0; i < index; i++)
        new_envp[i] = (*envp)[i];
    for (i = index; i < len - 1; i++)
        new_envp[i] = (*envp)[i + 1];
    new_envp[len - 1] = NULL;

    free((*envp)[index]);
    free(*envp);
    *envp = new_envp;
}

// Implementación de builtin_unset
void builtin_unset(char **args, t_env *env)
{
    int i;
    int index;

    for (i = 1; args[i] != NULL; i++)
    {
        index = find_env_var_index(env->envp_cpy, args[i]);
        if (index != -1)
        {
            remove_env_var(&env->envp_cpy, index);
        }
        else
        {
            printf("unset: '%s': not found\n", args[i]);
        }
    }
}
*/
#include "../../include/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Encuentra el índice de una variable en el array de entorno
int find_env_var_index(char **envp, const char *var)
{
    int i;
    int eq_idx;

    // Encuentra el índice del signo '=' en la variable
    eq_idx = equal_sign(var);
    if (eq_idx == -1) // Asegúrate de que `var` tenga un signo '='.
        return -1;

    // Copia el nombre de la variable para la comparación
    char *var_name = strndup(var, eq_idx);
    if (!var_name)
        return -1; // Manejo de errores en caso de fallo de memoria

    for (i = 0; envp[i]; i++)
    {
        // Compara el nombre de la variable con las variables en `envp`
        if (strncmp(envp[i], var_name, eq_idx) == 0 && envp[i][eq_idx] == '=')
        {
            free(var_name);
            return i;
        }
    }

    free(var_name);
    return -1; // Variable no encontrada
}

// Elimina una variable del array de entorno
void remove_env_var(char ***envp, int index)
{
    int len = 0;
    int i;
    char **new_envp;

    // Encuentra el tamaño del array original
    while ((*envp)[len])
        len++;

    // Reserva espacio para el nuevo array (tamaño original - 1)
    new_envp = (char **)malloc(sizeof(char *) * len);
    if (!new_envp)
        return; // Manejo de errores necesario

    // Copia los elementos antes del índice
    for (i = 0; i < index; i++)
        new_envp[i] = (*envp)[i];
    // Copia los elementos después del índice
    for (i = index; i < len - 1; i++)
        new_envp[i] = (*envp)[i + 1];
    new_envp[len - 1] = NULL;

    // Libera el array viejo y actualiza el puntero
    free((*envp)[index]);
    free(*envp);
    *envp = new_envp;
}

// Implementación de builtin_unset
void builtin_unset(char **args, t_env *env)
{
    int i;
    int index;

    for (i = 1; args[i] != NULL; i++)
    {
        // Encuentra el índice de la variable en el array de entorno
        index = find_env_var_index(env->envp_cpy, args[i]);
        if (index != -1)
        {
            // Elimina la variable si se encuentra
            remove_env_var(&env->envp_cpy, index);
        }
        else
        {
            // Imprime un mensaje si la variable no se encuentra
            printf("unset: '%s': not found\n", args[i]);
        }
    }
}