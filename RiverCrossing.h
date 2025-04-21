#include <iostream>
#include "Stack.h"
#include "Heap.h"

class RiverCrossing {
    public:
    Heap *open; // Los estado por visitar
    Stack *all; // todos los estados aceptados
    int pasos;
    RiverCrossing(int size); // size es el tamaño de cada repositorio
    ~RiverCrossing();
    State* solve(); // Resuelve el problema retornando el estado solucion
    void priorityCalc(State* s); // calcula la prioridad de un estado
    int** combinaciones(int* arr, int max, int size, int& count); // genera todas las combinaciones de un arreglo
    void combinacion(int**& output, int* arr, int* data, int start, int end, int index, int r, int& combIndex); // genera todas las combinaciones de un arreglo
};