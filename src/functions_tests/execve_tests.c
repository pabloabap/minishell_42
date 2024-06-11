#include "../../include/minishell.h"

#include <unistd.h>

/**
 * int execve(const char *pathname, char *const argv[], char *const envp[]);
 * 
 * @param pathname ejecutable binario o script que empieza por #!interpreter [optional-arg]
 * @param argv array de punterios a strings a pasar al nuevo programa como argumentos. 
 * 				Por convención el primero es el filename asociado al fichero a ejecutar.
 * 				Tiene que terminar en NULL pointer.
 * @param envp array de punteros a strings, por convenvión con formato key=value. Serán 
 * 				pasados como variables de entorno del nuevo programa. Tiene que terminar
 * 				con un puntero NULL.
 * 
 * @return no retorna en exito, y -1 y errno en error. 
**/

int main (void)
{
	char *pathname = "/usr/bin/echo";
	char *argv[] = {"echo", "\"$PATH\"", NULL};
	char *envp[] = {"PATH=HOLA", NULL};
	execve(pathname, argv, envp);

	return 0;
}

