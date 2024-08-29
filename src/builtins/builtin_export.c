/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:24:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/22 20:34:39 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/**
 * Replaces an old environment array with a new one.
 * Frees the memory occupied by the old environment array 
 * and returns the new array.
 * @param old_envp The old environment array to free.
 * @param new_envp The new environment array to return.
 * @return The new environment array.
 */

char	**replace_envp(char **old_envp, char **new_envp)
{
	int	i;

	i = 0;
	if (old_envp)
	{
		while (old_envp[i])
			free(old_envp[i++]);
		free(old_envp);
	}
	return (new_envp);
}

/**
 * Processes a variable string and updates the environment if necessary.
 * Checks if the variable string is valid, removes quotes if necessary,
 * and updates the environment if the variable does not already exist.
 * @param str The variable string to process.
 * @param env The environment structure to update.
 */
/*
static void	process_and_update_var(char *str, t_env *env)
{
	int		eq_idx;
	char	**new_envp;

	eq_idx = equal_sign(str);
	if (!is_valid_environment_variable(str))
		return ;
	if (eq_idx != -1 && str[eq_idx + 1] == '\"')
		delete_quotes(&str[eq_idx + 1], '\"');
	if (is_valid_identifier(str))
	{
		if (!variable_exist(env, str))
		{
			new_envp = add_var(env->envp_cpy, str);
			if (new_envp == NULL)
			{
				perror("Error al agregar variable de entorno");
				return ;
			}
			env->envp_cpy = replace_envp(env->envp_cpy, new_envp);
		}
	}
	else
		handle_export_errors(str);
}
*/

static void process_and_update_var(char *str, t_env *env)
{
    int eq_idx;
    char **new_envp;

    eq_idx = equal_sign(str);
    if (!is_valid_environment_variable(str))
        return;

    if (eq_idx != -1 && str[eq_idx + 1] == '\"')
        delete_quotes(&str[eq_idx + 1], '\"');

    if (is_valid_identifier(str))
    {
        if (eq_idx == -1) // Variable sin valor
        {
            update_export_list(env, str);
        }
        else
        {
            if (!variable_exist(env, str))
            {
                new_envp = add_var(env->envp_cpy, str);
                if (new_envp == NULL)
                {
                    perror("Error al agregar variable de entorno");
                    return;
                }
                env->envp_cpy = replace_envp(env->envp_cpy, new_envp);
            }
            // Actualizar la lista de exportación también
            update_export_list(env, str);
        }
    }
    else
    {
        handle_export_errors(str);
    }
}


/**
 * Updates the environment with variables specified in the arguments.
 * Iterates over the arguments, starting from the second argument, and
 * processes each one to update the environment.
 * @param args The arguments containing variable strings.
 * @param env The environment structure to update.
 */

void	update_environment(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		process_and_update_var(args[i], env);
		i++;
	}
}

/**
 * Implements the 'export' command to update environment variables.
 * If no additional arguments are provided, it lists the current environment.
 * Otherwise, it updates the environment with the provided variable strings.
 * @param args The arguments passed to the 'export' command.
 * @param env The environment structure to modify.
 */
