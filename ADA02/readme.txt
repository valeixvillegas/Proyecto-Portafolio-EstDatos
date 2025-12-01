=== SIMULADOR DE BANCO - ADA02 ===
===Facultad de Matemáticas=== 
==Estructuras de Datos==
==Profesor: Luis Basto==

DESCRIPCIÓN:
Simulador de atención al cliente en un banco con 3 colas implementado en C++.
El programa maneja clientes que llegan aleatoriamente y son asignados a las colas
de manera automática.

CARACTERÍSTICAS:
- 3 colas implementadas con structs y memoria dinámica
- Clientes generados aleatoriamente con 1-5 transacciones
- Asignación automática a la cola con menos clientes
- Visualización del estado de las colas
- Estadísticas completas de atención
- Pruebas del sistema incluidas

COMPILACIÓN:
g++ -o banco_simulador banco_simulador.cpp

EJECUCIÓN:
./banco_simulador

FUNCIONAMIENTO:
1. El programa primero ejecuta pruebas básicas del sistema
2. Inicia la simulación por 30 unidades de tiempo
3. Muestra el estado de las colas cada 5 unidades
4. Al finalizar muestra estadísticas completas

ESTADÍSTICAS:
- Clientes atendidos por cola
- Clientes pendientes en cola
- Tiempo promedio de espera
- Estadísticas generales

ESTRUCTURAS:
- Cliente: id, transacciones, tiempoLlegada, tiempoAtencion
- Nodo: cliente, siguiente (apuntador)
- Cola: frente, final, atendidos, tiempoEsperaTotal, clientesEnCola

OPERACIONES DE COLA:
- inicializarCola()
- colaVacia()
- encolar()
- desencolar()
- verFrente()
- mostrarCola()

ENTREGA:
- Carpeta: ADA02
- Archivos: banco_simulador.cpp, readme.txt
- Comprimir como: ADA02_E01.zip

AUTOR:
-Diego Alejandro Alvarez López 
-Valeria Adriany Ix Villegas