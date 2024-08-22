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

#include "../../include/minishell.h"

// Devuelve el índice del primer signo '=' en la cadena, o -1 si no se encuentra
int equal_sign(const char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '=')
            return i;
        i++;
    }
    return -1;
}

// Verifica si el identificador es válido
int is_valid_identifier(const char *str)
{
    int i;

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

// Elimina las comillas de una cadena
void delete_quotes(char *str, char quote_char)
{
    int i, j;

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

// Duplica el array de variables de entorno y agrega una nueva variable
/*
char **add_var(char **arr, char *str)
{
    int i;
    int len;
    char **new_arr;

    len = 0;
    while (arr[len] != NULL)
        len++;

    new_arr = (char **)malloc(sizeof(char *) * (len + 2));
    if (!new_arr)
        return NULL;

    for (i = 0; i < len; i++)
        new_arr[i] = ft_strdup(arr[i]);  // Duplica las cadenas existentes

    new_arr[i] = ft_strdup(str);  // Duplica la nueva cadena
    new_arr[i + 1] = NULL;

    // Limpia la memoria antigua
    for (i = 0; i < len; i++)
        free(arr[i]);
    free(arr);

    return new_arr;
}

// Reemplaza el array de variables de entorno antiguo con el nuevo
char **replace_envp(char **old_envp, char **new_envp)
{
    int i = 0;

    if (old_envp)
    {
        while (old_envp[i])
            free(old_envp[i++]);
        free(old_envp);
    }
    return new_envp;
}
*/

char **add_var(char **arr, char *str)
{
    int i;
    int len;
    char **new_arr;

    len = 0;
    while (arr[len] != NULL)
        len++;

    new_arr = (char **)malloc(sizeof(char *) * (len + 2));
    if (!new_arr)
        return NULL;

    for (i = 0; i < len; i++)
    {
        new_arr[i] = ft_strdup(arr[i]);
        if (!new_arr[i])
        {
            // En caso de fallo, liberar la memoria asignada
            while (i-- > 0)
                free(new_arr[i]);
            free(new_arr);
            return NULL;
        }
    }

    new_arr[i] = ft_strdup(str);
    if (!new_arr[i])
    {
        // En caso de fallo, liberar la memoria asignada
        while (i-- > 0)
            free(new_arr[i]);
        free(new_arr);
        return NULL;
    }

    new_arr[i + 1] = NULL;
    return new_arr;
}

char **replace_envp(char **old_envp, char **new_envp)
{
    int i = 0;

    if (old_envp)
    {
        while (old_envp[i])
            free(old_envp[i++]);
        free(old_envp);
    }
    return new_envp;
}
// Implementación de la función builtin_export
/*
void builtin_export(char **args, char **envp)
{
    int i;
    char *str;
    int eq_idx;
    char **new_envp;

    if (args[1] == NULL)
    {
        // Mostrar las variables de entorno
        builtin_env(args, envp);
        return;
    }

    for (i = 1; args[i] != NULL; i++)
    {
        if (is_valid_identifier(args[i]))
        {
            str = args[i];
            eq_idx = equal_sign(str);

            if (eq_idx != -1 && str[eq_idx + 1] == '\"')
                delete_quotes(&str[eq_idx + 1], '\"');

            new_envp = add_var(envp, str);
            if (new_envp == NULL)
            {
                perror("Error al agregar variable de entorno");
                return;
            }
            envp = new_envp;  // Actualiza el puntero envp original
        }
        else
            printf("export: '%s': not a valid identifier\n", args[i]);
    }
}
*/
void builtin_export(char **args, t_env *env)
{
    int i;
    char *str;
    int eq_idx;
    char **new_envp;

    if (args[1] == NULL)
    {
        // Mostrar las variables de entorno
        builtin_env(args, env);
        return;
    }

    for (i = 1; args[i] != NULL; i++)
    {
        if (is_valid_identifier(args[i]))
        {
            str = args[i];
            eq_idx = equal_sign(str);

            if (eq_idx != -1 && str[eq_idx + 1] == '\"')
                delete_quotes(&str[eq_idx + 1], '\"');

            // Primero, verificamos si la variable ya existe
            if (!variable_exist(env, str))
            {
                // Si no existe, intentamos agregarla
                new_envp = add_var(env->envp_cpy, str);
                if (new_envp == NULL)
                {
                    perror("Error al agregar variable de entorno");
                    return;
                }
                // Aquí actualizamos el puntero envp con el nuevo array
                env->envp_cpy = replace_envp(env->envp_cpy, new_envp);
            }
        }
        else
        {
            printf("export: '%s': not a valid identifier\n", args[i]);
        }
    }
}
