#include <iostream>
#include "Graph.h"

int main(){
    Graph* g = new Graph(5);
    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(2, 4);
    g->addEdge(3, 4);

    std::cout << "Graph created with edges." << std::endl;
    g->printGraph();

    return 0;
}