#include "executor.h"
#include "builtins.h"
#include "pipe.h"
#include "executor_utils.h"

// Ejecuta un comando simple (sin pipes)
void execute_command(char **args) {
    if (args[0] == NULL) {
        return; // Si no hay comando, no hacer nada
    }

    if (is_builtin(args[0])) {
        execute_builtin(args); // Ejecuta comandos internos
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("execvp");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
        } else {
            wait(NULL); // Espera a que el proceso hijo termine
        }
    }
}

// Ejecuta una tubería (pipeline) de comandos
void execute_pipeline(char ***commands) {
    int i = 0;
    int pipefd[2];
    int in_fd = 0;

    while (commands[i] != NULL) {
        pipe(pipefd);
        if (fork() == 0) {
            dup2(in_fd, 0);
            if (commands[i + 1] != NULL) {
                dup2(pipefd[1], 1);
            }
            close(pipefd[0]);
            execvp(commands[i][0], commands[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
            close(pipefd[1]);
            in_fd = pipefd[0];
            i++;
        }
    }
}

int main(int argc, char **argv) {
    char *input;
    while (1) {
        input = readline("$ ");
        if (!input) {
            break; // Salir del bucle si no hay entrada
        }

        if (strlen(input) > 0) {
            add_history(input); // Añadir la entrada al historial
        }

        char **commands = parse_input(input); // Analiza la entrada en comandos y argumentos
        if (is_pipeline(commands)) {
            char ***pipeline_commands = parse_pipeline(commands); // Analiza los comandos multiples
            execute_pipeline(pipeline_commands);
        } else {
            execute_command(commands); // Ejecuta un comando simple
        }

        free(input);
    }
    return 0;
}
