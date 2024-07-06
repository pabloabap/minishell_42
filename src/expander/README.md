La minishell detecta variables de entorno `$VAR_NAME` no `${VAR_NAME}`
ni `$(VAR_NAME)`.
Los caracteres que componen el nombre de una variable de entorno 
tinen que ser alfa-numéricos, `?` o `_`.

Las variable de entorno, precedidas por `$`, debe interpretarse en 
cualquier caso que no se encuentre entre comillas simples
(WORD, DOUBLE_QUOTES, PIPE, IN_REDIR, OUT_REDIR, APPEND_REDIR tokens).

Esta parte del programa recorrerá cada estructura de la lex_list y de 
la lista de redireciones de los single_cmd en busca de variables
de entorno y:
1. Recorrerá la str de la estructura t_lexem contando los caracteres
que dé la string expandida para reservar la memoría necesaria para
la nueva cadena.
2. Rellenará esta nueva memomería con la string expandida
3. Cambiara el puntero t_lexem->str para que apunte a la nueva
cadena de texto.
4. Liberará el espacio de memoria reservado para la antigua str.