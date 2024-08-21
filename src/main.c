/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:28 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/06/13 12:37:20 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_readline(t_data *data);
static int	ft_preprocesing(t_data *data);
int	g_error = 0;
/*
char **dup_envp(char **envp)
{
    int i;
    char **envp_cpy;

    i = 0;
    while (envp[i])
        i++;
    envp_cpy = (char **)malloc(sizeof(char *) * (i + 1));
    if (!envp_cpy)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        envp_cpy[i] = ft_strdup(envp[i]);
        if (!envp_cpy[i])
        {
            while (i > 0)
                free(envp_cpy[--i]);
            free(envp_cpy);
            return (NULL);
        }
        i++;
    }
    envp_cpy[i] = NULL;
    return (envp_cpy);
}
*/
char **dup_envp(char **envp)
{
    int i = 0;
    char **envp_copy;

    while (envp[i])
        i++;

    envp_copy = (char **)malloc(sizeof(char *) * (i + 1));
    if (!envp_copy)
        return NULL;

    i = 0;
    while (envp[i])
    {
        envp_copy[i] = ft_strdup(envp[i]);
        if (!envp_copy[i])
        {
            // En caso de error, liberamos la memoria ya asignada
            while (i-- > 0)
                free(envp_copy[i]);
            free(envp_copy);
            return NULL;
        }
        i++;
    }
    envp_copy[i] = NULL;
    return envp_copy;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status;

	if (argc == 1 && ft_strnstr(argv[0], "minishell", ft_strlen(argv[0])))
	{
		status = init_data(&data);
		// Inicializamos t_env y duplicamos envp dentro de envp_cpy
        data->env = malloc(sizeof(t_env));
        if (!data->env)
            return (EXIT_FAILURE);
        data->env->envp_cpy = dup_envp(envp);
		while (EXIT_SUCCESS == status)
		{
			ft_readline(data);
			if (data->input && *(data->input) != '\0')
			{
				if (EXIT_SUCCESS == ft_preprocesing(data) && EXIT_SUCCESS == \
				ft_executor(data->head_cmd_list, data->env, &data->last_exit))
					data->last_exit = 0;
			}
			else if (!data->input)
				return (ft_putendl_fd("exit", STDERR_FILENO), \
				clean_data(data), free(data), EXIT_SUCCESS);
			clean_data(data);
		}
        free(data->env->envp_cpy);  // Liberamos la memoria de envp_cpy
        free(data->env);            // Liberamos la estructura t_env
		free(data);
	}
	return (status);
}

/** Función que lee y almacena en historial inputs dados por el usuario.
 * En caso de que la variable global de error sea distinta de cero, 
 * actualiza el último estado de salida del programa.
 * 
 * @param data	Puntero a las estructuras de datos utilizadas en el programa.
 * 
 *  @return Nada, actualiza el último estado de salida del programa si
 *  la variable gloabl de error es distinta de cero.
 */
static void	ft_readline(t_data *data)
{
	data->input = readline("Minishell% ");
	if (g_error != 0)
		data->last_exit = g_error + 128;
	add_history(data->input);
}

/** Función que agrupa las aciones de lexing, parsing y actualiza el exit
 * status en caso de error.
 * 
 * 	@param data	Puntero a las estructuras de datos utilizadas en el programa.
 * 
 *  @return Estado de salida de la función.
 */
static int	ft_preprocesing(t_data *data)
{
	if ((EXIT_FAILURE == lexer(data->input, &(data->head_lex_list))) || \
		(EXIT_FAILURE == ft_lex_to_cmd(&(data->head_lex_list), \
		&(data->head_cmd_list), &data->last_exit)) || \
		(EXIT_FAILURE == ft_expander(data->head_lex_list, \
		data->head_cmd_list, &data->last_exit)))
	{
		data->last_exit = 2;
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}
