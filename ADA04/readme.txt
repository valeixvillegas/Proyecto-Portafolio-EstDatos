UNIVERSIDAD AUTÓNOMA DE YUCATÁN  
Facultad de Matemáticas  
Materia: Estructuras de Datos  
Profesor: Luis R. Basto  
Actividad: ADA04 – Gestión de estudiantes con Árbol Binario de Búsqueda  
Equipo: E01  

---------------------------------------------------------
INTEGRANTES
---------------------------------------------------------
- Valeria Ix Villegas  
- Diego Álvarez López  

---------------------------------------------------------
DESCRIPCIÓN GENERAL
---------------------------------------------------------
El programa implementa un sistema de gestión de estudiantes utilizando un
Árbol Binario de Búsqueda (ABB) en lenguaje C.  
Cada estudiante se almacena en un nodo del árbol y contiene los siguientes
datos:
- Matrícula
- Nombre
- Apellido
- Calificaciones (arreglo dinámico)

La matrícula determina la posición del nodo dentro del árbol.  
El sistema permite insertar, eliminar, modificar y consultar información
de los estudiantes, además de generar reportes y visualizar el árbol.

---------------------------------------------------------
FUNCIONALIDADES DEL PROGRAMA
---------------------------------------------------------
1. Mostrar todos los estudiantes ordenados por matrícula.  
2. Mostrar todos los estudiantes ordenados por promedio.  
3. Generar reporte de estudiantes con promedio menor a 70.  
4. Generar reporte de estudiantes con promedio mayor o igual a 70.  
5. Insertar un nuevo estudiante.  
6. Eliminar un estudiante dado su matrícula.  
7. Actualizar una calificación de un alumno.  
8. Contar cuántos alumnos tienen promedio menor al de una matrícula dada.  
9. Mostrar los valores de los nodos de un nivel específico.  
10. Mostrar el árbol binario de búsqueda en formato ASCII.  

---------------------------------------------------------
REQUERIMIENTOS TÉCNICOS
---------------------------------------------------------
- Lenguaje: C  
- Estructura de datos: Árbol Binario de Búsqueda  
- Uso de memoria dinámica (malloc y free)  
- Uso de funciones separadas para operaciones  
- Los datos se mantienen solo en memoria durante la ejecución  

---------------------------------------------------------
INSTRUCCIONES DE EJECUCIÓN (Visual Studio)
---------------------------------------------------------
1. Abrir Visual Studio.  
2. Crear un nuevo proyecto de tipo “Proyecto de C vacío”.  
3. En el Explorador de soluciones, clic derecho en “Source Files” → “Agregar” → “Nuevo elemento”.  
4. Crear el archivo: *ADA04.c*  
5. Copiar y pegar el código fuente del programa.  
6. Presionar *Ctrl + F5* para compilar y ejecutar.  

---------------------------------------------------------
MENÚ PRINCIPAL DEL PROGRAMA
---------------------------------------------------------
1. Insertar estudiante  
2. Reporte por matrícula  
3. Reporte por promedio  
4. Promedios menores a 70  
5. Promedios mayores o iguales a 70  
6. Eliminar estudiante  
7. Actualizar calificación  
8. Contar alumnos con promedio menor  
9. Mostrar nivel del árbol  
10. Mostrar árbol gráfico  
0. Salir  

---------------------------------------------------------