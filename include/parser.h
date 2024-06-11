// CABECERA !!!

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

/*Estructures para almacenar info de los comandos de los lexemas*/
typedef struct s_single_cmd
{
	char				*str; //commando
//	char				(*build_func)(<param1Typte> <param1Name>, ...) BUILDING FUNCTION. PDTE DE DEFINIRLAS
	int					_stdin; //Input file descriptor
	int					_stdout; //Output file descriptor
	int					_stderr; //Stderr file descriptor
	struct s_single_cmd	*prev; //Pointer to next item of lexer list
	struct s_single_cmd	*next; //Pointer to next item of lexer list
}	t_single_cmd;

#endif