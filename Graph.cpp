#include "Graph.h"

// Entradas: cantidad de vertices (int)
// Salidas: nuevo grafo (Graph)
// Descripcion: Constructor de un grafo
Graph::Graph(int v){
    this->V = v;
    E = 0;
    M = new int*[V];
    for(int i = 0; i < V; i++){
        M[i] = new int[V];
        for(int j = 0; j < V; j++){
            M[i][j] = 0;
        }
    }
}

// Entradas: nada
// Salidas: destruccion de un grafo
// Descripcion: Destructor de un grafo
Graph::~Graph(){
    for(int i = 0; i < V; i++){
        delete[] M[i];
    }
    delete[] M;
}

// Entradas: vertice u (int), vertice v (int)
// Salidas: void
// Descripcion: Funcion que crea una arista entre 2 vertices
void Graph::addEdge(int u, int v){
    if(u < 0 || u >= this->V || v < 0 || v >= this->V){
        return;
    }
    if(M[u][v] == 1 && M[v][u] == 1){
        return;
    }
    M[u][v] = 1;
    M[v][u] = 1;
    E++;
}

// Entradas: nada
// Salidas: si el grafo posee aristas o no (bool)
// Descripcion: Funcion que verifica si hay aristas en el grafo
bool Graph::isEmpty(){
    return E == 0;
}

// Entradas: nada
// Salidas: void
// Descripcion: Funcion que imprime por pantalla un grafo
void Graph::printGraph(){
    cout << "[Graph::printGraph] Imprimiendo la matriz de adyacencia" << endl;
    for(int i = 0; i < V; i++){
        cout << "[ ";
        for(int j = 0; j < V; j++){
            cout << M[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

// Entradas: arreglo de los pasajeros a cruzar (int*), arreglo de la orilla actual (bool*), capacidad de los botes (int)
// Salidas: si se puede o no realizar el cruce (bool)
// Descripcion: Funcion que valida un cruce de pasajeros
bool Graph::isValid(int* comb, bool* arr, int capacidad) {
    // Marcar los pasajeros de la combinación como ausentes temporalmente
    // cout << "[Graph::isValid] capacidad: " << capacidad << endl;
    // cout << "[Graph::isValid] Verificando combinación: {";
    for (int i = 0; i < capacidad; i++) {
        if(comb[i] > -1){
            // cout << comb[i] << " ";
            arr[comb[i]] = false;
        }
    }
    // cout << "}" << endl;

    // Validar si hay conflictos entre los pasajeros restantes
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (M[i][j] == 1 && arr[i] && arr[j]) {
                // Restaurar el estado original antes de salir
                for (int k = 0; k < capacidad; k++) {
                    if(comb[k] > -1){
                        arr[comb[k]] = true;
                    }
                }
                // cout << "[Graph::isValid] Combinación inválida por conflicto entre " << i << " y " << j << endl;
                return false;
            }
        }
    }

    // Restaurar el estado original
    for (int i = 0; i < capacidad; i++) {
        if(comb[i] > -1){
            arr[comb[i]] = true;
        }
    }

    // cout << "[Graph::isValid] Combinación válida" << endl;
    return true;
}

// Entradas: numero de sets que se van a crear (int&)
// Salidas: Arreglo de vectores con los sets de compatibilidad (Vector**)
// Descripcion: Funcion que crea los arreglos de los pasajeros compatibles entre si
Vector** Graph::separateNonAdjacent(int& numSets) {
    // Array to store the color of each vertex (-1 means no color assigned yet)
    int* color = new int[V];
    memset(color, -1, sizeof(int) * V);

    // Boolean array to mark which colors are available for a vertex
    bool* available = new bool[V];

    // Assign colors to vertices
    for (int u = 0; u < V; ++u) {
        // Mark all colors as available
        memset(available, true, sizeof(bool) * V);

        // Mark colors used by adjacent vertices as unavailable
        for (int v = 0; v < this->V; ++v) {
            if (M[u][v] == 1 && color[v] != -1) {
                available[color[v]] = false;
            }
        }

        // Assign the first available color to vertex u
        for (int c = 0; c < this->V; ++c) {
            if (available[c]) {
                color[u] = c;
                break;
            }
        }
    }

    // Find the number of colors used
    numSets = 0;
    for (int i = 0; i < this->V; ++i) {
        if (color[i] + 1 > numSets) {
            numSets = color[i] + 1;
        }
    }

    // Group vertices by their colors
    Vector** result = new Vector*[numSets];
    for (int i = 0; i < numSets; ++i) {
        result[i] = new Vector();
    }

    for (int i = 0; i < this->V; ++i) {
        result[color[i]]->push(i);
    }

    // Clean up
    delete[] color;
    delete[] available;

    return result;
}