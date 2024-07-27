#include "../../include/builtins.h"


// Implementación de equal_sign
int equal_sign(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '=')
            return i;
        i++;
    }
    return -1; // No se encontró el signo igual
}

// Implementación de delete_quotes
void delete_quotes(char *str, char quote_char) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != quote_char) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

// Implementación de mini_env
void mini_env(t_env *env, t_single_cmd *simple_cmd) {
    // Implementación de ejemplo
    (void)simple_cmd;
    // Imprimir las variables de entorno
    for (int i = 0; env->envp[i] != NULL; i++) {
        printf("%s\n", env->envp[i]);
    }
}

// Implementación de builtin_export
void builtin_export(char **args, char **envp) {
    char *str = args[1];
    if (str[equal_sign(str)] == '\"') {
        delete_quotes(str, '\"');
    }
    // Agregar la variable de entorno
    envp = add_var(envp, str);
}

// Implementación de add_var
char **add_var(char **arr, char *str) {
    int len = 0;
    while (arr[len] != NULL) {
        len++;
    }
    char **new_arr = malloc((len + 2) * sizeof(char *));
    for (int i = 0; i < len; i++) {
        new_arr[i] = arr[i];
    }
    new_arr[len] = strdup(str);
    new_arr[len + 1] = NULL;
    free(arr);
    return new_arr;
}