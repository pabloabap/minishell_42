// CABECERA !!!

#ifndef LEXER_H
# define LEXER_H
//# include "minshell.h"

/*Enumeración de posibles tokens a utilizar*/
typedef enum e_tokens
{
    WORD        ,
    PIPE        ,
    IN_REDIR    ,
    OUT_REDIR   ,
    HERE_DOC    ,
    APPEND_REDIR
}   t_tokens;

/*Estructures para almacenar inf de los lexemas*/
typedef struct  s_lexem
{
    char            *str; //word or token
    int             token; //classify the item
    struct s_lexem  *prev; //Pointer to previous item of lexer list
    struct s_lexem  *next; //Pointer to next item of lexer list
    
}   t_lexem;

int	token_lex_fill (char *str, t_lexem **lexem_item, t_tokens token);
void print_lexem_list(t_lexem *lexems_list_iter);

#endif