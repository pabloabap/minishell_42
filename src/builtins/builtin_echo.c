#include "../../include/minishell.h"

// Función auxiliar para imprimir líneas
static void print_lines(int start_index, char **args, int fd)
{
    int i = start_index;

    while (args[i] != NULL) {
        ft_putstr_fd(args[i], fd);
        if (args[i + 1] != NULL) {
            ft_putchar_fd(' ', fd);
        }
        i++;
    }
}

// Implementación del comando 'echo'
int builtin_echo(char **args)
{
    int i = 1;
    int j;
    int n_option = 0;

    // Manejo de la opción '-n'
    while (args[i] != NULL && args[i][0] == '-' && args[i][1] == 'n') {
        j = 1;
        while (args[i][j] == 'n') {
            j++;
        }
        if (args[i][j] == '\0') {
            n_option = 1;
        } else {
            break;
        }
        i++;
    }

    // Imprimir los argumentos
    print_lines(i, args, STDOUT_FILENO);

    // Imprimir salto de línea si no se ha especificado la opción '-n'
    if (!n_option) {
        ft_putchar_fd('\n', STDOUT_FILENO);
    }

    return EXIT_SUCCESS;
}

