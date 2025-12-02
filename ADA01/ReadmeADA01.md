El ADA01 se trato de construir un programa para evaluar expresiones aritmeticas, la herramienta principal que usamos para realizar esto fue la estructura Pila (stack).
El problema era que el programa tenía que leer expresiones "normales" (como las que escribimos, llamadas notación infija), que estaban en un archivo de entrada (exp_infijas.txt). Para poder calcularlas, implementamos un proceso que usan muchos lenguajes de programación.
Primero, teníamos que transformar la expresión infija a notación postfija. Una vez en postfija, teníamos que evaluar esa nueva expresión para obtener el resultado final.
Teníamos que ser muy cuidadosos con las prioridades de los operadores. Por ejemplo, los paréntesis () eran la máxima prioridad, seguidos por la potencia ^, luego * /, y al final + -.
El resultado final se tenía que escribir en un archivo de salida (exp_postfijas.txt) mostrando tanto la expresión postfija como el resultado de la evaluación, todo usando un punto y coma como delimitador.

Para mí, el mayor aprendizaje de este ADA fue ver la Pila en acción. Siempre la había visto como un concepto teórico. Aprendí que la Pila es indispensable para manejar las reglas de precedencia. Es la que decide qué operador tiene que esperar y cuál se ejecuta primero.
Logré dominar cómo usar dos pilas de manera coordinada (una para operadores y otra para operandos) para lograr la conversión y la evaluación.
Al principio tuve problemas con la lectura de archivos en C. Asegurar que leyéramos cada línea del archivo de entrada (exp_infijas.txt) y que escribiéramos en el formato exacto requerido en el archivo de salida (exp_postfijas.txt), pero con la ayuda de mi compañero lo pudimos solucionar.
