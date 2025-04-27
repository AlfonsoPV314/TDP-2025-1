#include <iostream>
#include "Stack.h"
#include "Heap.h"

class RiverCrossing {
    public:
    Heap *open; // Los estado por visitar
    Stack *all; // todos los estados aceptados
    int psgs; // cantidad de pasajeros
    int boatCant;
    int capacidad; // capacidad del barco
    Graph* incompMtrx;  // estatico, podria mejorarse para ser solo int** sin necesidad de List ni Node
    // RiverCrossing(int size); // size es el tamaño de cada repositorio
    RiverCrossing(int size, int psgs, int boatCant, Boat* boats, Graph* incompMtrx); // size es el tamaño de cada repositorio
    ~RiverCrossing();
    State* solve(Boat* boats); // Resuelve el problema retornando el estado solucion
    void addState(State* ns, int combSize); // agrega un nuevo estado a la pila y al heap
    void capacidadCalc(State* s, int combSize); // calcula la capacidad del barco
    void priorityCalc(State* s, int combSize); // calcula la prioridad de un estado
    void combinaciones(State* s, int* arr, int size, int& count); // genera todas las combinaciones de un arreglo
    void combinacion(State* s, int* arr, int* data, int start, int end, int index, int r, int& combIndex); // genera todas las combinaciones de un arreglo
};