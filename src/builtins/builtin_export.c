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

// Prototipos de funciones internas
char		**replace_envp(char **old_envp, char **new_envp);
static void	ft_update_var(char *str, t_env *env, int eq_idx);
static void	process_and_update_var(char *str, t_env *env, int *last_exit);
char		**add_var(char **arr, char *str);

/**
 * Implementa el comando `export` que añade o actualiza variables de entorno.
 * Si no se proporcionan argumentos, imprime la lista de exportación. De lo 
 * contrario, procesa cada argumento y actualiza las variables de entorno y 
 * exportación según corresponda.
 * @param args Array de cadenas que contiene los argumentos del comando 
 *             `export`.
 * @param env Puntero a la estructura `t_env` que contiene el array de 
 *            entorno `envp_cpy`.
 * @param last_exit Puntero a la variable que almacena el último código de 
 *                   salida.
 */
void	builtin_export(char **args, t_env *env, int *last_exit)
{
	int	i;

	i = 0 * *last_exit;
	if (!args[1])
		print_export_list(env);
	else
	{
		while (args[i])
		{
			process_and_update_var(args[i], env, last_exit);
			i++;
		}
	}
}

/**
 * Reemplaza el array de entorno antiguo con uno nuevo. Libera la memoria 
 * ocupada por el array de entorno antiguo y retorna el nuevo array.
 * 
 * @param old_envp El array de entorno antiguo que se debe liberar.
 * @param new_envp El nuevo array de entorno que se debe retornar.
 * 
 * @return El nuevo array de entorno.
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
 * Actualiza la variable de entorno en el array `envp_cpy` y la lista de 
 * exportación. Si la variable no existe en `envp_cpy`, la añade.
 * 
 * @param str La cadena que representa la variable de entorno a actualizar.
 * @param env Puntero a la estructura `t_env` que contiene el array de 
 *            entorno `envp_cpy`.
 * @param eq_idx El índice del signo '=' en la cadena `str`, o -1 si no 
 *               se encuentra.
 */
static void	ft_update_var(char *str, t_env *env, int eq_idx)
{
	char	**new_envp;

	if (eq_idx == -1)
		update_export_list(env, str);
	else
	{
		if (!variable_exist(env, str))
		{
			new_envp = add_var(env->envp_cpy, str);
			if (new_envp == NULL)
			{
				perror("Failure adding envirnomental variable");
				return ;
			}
			env->envp_cpy = replace_envp(env->envp_cpy, new_envp);
		}
		update_export_list(env, str);
	}
}

/**
 * Procesa y actualiza una variable de entorno. Valida la variable, elimina 
 * comillas si están presentes y actualiza o añade la variable en el entorno 
 * si es válida.
 * 
 * @param str La cadena que representa la variable de entorno a procesar.
 * @param env Puntero a la estructura `t_env` que contiene el array de 
 *            entorno `envp_cpy`.
 */
static void	process_and_update_var(char *str, t_env *env, int *last_exit)
{
	int	eq_idx;

	eq_idx = equal_sign(str);
	if (is_valid_identifier(str))
		ft_update_var(str, env, eq_idx);
	else
		handle_export_errors(str, last_exit);
}

/**
 * Añade una nueva variable a un array de variables de entorno. Asigna memoria 
 * para un nuevo array que incluye la variable adicional y copia todas las 
 * variables existentes a este nuevo array.
 * 
 * @param arr El array existente de variables de entorno.
 * @param str La nueva variable a añadir.
 * 
 * @return El nuevo array que incluye la nueva variable, o NULL en caso de 
 *         fallo.
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
