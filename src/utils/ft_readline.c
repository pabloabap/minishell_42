/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:08:30 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/09/04 14:08:34 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_readline_preprocesing(t_data *data);
static int	ft_check_var(char *str, char **envp, int *i, int *err);
static int	ft_update_input(t_data *data, int *i);
static int	ft_update_mid_null(t_data *data, char **tmp, int len, int *i);

/** Función que lee y almacena en historial inputs dados por el usuario.
 * En caso de que la variable global de error sea distinta de cero,
 * actualiza el último estado de salida del programa.
 *
 * @param data	Puntero a las estructuras de datos utilizadas en el programa.
 *
 *  @return Nada, actualiza el último estado de salida del programa si
 *  la variable gloabl de error es distinta de cero.
*/
void	ft_readline(t_data *data)
{
	data->input = readline("Minishell% ");
	if (g_error != 0)
		data->last_exit = g_error + 128;
	add_history(data->input);
	if (EXIT_FAILURE == ft_readline_preprocesing(data))
		data->input = NULL;
}

/** Hace un procesamiento inicial del input recibido por readline
 * para eliminar nombres de variables recibidas que no tienen valor
 * asociado.
 * 
 * @param data Puntero a las estructuras de datos utilizadas en el programa.
 * 
 * @return Resultado de la ejecución. Únicamente devulve fallo si hay
 * un fallo de malloc al actualizar el input.
*/
static int	ft_readline_preprocesing(t_data *data)
{
	int	i;

	i = 0;
	while ((*data).input && (*data).input[i])
	{
		if (EXIT_FAILURE == ft_jump_irrelevant_character(data->input, &i))
			return (EXIT_SUCCESS);
		if ((*data).input[i] == '$')
			if (EXIT_FAILURE == ft_check_var(data->input, \
				data->env->envp_cpy, &i, &(data->last_exit)))
				if (EXIT_FAILURE == ft_update_input(data, &i))
					return (EXIT_FAILURE);
		if (i == -1 || ((*data).input[i] && (*data).input[i] != '\''))
			i++;
	}
	return (EXIT_SUCCESS);
}

/** Comprueba si la variable introducida en el input tiene valor.
 * @param str String del input.
 * @param envp Doble puntero a las variables de entorno.
 * @param i Puntero al índice de iteracion.
 * @param err Puntero a entero que almacena el error de la última ejecución
 * para actualizarlo si es necesario.
 * 
 * @return Resultado de la ejecución. Devolverá EXIT_FAILURE únicamente si la 
 * variable no tiene valor.
*/
static int	ft_check_var(char *str, char **envp, int *i, int *err)
{
	int		len;
	char	*v_name;

	*i = *i + 1;
	len = *i;
	if (str[*i] != '_' && !(ft_isalpha(str[*i])))
		return (EXIT_SUCCESS);
	while (str[len] == '_' || (ft_isalnum(str[len])))
		len++;
	if (len > *i)
	{
		v_name = ft_substr(str, *i, len - *i);
		if (!v_name)
			return (err_malloc_fail(err), EXIT_FAILURE);
		if (!ft_getenv(v_name, envp))
			return (free(v_name), *i = *i - 1, EXIT_FAILURE);
		free(v_name);
	}
	return (EXIT_SUCCESS);
}

/** Reconstruye el texto del input eliminando variables nulas.
 * 
 * @param data Puntero a las estructuras de datos utilizadas en el programa.
 * @param i Puntero al índice de iteracion.
 * 
 * @return Resultado de la ejecución. Únicamente devulve fallo si hay
 * un fallo de malloc.
*/
static int	ft_update_input(t_data *data, int *i)
{
	int		len;
	char	*tmp ;

	len = *i + 1;
	tmp = data->input;
	while ((tmp[len] == '_' || (ft_isalnum(tmp[len]))))
		len++;
	if (*i == 0)
		data->input = ft_substr(tmp, len, ft_strlen(tmp) - len);
	else if (!(*data).input[len])
		data->input = ft_substr(tmp, 0, *i);
	else
		if (EXIT_FAILURE == ft_update_mid_null(data, &tmp, len, i))
			return (EXIT_FAILURE);
	if (!data->input)
		return (free(tmp), err_malloc_fail(&(data->last_exit)), EXIT_FAILURE);
	return (*i = -1, free(tmp), EXIT_SUCCESS);
}

/** Extrae del input el nombre de la variable sin valor y junta las otras dos
 * partes.
 * @param data Puntero a las estructuras de datos utilizadas en el programa.
 * @param tmp Doble puntero al string que almacena el input inicial o 
 * posterior al procesamiento previo. Será acutalizado para que apunte al
 * string obtenido del procesamiento realizado en la función.
 * @param len Número de caracteres que tiene el nombre de la variable.
 * @param i Puntero al índice de iteracion.
 * 
 * @return Resultado de la ejecución. Devolverá EXIT_FAILURE únicamente si la 
 * variable no tiene valor.
*/
static int	ft_update_mid_null(t_data *data, char **tmp, int len, int *i)
{
	char	*tmp2;

	data->input = ft_substr(*tmp, 0, *i);
	tmp2 = ft_substr(*tmp, len, ft_strlen(*tmp) - len);
	if (!tmp2)
		return (free(*tmp), free(data->input), \
			err_malloc_fail(&(data->last_exit)), EXIT_FAILURE);
	free(*tmp);
	*tmp = ft_strjoin(data->input, tmp2);
	if (!(*tmp))
		return (err_malloc_fail(&(data->last_exit)), EXIT_FAILURE);
	free (data->input);
	data->input = ft_strdup(*tmp);
	if (!tmp2)
		return (free(*tmp), free(tmp2), \
			err_malloc_fail(&(data->last_exit)), EXIT_FAILURE);
	free (tmp2);
	return (EXIT_SUCCESS);
}
