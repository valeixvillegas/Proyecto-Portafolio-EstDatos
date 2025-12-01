#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Cliente {
    int id;
    int transacciones;
    int tiempoLlegada;
    int tiempoAtencion;
};

struct Nodo {
    struct Cliente cliente;
    struct Nodo* siguiente;
};

struct Cola {
    struct Nodo* frente;
    struct Nodo* final;
    int atendidos;
    int tiempoEsperaTotal;
    int clientesEnCola;
};

void inicializarCola(struct Cola* c) {
    c->frente = NULL;
    c->final = NULL;
    c->atendidos = 0;
    c->tiempoEsperaTotal = 0;
    c->clientesEnCola = 0;
}

int colaVacia(struct Cola* c) {
    return c->frente == NULL;
}

void encolar(struct Cola* c, struct Cliente cli) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo->cliente = cli;
    nuevo->siguiente = NULL;

    if (colaVacia(c)) {
        c->frente = nuevo;
        c->final = nuevo;
    } else {
        c->final->siguiente = nuevo;
        c->final = nuevo;
    }
    c->clientesEnCola++;
}

struct Cliente desencolar(struct Cola* c) {
    if (colaVacia(c)) {
        struct Cliente vacio = {-1, 0, 0, 0};
        return vacio;
    }
    
    struct Nodo* temp = c->frente;
    struct Cliente cli = temp->cliente;
    c->frente = temp->siguiente;
    
    if (c->frente == NULL) {
        c->final = NULL;
    }
    
    free(temp);
    c->clientesEnCola--;
    return cli;
}

struct Cliente verFrente(struct Cola* c) {
    if (colaVacia(c)) {
        struct Cliente vacio = {-1, 0, 0, 0};
        return vacio;
    }
    return c->frente->cliente;
}

void mostrarCola(struct Cola* c, int numero) {
    printf("Cola %d: [", numero);
    if (colaVacia(c)) {
        printf("VACIA");
    } else {
        struct Nodo* actual = c->frente;
        while (actual != NULL) {
            printf("C%d(%d)", actual->cliente.id, actual->cliente.transacciones);
            if (actual->siguiente != NULL) {
                printf(" -> ");
            }
            actual = actual->siguiente;
        }
    }
    printf("]\n");
}

struct Cliente crearCliente(int id, int tiempo) {
    struct Cliente c;
    c.id = id;
    c.transacciones = 1 + rand() % 5;
    c.tiempoLlegada = tiempo;
    c.tiempoAtencion = -1;
    return c;
}

int elegirCola(struct Cola* c1, struct Cola* c2, struct Cola* c3) {
    if (c1->clientesEnCola <= c2->clientesEnCola && c1->clientesEnCola <= c3->clientesEnCola) return 1;
    if (c2->clientesEnCola <= c1->clientesEnCola && c2->clientesEnCola <= c3->clientesEnCola) return 2;
    return 3;
}

void procesarCola(struct Cola* c, int numCola, int tiempo) {
    if (!colaVacia(c)) {
        struct Cliente* actual = &c->frente->cliente;
        
        if (actual->tiempoAtencion == -1) {
            actual->tiempoAtencion = tiempo;
            printf("Tiempo %d: Cliente %d comienza atencion en Cola %d\n", tiempo, actual->id, numCola);
        }
        
        actual->transacciones--;
        
        if (actual->transacciones == 0) {
            struct Cliente terminado = desencolar(c);
            int espera = tiempo - terminado.tiempoLlegada;
            c->tiempoEsperaTotal += espera;
            c->atendidos++;
            printf("Tiempo %d: Cliente %d sale de Cola %d (espera: %d)\n", tiempo, terminado.id, numCola, espera);
        }
    }
}

