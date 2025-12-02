La Aplicación 01 del ADA 07 se centró en construir un sistema de registro de estudiantes utilizando la estructura de datos Tabla Hash.
El objetivo principal era lograr un sistema de búsqueda y gestión ultrarrápida para los estudiantes. Para esto, usamos la matrícula del estudiante (un número de hasta 6 dígitos) como la clave que nos permitía llegar directamente a su información (nombre, carrera, etc.) dentro de la tabla.
El sistema debía ser capaz de realizar las operaciones básicas de cualquier base de datos de manera eficiente, agregar un nuevo estudiante por su matrícula, buscar y recuperar la información de un estudiante por su matrícula.
y eliminar un registro completo de estudiante por matrícula.

Esta aplicación me ayudó a entender que las Tablas Hash son la estructura más rápida para sistemas de registro con IDs numéricos.
ntendí que si la función hash es buena, la búsqueda es casi instantánea.
Aunque el hashing es eficiente, tuvimos que asegurar que la matrícula ingresada por el usuario fuera correcta (que tuviera el formato numérico de hasta 6 dígitos). Integrar la validación de entrada
y la lógica de búsqueda con un mensaje claro de "Estudiante encontrado" o "Matrícula no encontrada" requería un buen diseño.
