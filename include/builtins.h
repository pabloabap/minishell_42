#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

// Declaraciones de las funciones internas
void builtin_cd(char **args, char **envp);
void builtin_pwd(void);
void builtin_unset(char **args, char **envp);
void builtin_exit(void);
void builtin_env(char **args, char **envp);
void builtin_export(char **args, char **envp);
void builtin_echo(char **args, char ** envp);

typedef void (*builtin_func)(char **args, char **envp);

builtin_func builtin_arr(char *str);

int is_builtin(char *command);
void execute_builtin(char **args, char **envp);

#endif

