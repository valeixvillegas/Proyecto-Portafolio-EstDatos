#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

typedef struct Movie {
    char *linea;             
    struct Movie* next;
    struct Movie* prev;
} Movie;

typedef struct {
    Movie* head;
    Movie* tail;
} ListaDoble;

void inicializarLista(ListaDoble* lista);
void cargarCSVCompleto(ListaDoble* lista, const char* nombreArchivo);
void mostrarLista(ListaDoble* lista);
void buscarEnLinea(ListaDoble* lista, char* id);
void insertarLinea(ListaDoble* lista);
void eliminarLinea(ListaDoble* lista, char* id);
void actualizarLinea(ListaDoble* lista, char* id);
void liberarLista(ListaDoble* lista);
void obtener_campo_robusto(const char* linea, int num_campo, char* destino, size_t tam_destino);


void inicializarLista(ListaDoble* lista) {
    lista->head = NULL;
    lista->tail = NULL;
}

void cargarCSVCompleto(ListaDoble* lista, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("\nError: no se pudo abrir el archivo %s\n", nombreArchivo);
        return;
    }

    char buffer[4096];

    fgets(buffer, sizeof(buffer), archivo);

    while (fgets(buffer, sizeof(buffer), archivo)) {
        
        bool esLineaValida = false;
        for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
            if (buffer[i] != ',' && buffer[i] != '\r') {
                esLineaValida = true;
                break;
            }
        }

        if (!esLineaValida) {
            continue;
        }

        Movie* nuevo = (Movie*)malloc(sizeof(Movie));
        if (!nuevo) continue;

        nuevo->linea = strdup(buffer);
        nuevo->next = NULL;
        nuevo->prev = lista->tail;

        if (lista->tail) {
            lista->tail->next = nuevo;
        } else {
            lista->head = nuevo;
        }
        lista->tail = nuevo;
    }

    fclose(archivo);
    printf("Archivo '%s' cargado exitosamente.\n", nombreArchivo);
}


void obtener_campo_robusto(const char* linea, int num_campo, char* destino, size_t tam_destino) {
    const char* p = linea;
    int campo_actual = 1;
    bool en_comillas = false;
    char* dest_ptr = destino;
    size_t len = 0;

    
    while (*p && campo_actual < num_campo) {
        if (*p == '"') {
            en_comillas = !en_comillas;
        } else if (*p == ',' && !en_comillas) {
            campo_actual++;
        }
        p++;
    }

    
    en_comillas = false;
    while (*p && len < tam_destino - 1) {
        if (*p == '"') {
            en_comillas = !en_comillas;
        } else if (*p == ',' && !en_comillas) {
            break;
        } else {
            *dest_ptr++ = *p;
            len++;
        }
        p++;
    }
    *dest_ptr = '\0';
    
    
    if (len > 0) {
        if (destino[len-1] == '\n' || destino[len-1] == '\r') {
            destino[len-1] = '\0';
            len--;
            if (len > 0 && (destino[len-1] == '\n' || destino[len-1] == '\r')) {
                destino[len-1] = '\0';
            }
        }
    }
}


void mostrarLista(ListaDoble* lista) {
    if (!lista->head) {
        printf("\nLa lista está vacía.\n");
        return;
    }
    printf("\n--- Listado de Películas (Campos Seleccionados) ---\n");
    Movie* actual = lista->head;
    
    while (actual != NULL) {
        char id[20], title[256], vote_average[20], popularity[20], genres[512];
        
        obtener_campo_robusto(actual->linea, 1, id, sizeof(id));
        obtener_campo_robusto(actual->linea, 2, title, sizeof(title));
        obtener_campo_robusto(actual->linea, 3, vote_average, sizeof(vote_average));
        obtener_campo_robusto(actual->linea, 17, popularity, sizeof(popularity));
        obtener_campo_robusto(actual->linea, 20, genres, sizeof(genres));

        printf("----------------------------------\n");
        printf("ID           : %s\n", id);
        printf("Título       : %s\n", title);
        printf("Puntuación   : %s\n", vote_average);
        printf("Popularidad  : %s\n", popularity);
        genres[strcspn(genres, "\r\n")] = 0;
        printf("Géneros      : %s\n", genres);

        actual = actual->next;
    }
    printf("----------------------------------\n\n");
}


void buscarEnLinea(ListaDoble* lista, char* id_ingresado) {
    if (!lista->head) {
        printf("\nLa lista está vacía.\n");
        return;
    }

    Movie* actual = lista->head;
    int encontrados = 0;
    char id_actual[256];
    
    id_ingresado[strcspn(id_ingresado, "\r\n")] = 0;

    printf("\n--- Resultados de la Búsqueda para ID '%s' ---\n", id_ingresado);

    while (actual != NULL) {
        obtener_campo_robusto(actual->linea, 1, id_actual, sizeof(id_actual));
        
        if (strcmp(id_actual, id_ingresado) == 0) {
            printf("Línea Completa Encontrada:\n%s", actual->linea);
            encontrados++;
            break;
        }
        actual = actual->next;
    }
    if (encontrados == 0) {
        printf("No se encontró ninguna línea con el ID '%s'.\n", id_ingresado);
    }
    printf("--- Fin de la Búsqueda ---\n\n");
}

