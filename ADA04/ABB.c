#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

typedef struct {
    int matricula;
    char nombre[50];
    char apellido[50];
    float *calificaciones;
    int numCalificaciones;
} Estudiante;

typedef struct Nodo {
    Estudiante est;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

float promedio(Estudiante e) {
    if (e.numCalificaciones == 0) return 0;
    float suma = 0;
    for (int i = 0; i < e.numCalificaciones; i++) suma += e.calificaciones[i];
    return suma / e.numCalificaciones;
}

Nodo* crearNodo(Estudiante e) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return NULL;
    }
    nuevo->est = e;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

Nodo* insertar(Nodo *raiz, Estudiante e) {
    if (raiz == NULL) return crearNodo(e);
    if (e.matricula < raiz->est.matricula)
        raiz->izq = insertar(raiz->izq, e);
    else if (e.matricula > raiz->est.matricula)
        raiz->der = insertar(raiz->der, e);
    return raiz;
}

Nodo* minimo(Nodo *raiz) {
    while (raiz->izq != NULL) raiz = raiz->izq;
    return raiz;
}

Nodo* eliminar(Nodo *raiz, int matricula) {
    if (raiz == NULL) return NULL;
    if (matricula < raiz->est.matricula)
        raiz->izq = eliminar(raiz->izq, matricula);
    else if (matricula > raiz->est.matricula)
        raiz->der = eliminar(raiz->der, matricula);
    else {
        if (raiz->izq == NULL) {
            Nodo *temp = raiz->der;
            free(raiz->est.calificaciones);
            free(raiz);
            return temp;
        } else if (raiz->der == NULL) {
            Nodo *temp = raiz->izq;
            free(raiz->est.calificaciones);
            free(raiz);
            return temp;
        }
        Nodo *temp = minimo(raiz->der);
        raiz->est = temp->est;
        raiz->der = eliminar(raiz->der, temp->est.matricula);
    }
    return raiz;
}

Nodo* buscar(Nodo *raiz, int matricula) {
    if (raiz == NULL || raiz->est.matricula == matricula) return raiz;
    if (matricula < raiz->est.matricula) return buscar(raiz->izq, matricula);
    else return buscar(raiz->der, matricula);
}

void inOrden(Nodo *raiz) {
    if (raiz != NULL) {
        inOrden(raiz->izq);
        printf("%d - %s %s - Promedio: %.2f\n", raiz->est.matricula, raiz->est.nombre, raiz->est.apellido, promedio(raiz->est));
        inOrden(raiz->der);
    }
}

void reportePromedio(Nodo *raiz, Estudiante *arr, int *i) {
    if (raiz != NULL) {
        reportePromedio(raiz->izq, arr, i);
        arr[*i] = raiz->est;
        (*i)++;
        reportePromedio(raiz->der, arr, i);
    }
}

void menoresA70(Nodo *raiz) {
    if (raiz != NULL) {
        menoresA70(raiz->izq);
        if (promedio(raiz->est) < 70)
            printf("%d - %s %s - Promedio: %.2f\n", raiz->est.matricula, raiz->est.nombre, raiz->est.apellido, promedio(raiz->est));
        menoresA70(raiz->der);
    }
}

void mayoresOIgualA70(Nodo *raiz) {
    if (raiz != NULL) {
        mayoresOIgualA70(raiz->izq);
        if (promedio(raiz->est) >= 70)
            printf("%d - %s %s - Promedio: %.2f\n", raiz->est.matricula, raiz->est.nombre, raiz->est.apellido, promedio(raiz->est));
        mayoresOIgualA70(raiz->der);
    }
}

void actualizarCalificacion(Nodo *raiz, int matricula) {
    Nodo *n = buscar(raiz, matricula);
    if (n == NULL) {
        printf("No encontrado.\n");
        return;
    }
    int pos;
    printf("Tiene %d calificaciones:\n", n->est.numCalificaciones);
    for (int i = 0; i < n->est.numCalificaciones; i++)
        printf("%d) %.2f\n", i + 1, n->est.calificaciones[i]);
    printf("Ingrese número de calificación a modificar: ");
    scanf("%d", &pos);
    if (pos < 1 || pos > n->est.numCalificaciones) return;
    printf("Nueva calificación: ");
    scanf("%f", &n->est.calificaciones[pos - 1]);
}

int contarMenores(Nodo *raiz, float cal) {
    if (raiz == NULL) return 0;
    int c = contarMenores(raiz->izq, cal) + contarMenores(raiz->der, cal);
    if (promedio(raiz->est) < cal) c++;
    return c;
}

