#include "Heap.h"

Heap::Heap(int size) {
    heap = new State*[size];
    this->size=size;
    top=0;
}

void Heap::push(State *s) {
    cout << "top: " << top << endl;
    if (top == size) {
        cout << "Heap lleno" << endl;
        // se debe volver a generar el arreglo
        State **newheap = new State*[size*2];
        for (int i=0; i<size; i++) {
            newheap[i] = heap[i];    
        }
        delete[] heap;
        heap = newheap;
        size = size*2;
    }
    cout << "flag1" << endl;
    heap[top] = s;
    cout << "flag21" << endl;
    top++;
    cout << "top: " << top << " top - 1: " << top-1 << endl;
    bubbleUp(top-1);
}

void Heap::bubbleUp(int i) {
    if (i != 0) {
        int up = (i-1)/2;
        cout << up << " " << i << endl;
        heap[0]->printState(1);
        if (*heap[up] < *heap[i]) {
            State *tmp = heap[up];
            heap[up] = heap[i];
            heap[i] = tmp;
            bubbleUp(up);
        } 
        cout << "glag" << endl;
    }
}


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

