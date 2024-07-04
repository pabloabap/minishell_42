// CABECERA !!!

#include "../../include/minishell.h"

/** Detector de expansiones de minishell ( 
 * detecta variable de entorno, cuyo nombre 
 * solo puede conterner carácteres alfanuméricos o `_`, y $?).
 * Las expansiones que empieza por $ y van entre parentesis o
 * llaves no son reconocidas por minishell.
 * 
 * @param str String en el que comprobar si hay expansiones
 * a reconocer por minishell.  
 * 
 * @returns Número de expansiones que tiene un string.
 **/
int	ft_has_expansion(char *str)
{
	int	i;
	int	expansiones;

	i = 0;
	expansiones = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) \
		|| str[i + 1] == '_' || str[i + 1] == '?' ))
			expansiones ++;
		i ++;
	}
	return (expansiones);
}
