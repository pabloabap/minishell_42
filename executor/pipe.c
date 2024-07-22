#include "pipe.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Verifica si hay un pipe en los comandos
int is_pipeline(char **commands) {
    int i = 0;
    while (commands[i] != NULL) {
        if (strcmp(commands[i], "|") == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

// Analiza los comandos en una estructura para pipelines
char ***parse_pipeline(char **commands) {
    int i = 0, j = 0, k = 0;
    char ***pipeline = malloc(10 * sizeof(char **));
    pipeline[j] = malloc(10 * sizeof(char *));
    while (commands[i] != NULL) {
        if (strcmp(commands[i], "|") == 0) {
            pipeline[j][k] = NULL;
            j++;
            k = 0;
            pipeline[j] = malloc(10 * sizeof(char *));
        } else {
            pipeline[j][k] = commands[i];
            k++;
        }
        i++;
    }
    pipeline[j][k] = NULL;
    pipeline[j + 1] = NULL;
    return pipeline;
}

