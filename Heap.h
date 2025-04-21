#include <iostream>
#include "State.h"
// se requiere que State disponga de un numero que represente la prioridad
using namespace std;
class Heap {
    public:
        State **heap; // arreglo de punteros a State
        int size; // tamaño del heap maximo
        int top; // ultima posicion despues del ultimo elemento
        Heap(int size);
        void push(State *s);
        State* pop();
        void bubbleUp(int i);
        void bubbleDown(int i);
        void printHeap();
};
