#include <iostream>
#include "Stack.h"
#include "Heap.h"

class RiverCrossing {
    public:
    Heap *open; // Los estados por visitar
    Stack *all; // todos los estados aceptados
    int psgs; // cantidad de pasajeros
    int boatCant;  // cantidad de barcos
    int capacidad; // capacidad del barco
    Graph* incompMtrx;  // matriz de incompatibilidades
    Vector** compSets; // vectores de sets de compatibilidad

    // Entradas: tamaño del stack (int), cantidad de pasajeros (int), cantidad de barcos (int), arreglo de barcos (Boat*), matriz de incompatibilidades (Graph*)
    // Salidas: nuevo RiverCrossing (RiverCrossing)
    // Descripcion: Constructor de un RiverCrossing. Inicializa el stack y el heap
    RiverCrossing(int size, int psgs, int boatCant, Boat* boats, Graph* incompMtrx);

    // Entradas: nada
    // Salidas: destruccion del RiverCrossing
    // Descripcion: Destructor de un RiverCrossing. Libera la memoria del stack y el heap
    ~RiverCrossing();

    // Entradas: botes (Boat*)
    // Salidas: estado solucion (State*)
    // Descripcion: Resuelve el problema de cruce de rio. Retorna el estado solucion
    State* solve(Boat* boats);

    // Entradas: estado a añadir (State*), cantidad de pasajeros curzados (int)
    // Salidas: void
    // Descripcion: Añade un nuevo estado al stack y al heap, verificando si es valido y si no se repite, y calcula su prioridad
    void addState(State* ns, int combSize); 

    // Entradas: estado a añadir (State*), cantidad de pasajeros curzados (int)
    // Salidas: void
    // Descripcion: Calcula la capacidad de los barcos para el estado a añadir
    void capacidadCalc(State* s, int combSize);

    // Entradas: estado a añadir (State*), cantidad de pasajeros curzados (int)
    // Salidas: void
    // Descripcion: Calcula la prioridad del estado a añadir
    void priorityCalc(State* s, int combSize); 

    // Entradas: estado a añadir (State*), arreglo de pasajeros (int*), tamaño de las combinaciones (int), cantidad de combinaciones (int&)
    // Salidas: void
    // Descripcion: Inicializa la funcion que genera todas las combinaciones de pasajeros a cruzar y los añade al stack y al heap
    void combinaciones(State* s, int* arr, int size, int& count);

    // Entradas: estado a añadir (State*), arreglo de pasajeros (int*), arreglo de combinaciones (int*), inicio (int), fin (int), indice (int), tamaño de la combinacion (int), indice en la combinacion (int&)
    // Salidas: void
    // Descripcion: Genera todas las combinaciones de pasajeros a cruzar y los añade al stack y al heap
    void combinacion(State* s, int* arr, int* data, int start, int end, int index, int r, int& combIndex);
};