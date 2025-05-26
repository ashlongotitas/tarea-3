#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <stdbool.h>

typedef struct Vertice {
    void* data;               // Datos genéricos del vértice
    int id;                   // Identificador único
    struct Vertice* next;     // Siguiente vértice en la lista
} Vertice;

typedef struct Graph {
    Vertice* vertices;        // Lista de vértices
} Graph;

// Funciones públicas del TDA Grafo
Graph* createGraph();
void freeGraph(Graph* graph);
void graph_insertVertex(Graph* graph, int id, void* data);
Vertice* graph_getVertex(Graph* graph, int id);
void* getVertexData(Graph* graph, int id);
bool graph_is_empty(Graph* graph);

#endif
