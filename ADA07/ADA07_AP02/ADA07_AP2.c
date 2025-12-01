#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANO_TABLA_SIMBOLOS 101
#define MAX_IDENTIFICADOR 50
#define MAX_TIPO 20
#define MAX_AMBITO 10

typedef struct {
    char tipo[MAX_TIPO];
    int valor;
    char ambito[MAX_AMBITO];
} Atributos;

typedef struct NodoTabla {
    char identificador[MAX_IDENTIFICADOR];
    Atributos atributos;
    struct NodoTabla *siguiente;
} NodoTabla;

NodoTabla* tabla_simbolos[TAMANO_TABLA_SIMBOLOS];

void inicializarTablaSimbolos() {
    for (int i = 0; i < TAMANO_TABLA_SIMBOLOS; i++) {
        tabla_simbolos[i] = NULL;
    }
}

int funcionHashString(const char *clave) {
    unsigned long hash = 5381;
    int c;
    while ((c = *clave++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TAMANO_TABLA_SIMBOLOS;
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

NodoTabla* buscarIdentificador(const char *id) {
    if (strlen(id) == 0) return NULL;
    
    int indice = funcionHashString(id);
    NodoTabla *actual = tabla_simbolos[indice];

    while (actual != NULL) {
        if (strcmp(actual->identificador, id) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}


int agregarIdentificador(const char *id, const char *tipo, int valor, const char *ambito) {
    if (strlen(id) == 0) {
        printf("Error: Identificador no puede ser vacio.\n");
        return 0;
    }

    if (buscarIdentificador(id) != NULL) {
        printf("Error: El identificador '%s' ya fue declarado.\n", id);
        return 0;
    }

    int indice = funcionHashString(id);
    NodoTabla *nuevoNodo = (NodoTabla*)malloc(sizeof(NodoTabla)); 
    
    if (nuevoNodo == NULL) {
        perror("Error al asignar memoria");
        return 0;
    }

    strncpy(nuevoNodo->identificador, id, MAX_IDENTIFICADOR - 1);
    nuevoNodo->identificador[MAX_IDENTIFICADOR - 1] = '\0';
    
    strncpy(nuevoNodo->atributos.tipo, tipo, MAX_TIPO - 1);
    nuevoNodo->atributos.tipo[MAX_TIPO - 1] = '\0';
    
    nuevoNodo->atributos.valor = valor;
    
    strncpy(nuevoNodo->atributos.ambito, ambito, MAX_AMBITO - 1);
    nuevoNodo->atributos.ambito[MAX_AMBITO - 1] = '\0';

    nuevoNodo->siguiente = tabla_simbolos[indice];
    tabla_simbolos[indice] = nuevoNodo;

    printf(" Identificador '%s' agregado en el índice %d.\n", id, indice);
    return 1;
}

int eliminarIdentificador(const char *id) {
    if (strlen(id) == 0) return 0;
    
    int indice = funcionHashString(id);
    NodoTabla *actual = tabla_simbolos[indice];
    NodoTabla *anterior = NULL;

    while (actual != NULL) {
        if (strcmp(actual->identificador, id) == 0) {
            if (anterior == NULL) {
                tabla_simbolos[indice] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            
            free(actual);
            printf(" Identificador '%s' eliminado con éxito.\n", id);
            return 1;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    printf(" Error: Identificador '%s' no encontrado para eliminar.\n", id);
    return 0;
}


void mostrarMenuSimbolos() {
    printf("\n===========================================\n");
    printf(" APLICACION 02: TABLA DE SIMBOLOS (Cadenas)\n");
    printf("===========================================\n");
    printf("1. Agregar Identificador\n");
    printf("2. Buscar Identificador\n");
    printf("3. Eliminar Identificador\n");
    printf("4. Salir\n");
    printf("Seleccione una opcion: ");
}

void manejarOpcionSimbolos(int opcion) {
    char id[MAX_IDENTIFICADOR];
    char tipo[MAX_TIPO];
    char ambito[MAX_AMBITO];
    int valor;
    NodoTabla* encontrado;

    switch (opcion) {
        case 1:
            printf("\n--- AGREGAR IDENTIFICADOR ---\n");
            printf("Identificador (Nombre de variable/funcion): ");
            limpiarBuffer();
            if (fgets(id, MAX_IDENTIFICADOR, stdin) == NULL) return;
            id[strcspn(id, "\n")] = 0;

            printf("Tipo (int, float, funcion, etc.): ");
            if (fgets(tipo, MAX_TIPO, stdin) == NULL) return;
            tipo[strcspn(tipo, "\n")] = 0;

            printf("Ámbito (Global, Local, etc.): ");
            if (fgets(ambito, MAX_AMBITO, stdin) == NULL) return;
            ambito[strcspn(ambito, "\n")] = 0;

            printf("Valor (Inicial/Referencia - entero): ");
            if (scanf("%d", &valor) != 1) {
                printf("Entrada invalida para valor.\n");
                limpiarBuffer();
                break;
            }
            
            agregarIdentificador(id, tipo, valor, ambito);
            break;

        case 2:
            printf("\n--- BUSCAR IDENTIFICADOR ---\n");
            printf("Identificador a buscar: ");
            limpiarBuffer();
            if (fgets(id, MAX_IDENTIFICADOR, stdin) == NULL) return;
            id[strcspn(id, "\n")] = 0;

            encontrado = buscarIdentificador(id);
            if (encontrado) {
                printf(" Encontrado:\n");
                printf("   Nombre: %s\n", encontrado->identificador);
                printf("   Tipo: %s\n", encontrado->atributos.tipo);
                printf("   Valor: %d\n", encontrado->atributos.valor);
                printf("   Ámbito: %s\n", encontrado->atributos.ambito);
            } else {
                printf(" Identificador '%s' no encontrado.\n", id);
            }
            break;

        case 3:
            printf("\n--- ELIMINAR IDENTIFICADOR ---\n");
            printf("Identificador a eliminar: ");
            limpiarBuffer();
            if (fgets(id, MAX_IDENTIFICADOR, stdin) == NULL) return;
            id[strcspn(id, "\n")] = 0;
            
            eliminarIdentificador(id);
            break;

        case 4:
            printf("\nSaliendo del programa de Tabla de Simbolos.\n");
            break;

        default:
            printf("\nOpción no valida. Intente de nuevo.\n");
    }
}

int main() {
    inicializarTablaSimbolos();
    int opcion;
    setlocale(LC_ALL,"spanish");
    
    do {
        mostrarMenuSimbolos();
        if (scanf("%d", &opcion) != 1) {
            opcion = 0; 
            limpiarBuffer();
        }
        manejarOpcionSimbolos(opcion);
    } while (opcion != 4);

    return 0;
}