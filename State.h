#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include "Graph.h"
#include "Boat.h"

using namespace std;

#define ZORRO 0
#define CABRA 1
#define REPOLLO 2

// NOTA: muchos de los atributos de la clase son estáticos y por ende repetitivos. podrían estar aparte en otra clase, puesto que al clonarse el estado se malgasta memoria

class State {
    public:
        bool* Izq;
        bool* Der;
        bool isIzq;
        Boat* boats;
        float priority; // prioridad para el heap
        State *parent;
        string operation; 
        int depth;
        State();
        void setInitialState(int psgs, Boat* boats); //
        int* getPassengers(int size, int& count); // retorna un arreglo con los pasajeros en la orilla activa
        //int* sortByIncomp(int* arr, int size); // ordena el arreglo de acuerdo a la cantidad de incompatibilidades
        // operaciones que retornan un nuevo estado 
        State* cross(int* comb, int capacidad, Graph* incompMtrx); // retorna nulo cuando no se puede
        State* crossVoid(int* comb, Graph* incompMtrx); // cruz barco sin item
        bool isFinalState(); // retorna verdadero si el estado es final
        State* clone();
        void printState();
        void printPath(); // imprime recursivamente la secuencia de operaciones
        bool operator==(State s);
        bool operator<(State s);
};

#endif
// STATE_H