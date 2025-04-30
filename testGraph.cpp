#include <iostream>
#include "Graph.h"

int main(){
    Graph* g = new Graph(20);
    g->addEdge(0, 10);
    g->addEdge(0, 12);
    g->addEdge(0, 13);
    g->addEdge(1, 10);
    g->addEdge(1, 11);
    g->addEdge(1, 17);
    g->addEdge(2, 10);
    g->addEdge(2, 12);
    g->addEdge(3, 12);
    g->addEdge(3, 13);
    g->addEdge(4, 12);
    g->addEdge(4, 13);
    g->addEdge(5, 11);
    g->addEdge(5, 14);
    g->addEdge(5, 16);
    g->addEdge(6, 14);
    g->addEdge(6, 15);
    g->addEdge(6, 19);
    g->addEdge(7, 14);
    g->addEdge(7, 15);
    g->addEdge(7, 16);
    g->addEdge(7, 17);
    g->addEdge(7, 19);
    g->addEdge(8, 18);
    g->addEdge(9, 13);
    g->addEdge(9, 18);

    std::cout << "Grafo creado!" << std::endl;
    g->printGraph();
    std::cout << "Grafo vacío: " << (g->isEmpty() ? "Sí" : "No") << std::endl;
    std::cout << "Cantidad de vértices: " << g->V << std::endl;
    std::cout << std::endl;

    int numSets;
    Vector** result = g->separateNonAdjacent(numSets);

    std::cout << "Conjuntos no adyacentes:" << std::endl;

    for (int i = 0; i < numSets; ++i) {
        std::cout << "[";
        for (int j = 0; j < result[i]->capacity; ++j) {
            std::cout << result[i]->getPos(j);
            if (j < result[i]->capacity - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    return 0;
}