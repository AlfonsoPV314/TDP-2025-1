#include <iostream>
#include "Graph.h"

int main(){
    Graph* g = new Graph(9);
    g->addEdge(0, 2);
    g->addEdge(1, 3);
    g->addEdge(1, 5);
    g->addEdge(1, 6);
    g->addEdge(2, 4);
    g->addEdge(2, 7);
    g->addEdge(3, 4);
    g->addEdge(4, 5);
    g->addEdge(4, 6);
    g->addEdge(5, 7);
    g->addEdge(5, 8);
    g->addEdge(6, 7);
    g->addEdge(6, 8);

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