void mostrarEstadisticas(struct Cola* c1, struct Cola* c2, struct Cola* c3, int tiempoTotal) {
    printf("\n=== ESTADISTICAS ===\n");
    printf("Tiempo de simulacion: %d\n", tiempoTotal);
    
    for (int i = 1; i <= 3; i++) {
        struct Cola* c;
        if (i == 1) c = c1;
        else if (i == 2) c = c2;
        else c = c3;
        
        printf("\nCola %d:\n", i);
        printf("  Atendidos: %d\n", c->atendidos);
        printf("  En cola: %d\n", c->clientesEnCola);
        
        if (c->atendidos > 0) {
            float promedio = (float)c->tiempoEsperaTotal / c->atendidos;
            printf("  Espera promedio: %.2f\n", promedio);
        }
    }
    
    int totalAtendidos = c1->atendidos + c2->atendidos + c3->atendidos;
    int totalEspera = c1->tiempoEsperaTotal + c2->tiempoEsperaTotal + c3->tiempoEsperaTotal;
    
    printf("\nTOTAL:\n");
    printf("  Clientes atendidos: %d\n", totalAtendidos);
    if (totalAtendidos > 0) {
        printf("  Espera promedio: %.2f\n", (float)totalEspera / totalAtendidos);
    }
}

void liberarTodo(struct Cola* c1, struct Cola* c2, struct Cola* c3) {
    while (!colaVacia(c1)) desencolar(c1);
    while (!colaVacia(c2)) desencolar(c2);
    while (!colaVacia(c3)) desencolar(c3);
}

void probarSistema() {
    printf("Probando el sistema...\n");
    
    struct Cola prueba;
    inicializarCola(&prueba);
    
    struct Cliente c1 = crearCliente(1, 0);
    struct Cliente c2 = crearCliente(2, 1);
    
    encolar(&prueba, c1);
    encolar(&prueba, c2);
    
    printf("Cola de prueba: ");
    mostrarCola(&prueba, 0);
    
    desencolar(&prueba);
    printf("Despues de desencolar: ");
    mostrarCola(&prueba, 0);
    
    while (!colaVacia(&prueba)) {
        desencolar(&prueba);
    }
}

int main() {
    srand(time(NULL));
    
    struct Cola cola1, cola2, cola3;
    inicializarCola(&cola1);
    inicializarCola(&cola2);
    inicializarCola(&cola3);
    
    probarSistema();
    
    int tiempo = 0;
    int idCliente = 1;
    int duracion = 30;
    
    printf("\n=== SIMULACION DE BANCO ===\n");
    
    while (tiempo < duracion || !colaVacia(&cola1) || !colaVacia(&cola2) || !colaVacia(&cola3)) {
        if (tiempo < duracion && rand() % 100 < 40) {
            struct Cliente nuevo = crearCliente(idCliente, tiempo);
            int cola = elegirCola(&cola1, &cola2, &cola3);
            
            if (cola == 1) {
                encolar(&cola1, nuevo);
                printf("Tiempo %d: Cliente %d llega a Cola 1\n", tiempo, nuevo.id);
            } else if (cola == 2) {
                encolar(&cola2, nuevo);
                printf("Tiempo %d: Cliente %d llega a Cola 2\n", tiempo, nuevo.id);
            } else {
                encolar(&cola3, nuevo);
                printf("Tiempo %d: Cliente %d llega a Cola 3\n", tiempo, nuevo.id);
            }
            idCliente++;
        }
        
        procesarCola(&cola1, 1, tiempo);
        procesarCola(&cola2, 2, tiempo);
        procesarCola(&cola3, 3, tiempo);
        
        if (tiempo % 5 == 0) {
            printf("\n");
            mostrarCola(&cola1, 1);
            mostrarCola(&cola2, 2);
            mostrarCola(&cola3, 3);
            printf("\n");
        }
        
        tiempo++;
    }
    
    mostrarEstadisticas(&cola1, &cola2, &cola3, tiempo);
    liberarTodo(&cola1, &cola2, &cola3);
    
    return 0;
}