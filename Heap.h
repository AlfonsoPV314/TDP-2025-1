#include <iostream>
#include "State.h"
// se requiere que State disponga de un numero que represente la prioridad
using namespace std;
class Heap {
    public:
        State **heap; // arreglo de punteros a State
        int size; // tamaño del heap maximo
        int top; // ultima posicion despues del ultimo elemento

        // Entradas: tamaño del heap (int)
        // Salidas: Un nuevo Heap (Heap)
        // Descripcion: Constructor de heap que se compone de estados
        Heap(int size);

        // Entradas: estado a añadir (State*)
        // Salidas: void
        // Descripcion: Añade un estado al heap
        void push(State *s);

        // Entradas: nada
        // Salidas: el estado con mayor prioridad del heap (State*)
        // Descripcion: Entrega y remueve del heap al estado con mayor prioridad
        State* pop();

        // Entradas: indice del estado a añadir (int)
        // Salidas: void
        // Descripcion: ordena los estados de segun su prioridad (mayor a menor) luego de un push
        void bubbleUp(int i);

        // Entradas: indice del estado a añadir (int)
        // Salidas: void
        // Descripcion: ordena los estados segun su prioridad (mayor a menor) luego de un pop
        void bubbleDown(int i);

        // Entradas: nada
        // Salidas: void
        // Descripcion: imprime por pantalla el heap de estados
        void printHeap();
};
