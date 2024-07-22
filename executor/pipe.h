#ifndef PIPE_H
#define PIPE_H

// Verifica si los comandos contienen una tubería
int is_pipeline(char **commands);

// Función para analizar los comandos de una tubería
char ***parse_pipeline(char **commands);

#endif

