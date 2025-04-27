#include <iostream>
using namespace std;
//NOTA: CAMBIAR GRAFO POR BITMASK EN EL FUTURO

class Graph{
public:
    int** M;    // adjacency matrix
    int V;   // number of vertices
    int E;  // number of edges
    int* incompArr; // array of incompatibilities
    Graph(int v);
    // Graph(int v, bool i[]);   // create a graph from island array
    ~Graph();
    void addEdge(int u, int v);   // add edge to graph
    int* sortByIncomp(int* arr, int size); // sort array by incompatibilities
    bool isEmpty();   // check if graph is empty
    void printGraph();   // print graph
    bool isValid(int* comb, bool* psgs, int capacidad); // check if combination is valid
    Graph* clonePtr();
    Graph* arrSubgraph(int* arr, int size); // create subgraph from array
    int mvc2Approx(Graph* g); // calcula una aproximacion que es al menos 2 veces el valor de la minima covertura de vértices
};