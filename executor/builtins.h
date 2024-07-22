#ifndef BUILTINS_H
#define BUILTINS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Declaraciones de las funciones internas

void builtin_cd(char **args);
void builtin_pwd(char **args);
void builtin_unset(char **args);
void builtin_exit(char **args);
void builtin_env(char **args);
void builtin_export(char **args);
void builtin_echo(char **args);

// Verifica si el comando es una función interna
int is_builtin(char *command);

// Ejecuta el comando interno correspondiente
void execute_builtin(char **args);

#endif

