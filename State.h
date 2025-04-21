#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

#define ZORRO 0
#define CABRA 1
#define REPOLLO 2

class State {
    public:
        int psgs;
        bool Izq[3];
        bool Der[3];
        bool isIzq;
        Graph* incompMtrx;
        float priority; // prioridad para el heap
        State *parent;
        string operation; 
        State();
        void setInitialState(); //
        // operaciones que retornan un nuevo estado 
        State* cross(int psg); // retorna nulo cuando no se puede
        State* crossVoid(); // cruz barco sin item
        bool isFinalState(); // retorna verdadero si el estado es final
        State* clone();
        void printState();
        void printPath(); // imprime recursivamente la secuencia de operaciones
        bool operator==(State s);
        bool operator<(State s);
};

#endif
// STATE_H