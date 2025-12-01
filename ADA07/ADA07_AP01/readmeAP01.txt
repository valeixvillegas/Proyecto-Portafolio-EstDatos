===========================================
        ADA07 - Aplicación 01
  Registro de Estudiantes con Hashing
===========================================

Este programa implementa una tabla hash con
direccionamiento abierto (sondeo lineal) para
almacenar estudiantes por matrícula.  
Incluye un menú interactivo para agregar, buscar
y eliminar estudiantes.

-------------------------------------------
ARCHIVOS INCLUIDOS
-------------------------------------------

main.c  
(Contiene:
- Estructura Estudiante
- Tabla hash con 101 posiciones
- Hash: clave % 101
- Funciones: agregar, buscar, eliminar
- Control de colisiones (sondeo lineal)
- Menú interactivo
)

-------------------------------------------
REQUISITOS
-------------------------------------------

• Compilador C (gcc, MinGW, Clang, etc.)  
• Sistema operativo Windows, Linux o MacOS.

-------------------------------------------
CÓMO COMPILAR
-------------------------------------------

En Windows (MinGW):
    gcc main.c -o Aplicacion01.exe

En Linux o MacOS:
    gcc main.c -o Aplicacion01

Asegúrate de estar dentro de la carpeta:
    ADA07_AP01

-------------------------------------------
CÓMO EJECUTAR
-------------------------------------------

En Windows:
    Aplicacion01.exe

En Linux o MacOS:
    ./Aplicacion01

-------------------------------------------
FUNCIONALIDADES IMPLEMENTADAS
-------------------------------------------

-Agregar estudiante  
-Matrícula (máx. 6 dígitos)  
-Nombre 
-Carrera  

-Buscar estudiante por matrícula  

-Eliminar estudiante   

-Manejo de colisiones con sondeo lineal  

- Menú interactivo:  
    1. Agregar  
    2. Buscar  
    3. Eliminar  
    4. Salir  

-Validación de entradas  
-Limpieza de buffer con getchar()

-------------------------------------------
AUTOR(ES)
-------------------------------------------
-E01:
- Diego Alejandro Alvarez López 
- Valeria Adriany Ix Villegas