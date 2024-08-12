/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:24:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/08 20:34:39 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// Implementación de equal_sign

/*
int	equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1); // No se encontró el signo igual
}

// Implementación de delete_quotes
void	delete_quotes(char *str, char quote_char)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != quote_char)
		{
			str[j++] = str[i];
		}
		i++;
	}
	str[j] = '\0';
}

// Implementación de mini_env
void	mini_env(t_env *env, t_single_cmd *simple_cmd)
{
	// Implementación de ejemplo
	(void)simple_cmd;
	// Imprimir las variables de entorno
	for (int i = 0; env->envp[i] != NULL; i++)
	{
		printf("%s\n", env->envp[i]);
	}
}

// Implementación de builtin_export
void	builtin_export(char **args, char **envp)
{
	char	*str;

	str = args[1];
    
    builtin_env(args, envp);
	if (str[equal_sign(str)] == '\"')
	{
		delete_quotes(str, '\"');
	}
	// Agregar la variable de entorno
	envp = add_var(envp, str);
    builtin_env(args, envp);
}

// Implementación de add_var
char	**add_var(char **arr, char *str)
{
	int		len;
	char	**new_arr;

	len = 0;
	while (arr[len] != NULL)
		len++;
	new_arr = malloc((len + 2) * sizeof(char *));
	for (int i = 0; i < len; i++)
	{
		new_arr[i] = arr[i];
	}
	new_arr[len] = strdup(str);
	new_arr[len + 1] = NULL;
	free(arr);
	return (new_arr);
}
*/

#include "../../include/builtins.h"

// Implementación de equal_sign
int equal_sign(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '=') {
            return i;
        }
        i++;
    }
    return -1; // No se encontró el signo igual
}

// Implementación de delete_quotes
void delete_quotes(char *str, char quote_char) {
    int i = 0;
    int j = 0;
    while (str[i]) {
        if (str[i] != quote_char) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

// Implementación de mini_env
void mini_env(t_env *env, t_single_cmd *simple_cmd) {
    (void)simple_cmd; // Indica que simple_cmd no se usa

    // Imprimir las variables de entorno
    int i = 0;
    while (env->envp[i] != NULL) {
        printf("%s\n", env->envp[i]);
        i++;
    }
}

// Implementación de add_var
char **add_var(char **arr, char *str) {
    int len = 0;
    while (arr[len] != NULL) len++;
    
    char **new_arr = malloc((len + 2) * sizeof(char *));
    if (new_arr == NULL) return NULL; // Error de memoria
    
    int i;
    for (i = 0; i < len; i++) {
        new_arr[i] = strdup(arr[i]);
        if (new_arr[i] == NULL) {
            while (i > 0) free(new_arr[--i]);
            free(new_arr);
            return NULL; // Error de memoria
        }
    }
    new_arr[i] = strdup(str);
    if (new_arr[i] == NULL) {
        while (i > 0) free(new_arr[--i]);
        free(new_arr);
        return NULL; // Error de memoria
    }
    new_arr[i + 1] = NULL;

    return new_arr;
}

// Implementación de builtin_export
void builtin_export(char **args, char **envp) {
    if (args[1] == NULL) {
        builtin_env(args, envp);
        return;
    }

    char *str = args[1];
    int eq_idx = equal_sign(str);
    
    if (eq_idx != -1 && str[eq_idx + 1] == '\"')
        delete_quotes(&str[eq_idx + 1], '\"');

    // Agregar la variable de entorno
    char **new_envp = add_var(envp, str);
    if (new_envp == NULL) {
        // Manejo de error si add_var falla
        return;
    }

    // Mostrar el entorno actualizado
    builtin_env(args, new_envp);

    // Liberar la memoria del entorno antiguo
    int j = 0;
    while (envp[j] != NULL)
		free(envp[j++]);
    free(envp);

    // Reemplazar el entorno antiguo con el nuevo
    envp = new_envp;
}