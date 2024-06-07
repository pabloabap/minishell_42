
#include "../../include/main.h"
#include <stdio.h>

int main(void)
{
	char	*text;
	int		counter;

	counter = 0;
	while (1)
	{	
		//Muestra el texto del argumento por pantalla
		// y almacena el output en text.
		text = readline("Introduce texto");
		printf("HAS ESCRITO: %s\n", text);
		/*
			Almacena el texto escrito en readline en
			el historical de ejecución del programa.
		*/
		add_history(text);
		/* 
			`history_length` es una variable que se
			genera en el fichero history.c de la librería
			readline y almacena el numero de strings
			almacenadas en el historial de ejecucion
		*/
		printf("%d\n", history_length);
		/* 
			Bucle para que, guardados 6 inputs en el historial,
		 	borra el historial de ejecución con rl_clear_history()
		*/
		if (counter == 5)
		{
			rl_clear_history();
			printf("Historial limpiado\n");
		}
		counter ++;
	}
	return (0);
}