void insertarLinea(ListaDoble* lista) {
    char buffer[2048];
    printf("Introduce la nueva línea de datos (formato CSV): ");
    fgets(buffer, sizeof(buffer), stdin);

    Movie* nuevo = (Movie*)malloc(sizeof(Movie));
    nuevo->linea = strdup(buffer);
    nuevo->next = NULL;
    nuevo->prev = lista->tail;

    if (lista->tail) {
        lista->tail->next = nuevo;
    } else {
        lista->head = nuevo;
    }
    lista->tail = nuevo;
    printf("Línea insertada correctamente.\n");
}


void eliminarLinea(ListaDoble* lista, char* id_ingresado) {
     if (!lista->head) {
        printf("\nLa lista está vacía.\n");
        return;
    }

    Movie* actual = lista->head;
    Movie* aEliminar = NULL;
    char id_actual[256];
    char confirmacion[5];
    char title[256];
    
    id_ingresado[strcspn(id_ingresado, "\r\n")] = 0;

    while (actual != NULL) {
        obtener_campo_robusto(actual->linea, 1, id_actual, sizeof(id_actual));
        
        if (strcmp(id_actual, id_ingresado) == 0) {
            aEliminar = actual;
            break;
        }
        actual = actual->next;
    }

    if (aEliminar) {
        
        obtener_campo_robusto(aEliminar->linea, 2, title, sizeof(title));
        title[strcspn(title, "\r\n")] = 0; 
        
        printf("\n--- Confirmación de Eliminación ---\n");
        printf("Se encontró la siguiente línea con ID '%s':\n", id_ingresado);
        printf("Título: %s\n", title);
        printf("Línea Completa: %s", aEliminar->linea);
        printf("¿Estás seguro de que deseas eliminar esta línea? (si/no): ");
        
        
        if (fgets(confirmacion, sizeof(confirmacion), stdin) != NULL) {
            confirmacion[strcspn(confirmacion, "\r\n")] = 0;
            
            
            if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "SI") == 0) {
                
                if (aEliminar->prev) {
                    aEliminar->prev->next = aEliminar->next;
                } else {
                    lista->head = aEliminar->next;
                }
                if (aEliminar->next) {
                    aEliminar->next->prev = aEliminar->prev;
                } else {
                    lista->tail = aEliminar->prev;
                }
                free(aEliminar->linea);
                free(aEliminar);
                printf("Línea con ID '%s' ha sido eliminada.\n", id_ingresado);
            } else {
                printf("Eliminación cancelada por el usuario.\n");
            }
        } else {
            printf("Error al leer la confirmación. Eliminación cancelada.\n");
        }
        printf("--- Fin de la Confirmación ---\n");
    } else {
        printf("No se encontró ninguna línea con ID '%s'.\n", id_ingresado);
    }
}


