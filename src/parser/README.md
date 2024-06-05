Una vez que el lexer ha dividido el código fuente en tokens, el parser toma estos tokens y los organiza en una estructura más compleja, a menudo una estructura de árbol conocida como árbol de sintaxis abstracta (AST). 

El parser verifica que los tokens se ajusten a las reglas gramaticales del lenguaje. 
> La estructura de comandos en Shell es:
> cmd [arg]* [| cmd[arg]*]* [[>filename] [<filename][>& filename] [>> filename] [>>&filename]]* [&]

 Indicadores de variables a expandir: "${", "$(" or '`', and "$(("

El parser verifica que estos componentes estén presentes y en el orden correcto.

## Test cases
1. String que empieza con comillas dobles (") y tiene comillas simples (')
 en medio debe imprimir las comillas simples. **Tratar todos los metacaracteres** 
 **como caracteres normales excepto `$`que tendra que expandirse a su variable** 
 **de entorno**. Si la variable de entorno no existe no devuelve caracteres. 
2. String que empieza con comillas simples (') y tiene comillas dobles (")
Las muestra como son y muestra todos los metacaracteres como caracteres normales.
Leer hasta metacaracter, comilla simple o comilla doble e introducirlo en una estructura.