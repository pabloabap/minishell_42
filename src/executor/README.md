Una vez que el lexer ha dividido el código fuente en tokens, el parser toma estos tokens y los organiza en una estructura más compleja, a menudo una estructura de árbol conocida como árbol de sintaxis abstracta (AST). 

El parser verifica que los tokens se ajusten a las reglas gramaticales del lenguaje. 
> La estructura de comandos en Shell es:
> cmd [arg]* [| cmd[arg]*]* [[>filename] [<filename][>& filename] [>> filename] [>>&filename]]* [&]

El parser verifica que estos componentes estén presentes y en el orden correcto.