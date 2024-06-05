Aqui tenemos que incluir los archivos que separe el input en tokens.
Los tokens son las unidades básicas del lenguaje, como palabras clave, 
identificadores, operadores, números, cadenas, etc. El lexer también 
elimina los espacios en blanco y los comentarios que no son relevantes 
para el análisis sintáctico.

**Metacaracteres**: Caracteres que cuando están fuera de las comillas
 separan palabras: `space`, `tab`, `\n`, `|`, `&`, `\``', (`, `)`, `<` o `>`.

### Test cases
1. String que empieza con comillas dobles (") y tiene comillas simples (')
 en medio debe ignorarlas 
2. String que empieza con comillas simples (') y tiene comillas dobles (")
debe ignorarlas

{



}