#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

// Declaraciones de las funciones internas
void builtin_cd(char **args);
void builtin_pwd(void);
void builtin_unset(char **args);
void builtin_exit(void);
void builtin_env(char **environ);
void builtin_export(char **args);
void builtin_echo(char **args);

// Verifica si el comando es una función interna
int is_builtin(char *command);

// Ejecuta el comando interno correspondiente
void execute_builtin(char **args);

#endif

