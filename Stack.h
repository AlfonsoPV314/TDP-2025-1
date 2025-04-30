#include<iostream>
#include "State.h"


using namespace std;

class Stack {
    public:
    State **arr;    // arreglo de estados del stack
    int size;   // tamaño del stack
    int top;    // posicion del siguiente elemento a añadir

    // Entradas: tamaño del stack (int)
    // Salidas: Un nuevo Stack (Stack)
    // Descripcion: Constructor de stack que se compone de estados
    Stack(int size);

    // Entradas: estado a añadir (State*)
    // Salidas: void
    // Descripcion: Añade un estado al stack
    void push(State* s);

    // Entradas: nada
    // Salidas: el estado con mayor prioridad del stack (State*)
    // Descripcion: Entrega y remueve del stack al estado con mayor prioridad
    State* pop();

    // Entradas: estado a verificar (State*)
    // Salidas: si el estado está en el stack o no (bool)
    // Descripcion: Verifica si un estado está en el stack
    bool find(State* s);
};