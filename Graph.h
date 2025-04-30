#include <iostream>
#include <cstring>
#include "Vector.h"
using namespace std;

class Graph{
public:
    int** M;    // grafo de incompatibilidades representado por su matriz de adyacencia
    int V;   // numero de vertices
    int E;  // numero de aristas

    // Entradas: cantidad de vertices (int)
    // Salidas: nuevo grafo (Graph)
    // Descripcion: Constructor de un grafo
    Graph(int v);

    // Entradas: nada
    // Salidas: destruccion de un grafo
    // Descripcion: Destructor de un grafo
    ~Graph();

    // Entradas: vertice u (int), vertice v (int)
    // Salidas: void
    // Descripcion: Funcion que crea una arista entre 2 vertices
    void addEdge(int u, int v);  

    // Entradas: nada
    // Salidas: si el grafo posee aristas o no (bool)
    // Descripcion: Funcion que verifica si hay aristas en el grafo
    bool isEmpty();  

    // Entradas: nada
    // Salidas: void
    // Descripcion: Funcion que imprime por pantalla un grafo
    void printGraph();  

    // Entradas: arreglo de los pasajeros a cruzar (int*), arreglo de la orilla actual (bool*), capacidad de los botes (int)
    // Salidas: si se puede o no realizar el cruce (bool)
    // Descripcion: Funcion que valida un cruce de pasajeros
    bool isValid(int* comb, bool* psgs, int capacidad); 

    // Entradas: numero de sets que se van a crear (int&)
    // Salidas: Arreglo de vectores con los sets de compatibilidad (Vector**)
    // Descripcion: Funcion que crea los arreglos de los pasajeros compatibles entre si
    Vector** separateNonAdjacent(int& numSets); 
};