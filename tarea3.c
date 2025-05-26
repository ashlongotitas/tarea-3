#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/graph.h"
#include "tdas/extra.h"
#include <string.h>

// Definición de estructuras de datos

// Estructura para representar items del juego
typedef struct {
    char nombre[50];   // Nombre del item
    int peso;          // Peso del item (afecta movimiento)
    int valor;         // Valor/puntos del item
} Item;

// Estructura para direcciones disponibles
typedef struct{
    int arriba;        // ID escenario arriba (-1 si no hay)
    int abajo;         // ID escenario abajo (-1 si no hay)
    int izquierda;     // ID escenario izquierda (-1 si no hay)
    int derecha;      // ID escenario derecha (-1 si no hay)
} Direccion;

// Estructura principal para los escenarios del juego
typedef struct{
    int id;                   // ID único del escenario
    char nombre[100];         // Nombre del escenario
    char descripcion[200];    // Descripción del escenario
    Direccion decisiones;     // Conexiones a otros escenarios
    List* items;             // Lista de items disponibles en este escenario
    bool esFinal;            // Indica si es un escenario final
} Escenario;

// Función que muestra el menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("==========================");
  puts("     GRAPH QUEST ");
  puts("==========================");
  puts("1) Leer escenarios");
  puts("2) Iniciar partida");
  puts("3) Salir");
}

// Función para cargar los escenarios desde un archivo CSV
void leer_escenarios(Graph* grafo) 
{
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/graphquest.csv", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea un nuevo escenario
    Escenario* escenario = (Escenario*)malloc(sizeof(Escenario));
    if (escenario == NULL) {
        perror("Error al asignar memoria para el escenario");
        fclose(archivo);
        return;
    }
    // Asigna los valores del CSV a los campos del escenario
    escenario->id = atoi(campos[0]);
    strncpy(escenario->nombre, campos[1], sizeof(escenario->nombre) - 1);
    escenario->nombre[sizeof(escenario->nombre) - 1] = '\0'; // Asegura null-terminación
    strncpy(escenario->descripcion, campos[2], sizeof(escenario->descripcion) - 1);
    escenario->descripcion[sizeof(escenario->descripcion) - 1] = '\0'; // Asegura null-terminación

    escenario->items = list_create();
    if (strlen(campos[3]) > 0) 
    { // Solo procesar si hay items
            List* items = split_string(campos[3], ";");
            
            for(char *item = list_first(items); item != NULL; item = list_next(items)) 
            {
                List* values = split_string(item, ",");
                char* item_name = list_first(values);
                char* peso_str = list_next(values);
                char* valor_str = list_next(values);

                if (item_name && valor_str && peso_str) 
                {
                    Item* nuevo_item = malloc(sizeof(Item));
                    strncpy(nuevo_item->nombre, item_name, 50);
                    nuevo_item->peso = atoi(peso_str);
                    nuevo_item->valor = atoi(valor_str);
                    list_pushBack(escenario->items, nuevo_item);
                }
                list_clean(values);
                free(values);
            }
            list_clean(items);
            free(items);
    }
    escenario->decisiones.arriba = atoi(campos[4]);
    escenario->decisiones.abajo = atoi(campos[5]);
    escenario->decisiones.izquierda = atoi(campos[6]);
    escenario->decisiones.derecha = atoi(campos[7]);
    if (strcasecmp(campos[8], "Si") == 0) 
    {
        escenario->esFinal = true;
    } 
    else 
    {
    escenario->esFinal = false;
    }

    // Inserta el escenario en el grafo
    graph_insertVertex(grafo, escenario->id, escenario);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas
  printf("Escenarios leidos correctamente.\n");
}

