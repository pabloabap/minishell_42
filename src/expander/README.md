La minishell detecta variables de entorno precedidas por `$VAR_NAME`
 (no `${VAR_NAME}`).
Los caracteres que componen el nombre de una variable de entorno 
tinen que ser alfa-numéricos o "_".

Solo tienen que expandirse cuando la palabra precedida por el `$` 
debe interpretarse en cualquier caso que no se encuentre entre comillas simples.
(WORD, DOUBLE_QUOTES, PIPE, IN_REDIR, OUT_REDIR, APPEND_REDIR  tokens).