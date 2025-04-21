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

bool Graph::isValid(int psg, bool* arr){
    if(psg >= 0){
        arr[psg] = false;
    }
    cout << "[Graph::isValid] calculando que pasa si el psg " << psg << " cruza" << endl;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(M[i][j] == 1 && arr[i] && arr[j]){
                if(psg >= 0){
                    arr[psg] = true;
                }                
                cout << "[Graph::isValid] no se puede cruzar el psg " << psg << endl;
                return false;
            }
        }
    }
    if(psg >= 0){
        arr[psg] = true;
    }
    cout << "[Graph::isValid] se puede cruzar el psg " << psg << endl;
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
