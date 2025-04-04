
#include "Heap.h"

Heap::Heap(int size){
    HeapArray = new State*[size];
    MaxSize = size;
    Top = 0;
}

void Heap::push(State* s){
    if(Top == MaxSize){
        cout << "Heap lleno" << endl;
        // se debe volver a generar el arreglo
        State** newHeap = new State* [MaxSize * 2];
        for(int i=0; i<MaxSize; i++){
            newHeap[i] = HeapArray[i];
        }
        delete[] HeapArray; // señor c++, en esta direccion de memoria hay un arreglo. encargate de borrar sus elementos también
        HeapArray = newHeap;
        MaxSize *= 2;
    }
    HeapArray[Top] = s;
    Top++;
    bubbleUp(Top - 1);  // top - 1 es el index del ultimo antes del top (el que antes era el top antes de poner el top)
}

void Heap::bubbleUp(int i){
    if(i != 0){
        int up = (i - 1)/2;
        if(HeapArray[up] < HeapArray[i]){   // en la implementacion del profe son con los punteros y el operador < definido custom
            State* tmp = HeapArray[up]; // guardo el padre
            HeapArray[up] = HeapArray[i];
            HeapArray[i] = tmp;
            bubbleUp(up);
        }
    }
}

State* Heap::pop(){
    if(Top == 0){
        cout << "Heap vacio" << endl;
        return nullptr;
    }

    State* s = HeapArray[0];    // elemento a retornar
    Top--;
    if(Top > 1){    // si hay un top válido
        HeapArray[0] = HeapArray[Top - 1];
        bubbleDown(0);
    }
    Top--;
    return s;
}

void Heap::bubbleDown(int i){
    int left = 2 * i + 1;   // hijo izquierdo en un AVL
    int right = 2 * i + 2;  // hijo derecho en un AVL
    int max = i;
    if(left < Top && HeapArray[max] < HeapArray[left]){
        max = right;
    }else if(right < Top && HeapArray[max] < HeapArray[right]){
        max = right;
    }

    if (max != i){
        State* temp = HeapArray[i]; // guardo el padre
        HeapArray[i] = HeapArray[max];  // guardo el hijo
        HeapArray[max] = temp;  // guardo el padre
        bubbleDown(max);    // sigo bajando
        // si el padre es mayor no se hace nada
    }
}

void Heap::printHeap(){
    cout << "[ ";
    for(int i=0; i<Top; i++){
        cout << i << ": ";
        // HeapArray[i]->printState();
    }
    cout << "]" << endl;
}