/*
void	builtin_export(char **args, t_env *env)
{
	if (args[1] == NULL)
	{
		builtin_env(args, env);
		return ;
	}
	update_environment(args, env);
}
*/
/*
void update_export_list(t_env *env, char *str)
{
    char **new_export_cpy;
    int size;
    int i;

    if (!env->export_cpy)
    {
        env->export_cpy = malloc(sizeof(char *));
        if (!env->export_cpy)
        {
            perror("Error al asignar memoria");
            exit(EXIT_FAILURE);
        }
        env->export_cpy[0] = NULL;
    }

    size = 0;
    while (env->export_cpy[size])
        size++;

    new_export_cpy = malloc((size + 2) * sizeof(char *));
    if (!new_export_cpy)
    {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (i < size && strcmp(env->export_cpy[i], str) < 0)
    {
        new_export_cpy[i] = strdup(env->export_cpy[i]);
        if (!new_export_cpy[i])
        {
            perror("Error al duplicar cadena");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    new_export_cpy[i] = strdup(str);
    if (!new_export_cpy[i])
    {
        perror("Error al duplicar cadena");
        exit(EXIT_FAILURE);
    }
    i++;
    while (i <= size)
    {
        new_export_cpy[i] = strdup(env->export_cpy[i - 1]);
        if (!new_export_cpy[i])
        {
            perror("Error al duplicar cadena");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    new_export_cpy[size + 1] = NULL;

    free_arr(env->export_cpy, size);
    env->export_cpy = new_export_cpy;
}
*/
/*
void update_export_list(t_env *env, char *str)
{
    char **new_export_cpy;
    int size;
    int i;

    // Verificar si export_cpy es NULL y manejar adecuadamente
    if (!env->export_cpy)
    {
        new_export_cpy = malloc(sizeof(char *) * 2);
        if (!new_export_cpy)
        {
            perror("Error al asignar memoria");
            exit(EXIT_FAILURE);
        }
        new_export_cpy[0] = strdup(str);
        if (!new_export_cpy[0])
        {
            perror("Error al duplicar cadena");
            exit(EXIT_FAILURE);
        }
        new_export_cpy[1] = NULL;
        env->export_cpy = new_export_cpy;
        return;
    }

    // Contar el tamaño actual del array
    size = 0;
    while (env->export_cpy[size])
        size++;

    // Reservar memoria para el nuevo array
    new_export_cpy = malloc(sizeof(char *) * (size + 2));
    if (!new_export_cpy)
    {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    // Copiar elementos existentes y añadir la nueva variable
    i = 0;
    while (i < size && strcmp(env->export_cpy[i], str) < 0)
    {
        new_export_cpy[i] = strdup(env->export_cpy[i]);
        if (!new_export_cpy[i])
        {
            perror("Error al duplicar cadena");
            free_arr(new_export_cpy, i);
            exit(EXIT_FAILURE);
        }
        i++;
    }

    new_export_cpy[i] = strdup(str);
    if (!new_export_cpy[i])
    {
        perror("Error al duplicar cadena");
        free_arr(new_export_cpy, i);
        exit(EXIT_FAILURE);
    }
    i++;

    while (i <= size)
    {
        new_export_cpy[i] = strdup(env->export_cpy[i - 1]);
        if (!new_export_cpy[i])
        {
            perror("Error al duplicar cadena");
            free_arr(new_export_cpy, i);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    new_export_cpy[size + 1] = NULL;

    // Liberar memoria del array anterior
    free_arr(env->export_cpy, size);
    env->export_cpy = new_export_cpy;
}
*/
void update_export_list(t_env *env, char *str)
{
    char **new_export_cpy;
    int size;
    int i;

    // Verificar si export_cpy es NULL y manejar adecuadamente
    if (!env->export_cpy)
    {
        new_export_cpy = malloc(sizeof(char *) * 2);
        if (!new_export_cpy)
        {
            perror("Error al asignar memoria");
            exit(EXIT_FAILURE);
        }
        new_export_cpy[0] = strdup(str);
        if (!new_export_cpy[0])
        {
            perror("Error al duplicar cadena");
            exit(EXIT_FAILURE);
        }
        new_export_cpy[1] = NULL;
        env->export_cpy = new_export_cpy;
        return;
    }

    // Contar el tamaño actual del array
    size = 0;
    while (env->export_cpy[size])
        size++;

    // Reservar memoria para el nuevo array
    new_export_cpy = malloc(sizeof(char *) * (size + 2));
    if (!new_export_cpy)
    {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    // Copiar elementos existentes y añadir la nueva variable
    i = 0;
    while (i < size && strcmp(env->export_cpy[i], str) < 0)
    {
        new_export_cpy[i] = strdup(env->export_cpy[i]);
        if (!new_export_cpy[i])
        {
            perror("Error al duplicar cadena");
            free_arr(new_export_cpy, i);
            exit(EXIT_FAILURE);
        }
        i++;
    }

    new_export_cpy[i] = strdup(str);
    if (!new_export_cpy[i])
    {
        perror("Error al duplicar cadena");
        free_arr(new_export_cpy, i);
        exit(EXIT_FAILURE);
    }
    i++;

    while (i <= size)
    {
        new_export_cpy[i] = strdup(env->export_cpy[i - 1]);
        if (!new_export_cpy[i])
        {
            perror("Error al duplicar cadena");
            free_arr(new_export_cpy, i);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    new_export_cpy[size + 1] = NULL;

    // Liberar memoria del array anterior
    free_arr(env->export_cpy, size);
    env->export_cpy = new_export_cpy;
}

void print_export_list(t_env *env)
{
    int i;

    if (env->export_cpy == NULL)
    {
        printf("export_cpy is NULL\n");
        return;
    }

    i = 0;
    while (env->export_cpy[i])
    {
        printf("declare -x %s\n", env->export_cpy[i]);
        i++;
    }
}


void builtin_export(char **args, t_env *env)
{
    int i;

    if (!args[1]) // Si no hay argumentos, imprimir todas las variables exportadas
    {
        print_export_list(env);
    }
    else
    {
        for (i = 1; args[i]; i++)
        {
            process_and_update_var(args[i], env);
        }
    }
}

/**
 * Adds a new variable to an array of environment variables.
 * Allocates memory for a new array that includes the additional variable and
 * copies all existing variables to this new array.
 * @param arr The existing array of environment variables.
 * @param str The new variable to add.
 * @return The new array including the new variable, or NULL on failure.
 */

char	**add_var(char **arr, char *str)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	while (arr[len] != NULL)
		len++;
	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			return (free_arr(new_arr, i));
		i++;
	}
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		return (free_arr(new_arr, i));
	new_arr[i + 1] = NULL;
	return (new_arr);
}