void mostrarNivel(Nodo *raiz, int nivelActual, int nivelDeseado) {
    if (raiz == NULL) return;
    if (nivelActual == nivelDeseado)
        printf("%d ", raiz->est.matricula);
    else {
        mostrarNivel(raiz->izq, nivelActual + 1, nivelDeseado);
        mostrarNivel(raiz->der, nivelActual + 1, nivelDeseado);
    }
}

void mostrarArbol(Nodo *raiz, int espacio) {
    if (raiz == NULL) {
        return;
    }
    espacio += 10;
    mostrarArbol(raiz->der, espacio);
    printf("\n");
    for (int i = 10; i < espacio; i++) {
        printf(" ");
    }
    printf("%d\n", raiz->est.matricula);
    mostrarArbol(raiz->izq, espacio);
}

int main() {
    Nodo *raiz = NULL;
    int op;
    setlocale(LC_ALL, "es_ES.UTF-8");
    do {
        printf("\n--- MENU ---\n");
        printf("1. Insertar estudiante\n");
        printf("2. Reporte por matrícula\n");
        printf("3. Reporte por promedio\n");
        printf("4. Promedio < 70\n");
        printf("5. Promedio >= 70\n");
        printf("6. Eliminar estudiante\n");
        printf("7. Actualizar calificación\n");
        printf("8. Contar alumnos con promedio menor a uno dado\n");
        printf("9. Mostrar nivel\n");
        printf("10. Mostrar árbol gráfico\n");
        printf("0. Salir\nOpción: ");
        scanf("%d", &op);

        if (op == 1) {
            Estudiante e;
            printf("Matrícula: "); scanf("%d", &e.matricula);
            printf("Nombre: "); scanf("%s", e.nombre);
            printf("Apellido: "); scanf("%s", e.apellido);
            printf("Número de calificaciones: "); scanf("%d", &e.numCalificaciones);
            e.calificaciones = (float*)malloc(e.numCalificaciones * sizeof(float));
            for (int i = 0; i < e.numCalificaciones; i++) {
                printf("Calificación %d: ", i + 1);
                scanf("%f", &e.calificaciones[i]);
            }
            raiz = insertar(raiz, e);
        } 
        else if (op == 2) {
            printf("\n--- Estudiantes ordenados por matrícula ---\n");
            inOrden(raiz);
        } 
        else if (op == 3) {
            Estudiante arr[100];
            int i = 0;
            reportePromedio(raiz, arr, &i);
            for (int x = 0; x < i - 1; x++)
                for (int y = x + 1; y < i; y++)
                    if (promedio(arr[x]) > promedio(arr[y])) {
                        Estudiante temp = arr[x];
                        arr[x] = arr[y];
                        arr[y] = temp;
                    }
            for (int j = 0; j < i; j++)
                printf("%d - %s %s - Promedio: %.2f\n", arr[j].matricula, arr[j].nombre, arr[j].apellido, promedio(arr[j]));
        } 
        else if (op == 4) {
            printf("\n--- Promedios menores a 70 ---\n");
            menoresA70(raiz);
        } 
        else if (op == 5) {
            printf("\n--- Promedios mayores o iguales a 70 ---\n");
            mayoresOIgualA70(raiz);
        } 
        else if (op == 6) {
            int m;
            printf("Matrícula a eliminar: ");
            scanf("%d", &m);
            raiz = eliminar(raiz, m);
        } 
        else if (op == 7) {
            int m;
            printf("Matrícula del estudiante: ");
            scanf("%d", &m);
            actualizarCalificacion(raiz, m);
        } 
        else if (op == 8) {
            int m;
            printf("Matrícula base: ");
            scanf("%d", &m);
            Nodo *n = buscar(raiz, m);
            if (n == NULL) printf("No encontrado.\n");
            else printf("Alumnos con promedio menor: %d\n", contarMenores(raiz, promedio(n->est)));
        } 
        else if (op == 9) {
            int nivel;
            printf("Nivel a mostrar: ");
            scanf("%d", &nivel);
            mostrarNivel(raiz, 0, nivel);
            printf("\n");
        } 
        else if (op == 10) {
            printf("\n--- Árbol Gráfico ASCII (Leer de Izquierda a Derecha) ---\n");
            mostrarArbol(raiz, 0); 
            printf("\n");
        }
    } while (op != 0);
    return 0;
}