void actualizarLinea(ListaDoble* lista, char* id_ingresado) {
    if (!lista->head) {
        printf("\nLa lista está vacía.\n");
        return;
    }

    Movie* actual = lista->head;
    char id_actual[256];

    id_ingresado[strcspn(id_ingresado, "\r\n")] = 0;
    
    while(actual != NULL) {
        obtener_campo_robusto(actual->linea, 1, id_actual, sizeof(id_actual));

        if (strcmp(id_actual, id_ingresado) == 0) {
            
            #define MAX_FIELDS 25       
            #define FIELD_SIZE 1024     
            char campos_originales[MAX_FIELDS][FIELD_SIZE];
            int i;
            int campo_a_modificar;
            char nuevo_valor[FIELD_SIZE];
            char nueva_linea[4096 * 2] = ""; 
            
            
            const int IDX_TITULO = 2;
            const int IDX_PUNTUACION = 3;
            const int IDX_POPULARIDAD = 17;
            const int IDX_GENEROS = 20;
            
            
            
            int num_campos_existentes = 0;
            int limite_extraccion = IDX_GENEROS > MAX_FIELDS ? MAX_FIELDS : IDX_GENEROS; 

            for (i = 1; i <= limite_extraccion; i++) {
                obtener_campo_robusto(actual->linea, i, campos_originales[i - 1], FIELD_SIZE);
                num_campos_existentes = i; 
            }
            
            
            if (num_campos_existentes < MAX_FIELDS) {
                 obtener_campo_robusto(actual->linea, num_campos_existentes + 1, campos_originales[num_campos_existentes], FIELD_SIZE);
                 if (campos_originales[num_campos_existentes][0] != '\0') {
                    
                    num_campos_existentes++;
                 }
            }


            
            
            
            const char* popularidad_actual = campos_originales[IDX_POPULARIDAD - 1][0] != '\0' ? campos_originales[IDX_POPULARIDAD - 1] : "N/D";
            const char* generos_actual = campos_originales[IDX_GENEROS - 1][0] != '\0' ? campos_originales[IDX_GENEROS - 1] : "N/D";
            
            printf("\nLínea encontrada para el ID %s:\n", id_ingresado);
            printf("----------------------------------\n");
            printf("1. Título       (Actual: %s)\n", campos_originales[IDX_TITULO - 1]);
            printf("2. Puntuación   (Actual: %s)\n", campos_originales[IDX_PUNTUACION - 1]);
            printf("3. Popularidad  (Actual: %s)\n", popularidad_actual);
            printf("4. Géneros      (Actual: %s)\n", generos_actual); 
            printf("0. Cancelar\n");
            printf("Opción a modificar: ");
            
            if (scanf("%d", &campo_a_modificar) != 1) {
                printf("Opción no válida. Cancelando actualización.\n");
                while (getchar() != '\n' && !feof(stdin)); 
                return;
            }
            getchar(); 
            
            
            int indice_csv = -1;
            switch(campo_a_modificar) {
                case 1: indice_csv = IDX_TITULO; break;
                case 2: indice_csv = IDX_PUNTUACION; break;
                case 3: indice_csv = IDX_POPULARIDAD; break;
                case 4: indice_csv = IDX_GENEROS; break;
                case 0: printf("Actualización cancelada.\n"); return;
                default: printf("Opción no válida. Actualización cancelada.\n"); return;
            }

            
            printf("Introduzca el nuevo valor para el campo: ");
            
            if (fgets(nuevo_valor, FIELD_SIZE, stdin) == NULL) {
                printf("Error al leer el nuevo valor. Actualización cancelada.\n");
                return;
            }
            
            nuevo_valor[strcspn(nuevo_valor, "\r\n")] = 0;
            
            
            
            strncpy(campos_originales[indice_csv - 1], nuevo_valor, FIELD_SIZE - 1);
            campos_originales[indice_csv - 1][FIELD_SIZE - 1] = '\0';

            
            for (i = 0; i < num_campos_existentes; i++) {
                
                
                
                
                bool necesita_comillas = (strchr(campos_originales[i], ',') != NULL);
                
                if (necesita_comillas) {
                    strcat(nueva_linea, "\"");
                }

                
                strcat(nueva_linea, campos_originales[i]);
                
                if (necesita_comillas) {
                    strcat(nueva_linea, "\"");
                }
                
                
                if (i < num_campos_existentes - 1) {
                    strcat(nueva_linea, ",");
                }
            }
            
        
            strcat(nueva_linea, "\n");
            
            
            free(actual->linea);
            actual->linea = strdup(nueva_linea);
            
            printf("Línea con ID '%s' actualizada correctamente. Nuevo valor guardado.\n", id_ingresado);
            return;
        }
        actual = actual->next;
    }
    printf("No se encontró ninguna línea con ID '%s'.\n", id_ingresado);
}


void liberarLista(ListaDoble* lista) {
    Movie* actual = lista->head;
    while (actual != NULL) {
        Movie* siguiente = actual->next;
        free(actual->linea);
        free(actual);
        actual = siguiente;
    }
    lista->head = NULL;
    lista->tail = NULL;
}


int main() {
    ListaDoble lista;
    char texto[256];
    int opcion = -1;
    setlocale(LC_ALL, "es_ES.UTF-8");

    inicializarLista(&lista);
    cargarCSVCompleto(&lista, "Movies.csv");

    do {
        printf("\n--- MENÚ ---\n");
        printf("1. Mostrar lista de películas (resumen)\n");
        printf("2. Buscar línea (por ID)\n");
        printf("3. Insertar línea\n");
        printf("4. Eliminar línea (por ID)\n"); 
        printf("5. Actualizar línea (por ID)\n"); 
        printf("0. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                mostrarLista(&lista);
                break;
            case 2:
                printf("ID de la línea a buscar: ");
                fgets(texto, sizeof(texto), stdin);
                buscarEnLinea(&lista, texto);
                break;
            case 3:
                insertarLinea(&lista);
                break;
            case 4:
                printf("ID de la línea a eliminar: ");
                fgets(texto, sizeof(texto), stdin);
                eliminarLinea(&lista, texto);
                break;
            case 5:
                printf("ID de la línea a actualizar: ");
                fgets(texto, sizeof(texto), stdin);
                actualizarLinea(&lista, texto);
                break;
            case 0:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpción no válida. Inténtalo de nuevo.\n");
        }
    } while (opcion != 0);

    liberarLista(&lista);
    return 0;
}