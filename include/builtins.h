#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

// Definición de la estructura t_env
typedef struct s_env {
    char **envp;
} t_env;

// Declaraciones de las funciones internas
void builtin_cd(char **args, char **envp);
void builtin_pwd(char **args, char **envp);
void builtin_unset(char **args, char **envp);
void builtin_exit(char **args, char **envp);
void builtin_env(char **args, char **envp);
void builtin_export(char **args, char **envp);
void builtin_echo(char **args, char **envp);

typedef void (*builtin_func)(char **args, char **envp);

builtin_func builtin_arr(char *str);

int is_builtin(char *command);
void execute_builtin(char **args, char **envp);
char **add_var(char **arr, char *str);
void whileloop_add_var(char **arr, char **rtn, char *str);

// Declaraciones de las funciones faltantes
int equal_sign(char *str);
void delete_quotes(char *str, char quote_char);
void mini_env(t_env *env, t_single_cmd *simple_cmd);

#endif

