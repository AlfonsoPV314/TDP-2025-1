#include "Heap.h"

// Entradas: tamaño del heap (int)
// Salidas: Un nuevo Heap (Heap)
// Descripcion: Constructor de heap que se compone de estados
Heap::Heap(int size) {
    heap = new State*[size];
    this->size=size;
    top=0;
}

// Entradas: estado a añadir (State*)
// Salidas: void
// Descripcion: Añade un estado al heap
void Heap::push(State *s) {
    if(s == nullptr) {
        cout << "Estado nulo" << endl;
        return;
    }
    if (top == size) {
        //cout << "Heap lleno" << endl;
        // se debe volver a generar el arreglo
        State **newheap = new State*[size*2];
        for (int i=0; i<size; i++) {
            newheap[i] = heap[i];    
        }
        delete[] heap;
        heap = newheap;
        size = size*2;
    }
    heap[top] = s;
    top++;
    bubbleUp(top-1);
}

// Entradas: nada
// Salidas: el estado con mayor prioridad del heap (State*)
// Descripcion: Entrega y remueve del heap al estado con mayor prioridad
State* Heap::pop() {
    if (top == 0) {
        cout << "Heap vacio" << endl;
        return nullptr;
    }
    State *s = heap[0]; // elemnto a retornar

    if (top >1) {
        heap[0] = heap[top-1]; // reemplazo el primer elemento por el ultimo
        bubbleDown(0);
    } 
    top--;
    return s;
}

// Entradas: indice del estado a añadir (int)
// Salidas: void
// Descripcion: ordena los estados de segun su prioridad (mayor a menor) luego de un push
void Heap::bubbleUp(int i) {
    if (i != 0) {
        int up = (i-1)/2;
        if (*heap[up] < *heap[i]) {
            State *tmp = heap[up];
            heap[up] = heap[i];
            heap[i] = tmp;
            bubbleUp(up);
        } 
    }
}

// Entradas: indice del estado a añadir (int)
// Salidas: void
// Descripcion: ordena los estados segun su prioridad (mayor a menor) luego de un pop
void Heap::bubbleDown(int i) {
    int left = 2*i+1;
    int right = 2*i+2;
    int max = i;
    if (left < top // aun sigo dentro del heap 
        && *heap[max] < *heap[left]) { //el  
        max = left;
    } else if (right < top // aun sigo dentro del heap 
        && *heap[max] < *heap[right]) { //el  
        max = right;
    }
    if (max != i) {
        State *tmp= heap[i]; // guardo el padre
        heap[i] = heap[max]; // guardo el hijo
        heap[max] = tmp; // guardo el padre
        bubbleDown(max); // sigo bajando
    } // si el padre es mayor no se hace nada
}

// Entradas: nada
// Salidas: void
// Descripcion: imprime por pantalla el heap de estados
void Heap::printHeap() {
    if(top == 0) {
        cout << "Heap vacio" << endl;
        return;
    }
    for(int i=0; i<top; i++) {
        cout << "[" << i << ": " << heap[i]->operation << ", prioridad: " << heap[i]->priority << "] -> ";
    }
    cout << endl;
}

