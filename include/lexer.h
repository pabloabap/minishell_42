// CABECERA !!!

#ifndef LEXER_H
# define LEXER_H
//# include "minshell.h"

// Enumeración de posibles tokens a utilizar
typedef enum e_tokens
{
    WORD        ,
    PIPE        ,
    IN_REDIR    ,
    OUT_REDIR   ,
    HERE_DOC    ,
    APPEND_REDIR
}   t_tokens;

typedef struct  s_lexer
{
    char    *str; //word or token
    int     index; //position of the item in the global string
    int     token; //define the end of a command (0 = end of line)
}   t_lexer;

#endif