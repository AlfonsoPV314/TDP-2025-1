#include "List.h"

class Graph{
public:
    int** M;    // adjacency matrix
    int V;   // number of vertices
    int E;  // number of edges
    Graph(int v);
    Graph(int v, List** l);   // create a graph from list of edges
    // Graph(int v, bool i[]);   // create a graph from island array
    ~Graph();
    void addEdge(int u, int v);   // add edge to graph
    bool isEmpty();   // check if graph is empty
    void printGraph();   // print graph
    bool isValid(int psg, bool* psgs);
    Graph* clonePtr();
};