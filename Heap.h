#include <iostream>
#include "State.h"

// se requiere un numero que represente la prioridad (heuristica)

class Heap{
    public:
        State** HeapArray; // arreglo de punteros a state
        int MaxSize;   // tamaño max del heap
        int Top;    // ultima posicion después del último elemento
        Heap(int size);
        void push(State* s);
        State* pop();
        void bubbleUp(int i);
        void bubbleDown(int i);
        void printHeap();
};