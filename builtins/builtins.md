## Builtins
### `echo [-n] [arg ...]`
Muestra los argumentos, separados por espacios, seguidos de un salto de línea. El estado de retorno es siempre 0. Si se especifica `-n`, se suprime el salto de línea final.

### `cd [dir]`
Cambia el directorio actual a dir. La variable HOME es el directorio predeterminado. La variable `CDPATH` define la ruta de búsqueda para el directorio que contiene dir. Los nombres de directorios alternativos en `CDPATH` están separados por dos puntos (:). Un nombre de directorio nulo en `CDPATH` es el mismo que el directorio actual, es decir, ''.''. Si dir comienza con una barra inclinada (/), entonces `CDPATH` no se utiliza. Si se usa un nombre de directorio no vacío de `CDPATH` y el cambio de directorio es exitoso, la ruta absoluta del nuevo directorio de trabajo se escribe en la salida estándar. El valor de retorno es verdadero si el directorio se cambió con éxito; falso en caso contrario.

### `pwd`
Imprime la ruta absoluta del directorio de trabajo actual. El estado de retorno es 0 a menos que ocurra un error al leer el nombre del directorio actual o se suministre una opción no válida.

### `export name=value ...`
El valor de la variable de entorno name se establece en value. Si la variable de entorno name no existe, se crea. Si no se da ningún valor, el valor se establecerá en "". export devuelve un estado de salida de 0 a menos que uno de los nombres no sea un nombre de variable de shell válido.
El texto después del '=' se somete a expansión de variables y eliminación de comillas antes de asignarse a la variable.

### `unset [name ...]`
Para cada nombre, elimina la variable correspondiente. Cada nombre se refiere a una variable de shell. Las variables de solo lectura no se pueden desestablecer. Cada variable desestablecida se elimina del entorno pasado a los comandos posteriores. El estado de salida es verdadero a menos que un nombre sea de solo lectura.

### `env`
Imprime el entorno actual.

### `exit [N]`
Imprime `exit` seguido de un salto de línea antes de cerrar el shell devolviendo el estado de salida N. Si N no está definido, el estado de salida es el del último comando ejecutado. La palabra `exit` no se imprime si la salida ha sido redirigida o canalizada.

> [!NOTA]  
> Los comandos internos devuelven 0 si tienen éxito, y un valor distinto de cero si ocurre un error mientras se ejecutan.

