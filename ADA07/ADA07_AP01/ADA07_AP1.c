#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANO_TABLA 101
#define MATRICULA_VACIA -1
#define MATRICULA_ELIMINADA -2
#define MAX_NOMBRE 50
#define MAX_CARRERA 50

typedef struct {
    int matricula;
    char nombre[MAX_NOMBRE];
    char carrera[MAX_CARRERA];
} Estudiante;

Estudiante tabla[TAMANO_TABLA];

void inicializarTabla() {
    for (int i = 0; i < TAMANO_TABLA; i++) {
        tabla[i].matricula = MATRICULA_VACIA;
    }
}

int funcionHash(int clave) {
    return clave % TAMANO_TABLA;
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Estudiante* buscarEstudiante(int matricula) {
    int indiceInicial = funcionHash(matricula);
    int i = 0;
    
    while (i < TAMANO_TABLA) {
        int indiceActual = (indiceInicial + i) % TAMANO_TABLA;
        
        if (tabla[indiceActual].matricula == matricula) {
            return &tabla[indiceActual];
        }
        
        if (tabla[indiceActual].matricula == MATRICULA_VACIA) {
            return NULL;
        }
        
        i++;
    }
    return NULL;
}


int agregarEstudiante(int matricula, const char* nombre, const char* carrera) {
    if (matricula <= 0 || matricula > 999999) {
        printf("Error: La matricula debe ser positiva y tener un maximo de 6 digitos.\n");
        return 0;
    }

    if (buscarEstudiante(matricula) != NULL) {
        printf(" Error: La matricula %d ya existe en la tabla.\n", matricula);
        return 0; 
    }
    
    int indiceInicial = funcionHash(matricula);
    int i = 0;
    
    while (i < TAMANO_TABLA) {
        int indiceActual = (indiceInicial + i) % TAMANO_TABLA;
        
        if (tabla[indiceActual].matricula == MATRICULA_VACIA || tabla[indiceActual].matricula == MATRICULA_ELIMINADA) {
            tabla[indiceActual].matricula = matricula;
            strncpy(tabla[indiceActual].nombre, nombre, MAX_NOMBRE - 1);
            tabla[indiceActual].nombre[MAX_NOMBRE - 1] = '\0';
            strncpy(tabla[indiceActual].carrera, carrera, MAX_CARRERA - 1);
            tabla[indiceActual].carrera[MAX_CARRERA - 1] = '\0';
            
            printf("Estudiante %d agregado en el indice %d.\n", matricula, indiceActual);
            return 1;
        }
        
        i++;
    }
    printf("Error: Tabla hash llena.\n");
    return 0;
}

int eliminarEstudiante(int matricula) {
    Estudiante* estudiante = buscarEstudiante(matricula);
    
    if (estudiante != NULL) {
        estudiante->matricula = MATRICULA_ELIMINADA; 
        printf(" Estudiante %d eliminado (marcado).\n", matricula);
        return 1;
    } else {
        printf(" Error: Matricula %d no encontrada para eliminar.\n", matricula);
        return 0;
    }
}

void mostrarMenu() {
    printf("\n===================================\n");
    printf(" GESTOR DE ESTUDIANTES (HASH TABLE)\n");
    printf("===================================\n");
    printf("1. Agregar Estudiante\n");
    printf("2. Buscar Estudiante (por Matricula)\n");
    printf("3. Eliminar Estudiante (por Matricula)\n");
    printf("4. Salir\n");
    printf("Seleccione una opcion: ");
}

void manejarOpcion(int opcion) {
    int matricula;
    Estudiante* encontrado;
    char nombre[MAX_NOMBRE];
    char carrera[MAX_CARRERA];

    switch (opcion) {
        case 1:
            printf("\n--- AGREGAR ESTUDIANTE ---\n");
            printf("Ingrese la matricula (Max 6 digitos): ");
            if (scanf("%d", &matricula) != 1) {
                printf("Entrada invalida.\n");
                limpiarBuffer();
                break;
            }
            limpiarBuffer(); 
            
            
            printf("Ingrese el nombre: ");
            if (fgets(nombre, MAX_NOMBRE, stdin) == NULL) return;
            nombre[strcspn(nombre, "\n")] = 0;
            
            printf("Ingrese la carrera: ");
            if (fgets(carrera, MAX_CARRERA, stdin) == NULL) return;
            carrera[strcspn(carrera, "\n")] = 0;

            agregarEstudiante(matricula, nombre, carrera);
            break;

        case 2:
            printf("\n--- BUSCAR ESTUDIANTE ---\n");
            printf("Ingrese la matricula a buscar: ");
            if (scanf("%d", &matricula) != 1) {
                printf("Entrada invalida.\n");
                limpiarBuffer();
                break;
            }
            limpiarBuffer();
            
            encontrado = buscarEstudiante(matricula);
            if (encontrado) {
                printf(" Encontrado:\n");
                printf("   Matricula: %d\n", encontrado->matricula);
                printf("   Nombre: %s\n", encontrado->nombre);
                printf("   Carrera: %s\n", encontrado->carrera);
            } else {
                printf(" Matricula %d no encontrada.\n", matricula);
            }
            break;

        case 3:
            printf("\n--- ELIMINAR ESTUDIANTE ---\n");
            printf("Ingrese la matricula a eliminar: ");
            if (scanf("%d", &matricula) != 1) {
                printf("Entrada invalida.\n");
                limpiarBuffer();
                break;
            }
            limpiarBuffer();
            
            eliminarEstudiante(matricula);
            break;

        case 4:
            printf("\nSaliendo del programa. ¡Hasta luego!\n");
            break;

        default:
            printf("\nOpcion no valida. Intente de nuevo.\n");
            limpiarBuffer();
    }
}

int main() {
    inicializarTabla();
    int opcion;
    setlocale(LC_ALL, "");
    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            opcion = 0;
            limpiarBuffer();
        }
        manejarOpcion(opcion);
    } while (opcion != 4);

    return 0;
}