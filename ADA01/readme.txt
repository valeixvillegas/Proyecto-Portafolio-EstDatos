=========================================
   Proyecto ADA01 - Pilas
   Parser de Expresiones Aritméticas
=========================================

Profesor: Luis R. Basto
Materia: Estructuras de Datos
Formato: Equipo 1

-----------------------------------------
Descripción
-----------------------------------------
Este programa implementa un parser de expresiones aritméticas
usando pilas creadas manualmente con nodos enlazados.

El proceso es:
1. Leer expresiones en notación infija desde un archivo de entrada.
2. Convertir cada expresión a notación postfija (RPN).
3. Evaluar la expresión postfija.
4. Generar un archivo de salida con la expresión postfija y su resultado.

Ejemplo:
Entrada:   ((2+4)7)+3(9-5);
Salida:    Expresión: 2 4 + 7 * 3 9 5 - * +; Resultado: 54

-----------------------------------------
Archivos incluidos
-----------------------------------------
- InfijoAPostfijoApp.cpp   -> Código fuente principal
- exp_infijas.txt          -> Archivo de entrada con expresiones infijas
- exp_postfijas.txt        -> Archivo de salida generado por el programa
- readme.txt               -> Este archivo con las instrucciones

-----------------------------------------
Compilación
-----------------------------------------
En una terminal (cmd o bash), situarse dentro de la carpeta ADA01
y compilar con:

    g++ InfijoAPostfijoApp.cpp -o InfijoAPostfijoApp

Esto generará el ejecutable llamado "InfijoAPostfijoApp".

-----------------------------------------
Ejecución
-----------------------------------------
Para ejecutar el programa, usar:

    ./InfijoAPostfijoApp exp_infijas.txt

El programa leerá las expresiones del archivo exp_infijas.txt
(separadas por ';') y generará un archivo exp_postfijas.txt con
las expresiones en notación postfija y sus resultados.

-----------------------------------------
Ejemplo de Entrada (exp_infijas.txt)
-----------------------------------------
2+3;
2*(3+4);
((2+4)7)+3(9-5);
10+2*6;
100*(2+12)/14;
3^2+4*(5-2);

-----------------------------------------
Ejemplo de Salida (exp_postfijas.txt)
-----------------------------------------
Expresión: 2 3 +; Resultado: 5
Expresión: 2 3 4 + *; Resultado: 14
Expresión: 2 4 + 7 * 3 9 5 - * +; Resultado: 54
Expresión: 10 2 6 * +; Resultado: 22
Expresión: 100 2 12 + * 14 /; Resultado: 100
Expresión: 3 2 ^ 4 5 2 - * +; Resultado: 19

-----------------------------------------
Notas
-----------------------------------------
- Se utilizan pilas implementadas con nodos enlazados (struct Nodo).
- Los operadores soportados son: +, -, *, /, ^ y paréntesis.
- La prioridad de operadores está implementada correctamente.
- Solo se manejan números enteros positivos.
- Las expresiones deben estar bien formadas y terminadas con ';'.