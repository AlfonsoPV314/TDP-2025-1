#include "Graph.h"

int main(){
    List L(4);
    L.addFirst(3);
    L.addFirst(2);
    L.addFirst(1);
    L.printList();
    L.addLast(5);
    L.addLast(6);
    L.printList();
    Graph G(4);
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 0);
    G.addEdge(0, 2);
    G.printGraph();
}