// Función para mostrar el estado actual del juego
void mostrar_estado(Escenario* actual, List* inventario, int puntaje, int peso_actual, int tiempo) {
    limpiarPantalla();
    puts("==================================");
    puts("          ESTADO ACTUAL");
    puts("==================================");
    printf("Ubicacion: %s\n", actual->nombre);
    printf("Descripcion: %s\n\n", actual->descripcion);

    // Mostrar items disponibles
    puts("Items disponibles en este escenario:");
    if (list_isEmpty(actual->items)) {
        puts(" - No hay items aqui");
    } else {
        Item* item = list_first(actual->items);
        int i = 0;
        while (item) {
            printf("  %d) %s (Valor: %d, Peso: %d kg)\n", i++, item->nombre, item->valor, item->peso);
            item = list_next(actual->items);
        }
    }

    // Mostrar inventario
    printf("\nInventario (Peso: %d, Puntos: %d):\n", peso_actual, puntaje);
    if (list_isEmpty(inventario)) 
    {
        puts("  - Inventario vacio");
    } 
    else 
    {
        Item* inv_item = list_first(inventario);
        while (inv_item) {
            printf("  - %s (Valor: %d, Peso: %d)\n", inv_item->nombre, inv_item->valor, inv_item->peso);
            inv_item = list_next(inventario);
        }
    }

    // Mostrar tiempo y direcciones
    printf("\nTiempo restante: %d", tiempo);
    puts("\nDirecciones disponibles:");
    if (actual->decisiones.arriba != -1) puts("1. Arriba ");
    if (actual->decisiones.abajo != -1) puts("2. Abajo");
    if (actual->decisiones.izquierda != -1) puts("3. Izquierda");
    if (actual->decisiones.derecha != -1) puts("4. Derecha ");
}

