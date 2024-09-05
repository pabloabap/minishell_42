# Minishell
## Explicación
TBD
## BUGS
- [ ] `Ctrl` + `\` (`SIGQUIT`) - Funciona como se espera pero muestra caracter `^\` en la linea. Si se es completamente estricto tampoco debería aparecer el caracter.
- [ ] `$SHLVL` no se gestiona. Debería mostrar el nivel de profundidad de bash en el que se ejecuta el programa.
- [ ] La señal `SIGINT` en **heredoc** se comportan como si estuvieras en el programa principal (printea nueva linea, pero debería cerrar el fichero).
- [ ] `cat file | grep bla | s | pwd` - exit code tendría que ser 0 pero se queda con el 127 del command not found de s.
- [ ] En los casos que comandos previos terminen antes que comandos posteriores a veces el proceso padre retorna 141 (`SIGPIPE`) en vez del código de salida esperado. Esto ocurre por intentar escribir en PIPES ya cerrados por los procesos anteriores.
