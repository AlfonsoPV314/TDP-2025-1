#include "Stack.h"

// Entradas: tamaño del stack (int)
// Salidas: Un nuevo Stack (Stack)
// Descripcion: Constructor de stack que se compone de estados
Stack::Stack(int size) {
    arr = new State*[size]; 
    this->size=size;
    top=0;
}

// Entradas: estado a añadir (State*)
// Salidas: void
// Descripcion: Añade un estado al stack
void Stack::push(State* s) {
    if (top==size) { // esta lleno
        cout << "[Stack::push] stack overflow!" << endl;
        return;
    } 
    arr[top]=s;
    top++;
    return;
}

// Entradas: nada
// Salidas: el estado con mayor prioridad del stack (State*)
// Descripcion: Entrega y remueve del stack al estado con mayor prioridad
State* Stack::pop() {
    if (top==0) { // esta vacio
        return nullptr;
    }
    top--;
    return(arr[top]);
}

// Entradas: estado a verificar (State*)
// Salidas: si el estado está en el stack o no (bool)
// Descripcion: Verifica si un estado está en el stack
bool Stack::find(State *s) {
    if (top==0 || nullptr == s) { // esta vacio
        return false;
    } 
    for(int k=0; k<top; k++) {
        if (*s == *arr[k]) {
            return true;
        }
    }
    return false;
}