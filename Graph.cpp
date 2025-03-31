#include "Graph.h"

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

Graph::Graph(int v, List** l){
    this->V = v;
    E = 0;
    M = new int*[V];
    for(int i = 0; i < V; i++){
        M[i] = new int[V];
        for(int j = 0; j < V; j++){
            M[i][j] = 0;
        }
    }

    for(int i = 0; i < (*l)->Len; i++){
        int u = (*l)[i].get(0);
        int v = (*l)[i].get(1);
        M[u][v] = 1;
        M[v][u] = 1;
        E++;
    }
}

Graph::~Graph(){
    for(int i = 0; i < V; i++){
        delete[] M[i];
    }
    delete[] M;
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
    E++;
}

void Graph::removeEdge(int u, int v){
    if(u < 0 || u >= this->V || v < 0 || v >= this->V){
        return;
    }
    M[u][v] = 0;
    M[v][u] = 0;
    E--;
}

List* Graph::getNeighbors(int v){
    if(v < 0 || v >= this->V){
        return nullptr;
    }
    List* neighbors = new List();
    for(int i = 0; i < V; i++){
        if(M[v][i] == 1){
            neighbors->addLast(i);
        }
    }
    return neighbors;
}

List* Graph::getNodes(){
    List* nodes = new List();
    for(int i = 0; i < V; i++){
        nodes->addLast(i);
    }
    return nodes;
}

bool Graph::isEmpty(){
    return E == 0;
}

void Graph::printGraph(){
    for(int i = 0; i < V; i++){
        cout << "[ ";
        for(int j = 0; j < V; j++){
            cout << M[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

bool Graph::isDominatingSet(bool currentSet[], int size){
    for(int i = 0; i < V; i++){
        if(currentSet[i] == false){
            bool isDominated = false;
            for(int j = 0; j < V; j++){
                if(M[i][j] == 1 && currentSet[j] == true){
                    isDominated = true;
                    break;
                }
            }
            if(!isDominated){
                return false;
            }
        }
    }
    return true;
}

void Graph::findAllMDS(bool currentSet[], int currentSetSize, bool bestSet[], int& bestSize, int pos, bool includedNodes[], int minSetSize){
    if(currentSetSize > V){
        return;
    }
    if(pos == V){
        if(currentSetSize == minSetSize && isDominatingSet(currentSet, V)){
            if(currentSetSize < bestSize){
                bestSize = currentSetSize;
                for(int i = 0; i < V; i++){
                    bestSet[i] = currentSet[i];
                }
            }
        }
        return;
    }

    // include the node
    currentSet[pos] = true;

    findAllMDS(currentSet, currentSetSize + 1, bestSet, bestSize, pos + 1, includedNodes, minSetSize);

    // exclude the node
    currentSet[pos] = false;
    findAllMDS(currentSet, currentSetSize, bestSet, bestSize, pos + 1, includedNodes, minSetSize);
}