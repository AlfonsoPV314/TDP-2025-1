#include "Graph.h"

Graph::Graph(int v){
    this->V = v;
    E = 0;
    M = new int*[V];
    incompArr = new int[V];
    for(int i = 0; i < V; i++){
        M[i] = new int[V];
        for(int j = 0; j < V; j++){
            M[i][j] = 0;
        }
    }
}

Graph::~Graph(){
    for(int i = 0; i < V; i++){
        delete[] M[i];
    }
    delete[] M;
    delete[] incompArr;
}

void Graph::addEdge(int u, int v){
    if(u < 0 || u >= this->V || v < 0 || v >= this->V){
        return;
    }
    if(M[u][v] == 1 && M[v][u] == 1){
        return;
    }
    M[u][v] = 1;
    M[v][u] = 1;
    incompArr[u]++;
    incompArr[v]++;
    E++;
}

bool Graph::isEmpty(){
    return E == 0;
}

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

bool Graph::isValid(int* comb, bool* arr, int capacidad) {
    // Marcar los pasajeros de la combinación como ausentes temporalmente
    if(comb[0] != -1){
        for (int i = 0; comb[i] != -1; i++) {
            arr[comb[i]] = false;
        }
    }


    // cout << "[Graph::isValid] Verificando combinación: {";
    // for (int i = 0; comb[i] != -1; i++) {
    //     cout << comb[i] << (comb[i + 1] != 0 ? ", " : "");
    // }
    // cout << "}" << endl;

    // Validar si hay conflictos entre los pasajeros restantes
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (M[i][j] == 1 && arr[i] && arr[j]) {
                // Restaurar el estado original antes de salir
                for (int k = 0; comb[k] != -1 && k < capacidad; k++) {
                    arr[comb[k]] = true;
                }
                cout << "[Graph::isValid] Combinación inválida por conflicto entre " << i << " y " << j << endl;
                return false;
            }
        }
    }

    // Restaurar el estado original
    for (int i = 0; comb[i] != -1; i++) {
        arr[comb[i]] = true;
    }

    cout << "[Graph::isValid] Combinación válida" << endl;
    return true;
}




int* Graph::sortByIncomp(int* arr, int size) {
    // Crear un nuevo arreglo dinámico para los elementos ordenados
    int* sortedArr = new int[size];
    for (int i = 0; i < size; i++) {
        sortedArr[i] = arr[i];
    }
    
    // Ordenar usando Bubble Sort
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (incompArr[sortedArr[j] - 1] < incompArr[sortedArr[j + 1] - 1]) {
                // Intercambiar elementos
                int temp = sortedArr[j];
                sortedArr[j] = sortedArr[j + 1];
                sortedArr[j + 1] = temp;
            }
        }
    }

    return sortedArr;
}

Graph* Graph::clonePtr(){
    Graph* g = new Graph(V);
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            g->M[i][j] = M[i][j];
        }
        g->incompArr[i] = incompArr[i];
    }
    return g;
}
