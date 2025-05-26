#include "graph.h"
#include <stdlib.h>

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;
    graph->vertices = NULL;
    return graph;
}

void freeGraph(Graph* graph) {
    if (!graph) return;
    
    Vertice* current = graph->vertices;
    while (current != NULL) {
        Vertice* temp = current;
        current = current->next;
        free(temp); // Nota: Los datos (data) deben liberarse externamente
    }
    free(graph);
}

void graph_insertVertex(Graph* graph, int id, void* data) {
    if (!graph || !data) return;
    
    Vertice* newVertice = (Vertice*)malloc(sizeof(Vertice));
    if (!newVertice) return;
    
    newVertice->id = id;
    newVertice->data = data;
    newVertice->next = graph->vertices;
    graph->vertices = newVertice;
}

Vertice* graph_getVertex(Graph* graph, int id) {
    if (!graph) return NULL;
    
    Vertice* current = graph->vertices;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void* getVertexData(Graph* graph, int id) {
    Vertice* vertice = graph_getVertex(graph, id);
    return vertice ? vertice->data : NULL;
}

bool graph_is_empty(Graph* graph) {
    return !graph || graph->vertices == NULL;
}
