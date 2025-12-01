===========================================
      ADA07 – Aplicación 02
        Tabla de Símbolos 
===========================================

Este programa implementa una tabla de símbolos
para un compilador, usando hashing con cadenas
como clave.  
Cada identificador almacena: tipo, valor y ámbito.  
Las colisiones se manejan con listas ligadas.

Incluye un menú interactivo para agregar,
buscar y eliminar identificadores.

-------------------------------------------
ARCHIVOS INCLUIDOS
-------------------------------------------

main.c
(Contiene:
- Estructura Atributos
- Definición de NodoTabla para listas ligadas
- Tabla hash de tamaño 101
- Hash para strings
- Funciones: agregar, buscar, eliminar
- Menú de interacción con el usuario
)

-------------------------------------------
REQUISITOS
-------------------------------------------

• Compilador C (gcc, MinGW, Clang).  
• Sistema operativo Windows, Linux o Mac.  

-------------------------------------------
CÓMO COMPILAR
-------------------------------------------

En Windows (MinGW):
    gcc main.c -o aplicacion02.exe

En Linux / Mac:
    gcc main.c -o aplicacion02

Debe compilarse dentro de la carpeta:
    ADA07_AP02

-------------------------------------------
CÓMO EJECUTAR
-------------------------------------------

En Windows:
    aplicacion02.exe

En Linux o Mac:
    ./aplicacion02

-------------------------------------------
FUNCIONALIDADES IMPLEMENTADAS
-------------------------------------------

- Agregar identificador
    - Nombre (string)
    - Tipo (int, float, funcion, etc.)
    - Valor (int, float etc.)
    - Ámbito (Global/Local)

- Buscar identificador  
- Eliminar identificador  
- Manejo de colisiones mediante listas ligadas  
- Recorre la cubeta para buscar y eliminar  
- Validación de identificadores repetidos  

-------------------------------------------
NOTAS IMPORTANTES
-------------------------------------------

• No se permite declarar un identificador repetido.  
• El usuario puede ingresar texto con espacios.  
• El valor asignado debe ser uno válido.  
• El programa funciona hasta que el usuario elige opción 4.

-------------------------------------------
AUTOR(ES)
-------------------------------------------
- Diego Alejandro Alvarez López 
- Valeria Adriany Ix Villegas