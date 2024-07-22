#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtins.h"
#include "pipe.h"

// Función para ejecutar un comando simple
void execute_command(char **args);

// Función para ejecutar una tubería de comandos
void execute_pipeline(char ***commands);

// Función para analizar la entrada del usuario en comandos y argumentos
char **parse_input(char *input);

// Verifica si los comandos contienen una tubería
int is_pipeline(char **commands);

// Función para analizar los comandos de una tubería
char ***parse_pipeline(char **commands);

#endif

