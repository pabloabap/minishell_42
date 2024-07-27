
#include "../../include/minishell.h"
#include <stdio.h>


static int	ft_heredoc_creation(t_lexem *redir);
int main(void)
{
	char	*text;
	int		counter;
	int		fd;
//----------CMD 1----------//	
	t_lexem *redirs1;
	t_lexem r1;
//------CMD 1 FILL---------//
	r1.str = "$USER";
	r1.token = HERE_DOC;
	r1.next = NULL;
	r1.prev = NULL;
	redirs1 = &r1;
//----------CMD 2----------//	
	t_lexem *redirs2;
	t_lexem r2;
//------CMD 2 FILL---------//
	r2.str = "$USER";
	r2.token = HERE_DOC + SINGLE_QUO_RED;
	r2.next = NULL;
	r2.prev = NULL;
	redirs2 = &r2;

	counter = 0;
	fd = ft_heredoc_creation(redirs1);
	while (1 && redirs2)
	{	
		//Muestra el texto del argumento por pantalla
		// y almacena el output en text.
		text = readline("Introduce texto");
		printf("HAS ESCRITO: %s\n", text);
		add_history(text);
		/* 
			`history_length` es una variable que se
			genera en el fichero history.c de la librería
			readline y almacena el numero de strings
			almacenadas en el historial de ejecucion
		*/
		printf("%d\n", history_length);
		/* 
			Bucle para que, guardados 6 inputs en el historial,
		 	borra el historial de ejecución con rl_clear_history()
		*/
		if (counter == 5)
		{
			rl_clear_history();
			printf("Historial limpiado\n");
		}
		counter ++;
	}
	return (0);
}

static int	ft_heredoc_creation(t_lexem *redir)
{
	int	fd;

	fd = open(redir->str, O_RDWR);
	printf ("HDOC DEL - %s\n", redir->str);
	return (EXIT_FAILURE);
}

/** Checkea si la linea escrita es EOF.
 * 	`len_eof` es un caracter más larga que la
 * 	longitud de EOF porque también queremos que se
 * 	compruebe el `\0` (por si str fuera más larga). 
 *  @param eof String que representa el EOF
 *  @param str String escrita en readline.
 * 	
 *  @return Resultado de la comprobación. Si es cero es que 
 *  las strings son iguales.
*/
static int	eof_check(char *eof, char *str)
{
	int	len_eof;
	int	diff;

	len_eof = ft_strlen(eof) + 1;
	diff = ft_strncmp(eof, str, sizeof(char) * len_eof);
	return (diff);
}


