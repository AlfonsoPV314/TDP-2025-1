#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include "Graph.h"
#include "Boat.h"

using namespace std;

class State {
    public:
        bool* Izq;  // pasajeros en la izquierda
        bool* Der;  // pasajeros en la derecha
        bool isIzq; // lado en el que está
        Boat* boats;    // arreglo de barcos
        int cantBotes;  // cantidad de barcos
        float priority; // prioridad para el heap
        State *parent;  // estado padre
        string operation;   // operacion hecha en el estado
        int depth;  // cantidad de estados anteriores
        int psgs;   // cantidad de pasajeros
        int capacidadActual;    // capacidad actual de los barcos

        // Entradas: numero de psajeros (int), arreglo de botes (Boat*), cantidad de botes (int), capacidad actual de los botes (int)
        // Salidas: Estado nuevo (State)
        // Descripcion: Constructor de un estado.
        State(int psgs, Boat* boats, int cantBotes, int capacidad);

        // Entradas: nada
        // Salidas: void
        // Descripcion: Inicializa el estado y sus atributos asumiendo que es el estado inicial.
        void setInitialState(); 

        // Entradas: tamaño del arreglo inicial (int), tamaño del arreglo con la cantidad de pasajeros (int&)
        // Salidas: retorna un arreglo con los pasajeros en la orilla activa (int*)
        // Descripcion: obtiene los pasajeros presentes en la orilla en la cual se está actualmente
        int* getPassengers(int size, int& count); 
        
        // Entradas: pasajeros a cruzar (int*), cantidad de pasajeros que cruzan (int), grafo de incompatibilidades
        // Salidas: estado con los pasajeros a cruzar en la otra orilla (State*)
        // Descripcion: Realiza un cruce de pasajeros en un estado, verificando su validez
        State* cross(int* comb, int capacidad, Graph* incompMtrx); // retorna nulo cuando no se puede

        // Entradas: pasajeros a cruzar (int*) (auxiliar), grafico de incompatibilidades (Graph*)
        // Salidas: estado con los botes en la otra orilla (State*)
        // Descripcion: Realiza un cruce sin ningun pasajero en un estado, verificando su validez
        State* crossVoid(int* comb, Graph* incompMtrx); // cruz barco sin item

        // Entradas: nada
        // Salidas: si es el estado final o no (bool)
        // Descripcion: verifica si el estado es el estado final
        bool isFinalState(); // retorna verdadero si el estado es final

        // Entradas: nada
        // Salidas: estado clonado (State*)
        // Descripcion: Clona el estado
        State* clone();

        // Entradas: nada
        // Salidas: void
        // Descripcion: Imprime el estado por pantalla
        void printState();

        // Entradas: nada
        // Salidas: void
        // Descripcion: Imprime por pantalla el camino de los estados
        void printPath(); // imprime recursivamente la secuencia de operaciones

        // Entradas: estado a verificar (State)
        // Salidas: si son iguales o no (bool)
        // Descripcion: Verifica si 2 estados son iguales
        bool operator==(State s);

        // Entradas: estado a verificar (State)
        // Salidas: si el estado es menor a aquel que se compara o no (bool)
        // Descripcion: Verifica si el estado es menor que un estado a comparar
        bool operator<(State s);
};

#endif
// STATE_H