// Función principal del juego
void iniciar_partida(Graph* grafo) 
{
    List* inventario = list_create();  // Inventario del jugador
    int puntaje = 0, peso_actual = 0, tiempo = 15;  // Estadísticas del jugador
    int escenario_actual = 1; // Comenzar en el escenario 1 (Entrada)

    Escenario* actual = (Escenario*)getVertexData(grafo, escenario_actual);
    if (!actual) {
        puts("No hay escenarios cargados. Por favor, cargue los escenarios primero.");
        return;
    }

    printf("Iniciando partida en el escenario: %s\n", actual->nombre);
    printf("Descripcion: %s\n", actual->descripcion);

    // Bucle principal del juego
    while (tiempo > 0 && !actual->esFinal) {

        printf("\nOpciones:\n");
        printf("1) Recoger item\n");
        printf("2) Descartar item\n");
        printf("3) Moverse\n");
        printf("4) Reiniciar\n");
        printf("5) Salir\n");
        printf("Seleccione: ");

        char opcion;
        scanf(" %c", &opcion);
        getchar();

        switch(opcion) {
            case '1': { // Recoger item
                if (list_isEmpty(actual->items)) {
                    puts("No hay items para recoger aqui");
                    break;
                }

                printf("\nItems disponibles:\n");
                Item* item = list_first(actual->items);
                int i = 0;
                while (item) {
                    printf("%d) %s (Valor: %d, Peso: %d)\n", i++, item->nombre, item->valor, item->peso);
                    item = list_next(actual->items);
                }

                printf("Seleccione item (0-%d): ", i-1);
                int seleccion;
                scanf("%d", &seleccion);
                getchar();

                item = list_get(actual->items, seleccion);
                if (!item) {
                    puts("Seleccion invalida");
                    break;
                }

                list_pushBack(inventario, item);
                list_remove(actual->items, seleccion);
                puntaje += item->valor;
                peso_actual += item->peso;
                tiempo--;
                printf("Recogiste: %s\n", item->nombre);
                mostrar_estado(actual, inventario, puntaje, peso_actual, tiempo);
                break;
            }
            case '2': { // Descartar item
                if (list_isEmpty(inventario)) {
                    puts("No tienes items para descartar");
                    break;
                }

                printf("Tus items:\n");
                Item* item = list_first(inventario);
                int i = 0;
                while (item) {
                    printf("%d) %s (Valor: %d puntos, Peso: %d)\n", i++, item->nombre, item->valor, item->peso);
                    item = list_next(inventario);
                }

                printf("Seleccione item (0-%d): ", i-1);
                int seleccion;
                scanf("%d", &seleccion);
                getchar();

                item = list_get(inventario, seleccion);
                if (!item) {
                    puts("Seleccion inválida");
                    break;
                }

                list_pushBack(actual->items, item);
                list_remove(inventario, seleccion);
                puntaje -= item->valor;
                peso_actual -= item->peso;
                tiempo--;
                printf("Descartaste: %s\n", item->nombre);
                mostrar_estado(actual, inventario, puntaje, peso_actual, tiempo);
                break;
            }
            case '3': { // Moverse
                printf("\nDirecciones disponibles:\n");
                if (actual->decisiones.arriba != -1) printf("1) Arriba\n");
                if (actual->decisiones.abajo != -1) printf("2) Abajo\n");
                if (actual->decisiones.izquierda != -1) printf("3) Izquierda\n");
                if (actual->decisiones.derecha != -1) printf("4) Derecha\n");

                printf("Seleccione direccion: ");
                char dir;
                scanf(" %c", &dir);
                getchar();

                int nuevo_id = -1;
                switch(dir) 
                {
                    case '1': nuevo_id = actual->decisiones.arriba; break;
                    case '2': nuevo_id = actual->decisiones.abajo; break;
                    case '3': nuevo_id = actual->decisiones.izquierda; break;
                    case '4': nuevo_id = actual->decisiones.derecha; break;
                    default: puts("Direccion invalida"); break;
                }

                if (nuevo_id == -1 && (dir >= '1' && dir <= '4')) 
                {
                    puts("\nDireccion no disponible en este escenario");
                }

                if (nuevo_id != -1) {
                    int costo = (peso_actual + 10) / 10; // ceil(peso/10)
                    if (tiempo - costo <= 0) {
                        puts("No tienes suficiente tiempo para moverte");
                        tiempo = 0;
                        break;
                    }

                    tiempo -= costo;
                    actual = (Escenario*)getVertexData(grafo, nuevo_id);
                    printf("Te moviste a: %s\n", actual->nombre);   
                    presioneTeclaParaContinuar();

                    if (actual->esFinal) {
                        puts("\nFelicidades, Has llegado al final del laberinto");
                        printf("Puntaje final: %d\n", puntaje);
                        list_clean(inventario);
                        free(inventario);
                        return;
                    }
                    mostrar_estado(actual, inventario, puntaje, peso_actual, tiempo);
                }
                break;
            }
            case '4': // Reiniciar
                while (!list_isEmpty(inventario)) {
                    Item* item = list_popFront(inventario);
                    list_pushBack(actual->items, item);
                }
                puntaje = 0;
                peso_actual = 0;
                tiempo = 15;
                escenario_actual = 1;
                actual = (Escenario*)getVertexData(grafo, escenario_actual);
                puts("Partida reiniciada");
                break;
            case '5': // Salir
                puts("Saliendo del juego...");
                list_clean(inventario);
                free(inventario);
                return;
            default:
                puts("Opcion no valida");
                break;
        }

        if (tiempo <= 0) {
            puts("\nSe te acabo el tiempo, Game Over");
            printf("Puntaje final: %d\n", puntaje);
        }
        presioneTeclaParaContinuar();
        limpiarPantalla(); 
    }

    list_clean(inventario);
    free(inventario);
}

// Función principal del programa
int main() {
    Graph* grafo = createGraph();  // Crea el grafo que contendrá los escenarios
    char opcion;

    // Bucle del menú principal
    do {
        mostrarMenuPrincipal();
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);
        getchar(); 

        switch(opcion) {
            case '1':
                leer_escenarios(grafo);  // Carga los escenarios desde el archivo
                break;
            case '2':
                iniciar_partida(grafo);  // Inicia una nueva partida
                break;
            case '3':
                puts("Saliendo...");
                break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();
    } while (opcion != '4');

    return 0;
}
