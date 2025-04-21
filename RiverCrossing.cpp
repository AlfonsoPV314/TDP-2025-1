#include "RiverCrossing.h"

RiverCrossing::RiverCrossing(int size) {
//    open = new Stack(size); // se cambio a heap
    open = new Heap(size);
    all = new Stack(size);
    pasos = 0;
}

RiverCrossing::~RiverCrossing(){
    delete open;
    delete all;
}

State* RiverCrossing::solve() {
    // paso 1: generar estado inicial e insertar en open
    State *init= new State();
    init->setInitialState();
    init->printState();
    open->push(init);
    all->push(init);

    //paso 2: mientras open no este vacio
    while(open->top!=0) { // recordar que top es el lugar vacío en el arreglo
        State *s = open->pop();
        pasos++;
        cout << "[RiverCrossing::solve] NUEVA ITERACION! :D. Camino actual: " << endl;
        s->printPath();
        cout << endl;
        // paso 3: preguntamos si es la solucion
        if (s->isFinalState()) {
            return s;
        }

        // paso 4: generar todos los estado proximos a s
        State *ns=nullptr;
       
        // se pregunta si se puede realizar la operacion y si no se repite el estado por cada caso
        for(int i = 0; i <= s->psgs; i++) {
            cout << "[RiverCrossing::solve] Verificando si cruzar con " << i << endl;
            cout << "[RiverCrossing::solve] Heap: " << endl;
            open->printHeap();
            ns = s->cross(i);
            if(nullptr != ns){
                priorityCalc(ns);
            }
            if (!all->find(ns) && nullptr != ns) {
                ns->printState();
                all->push(ns);
                open->push(ns);
            }
            cout << endl;
        }
    }
    return nullptr; // caso nuestra busqueda no llego a solucion    
}

void RiverCrossing::priorityCalc(State* s) {
    // Se calcula la prioridad como la cantidad de elementos en la orilla
    // izquierda que no son incompatibles entre si
    s->priority = all->currentSize;
    for (int i = 0; i < 3; i++) {
        if (s->Der[i]) {
            s->priority++;
        }
    }
}

int** RiverCrossing::combinaciones(int* arr, int n, int size, int& combCount) {
    int maxCombinations = (1 << size) - 1; // maximas combinaciones posibles.
    int** output = new int*[maxCombinations];
    for (int i = 0; i < maxCombinations; i++) {
        output[i] = new int[size]();
    }
    combCount = 0;
    for (int r = 1; r <= size; r++) { // generar combinaciones de tamaños 1 hasta "size".
        int* data = new int[r];
        combinacion(output, arr, data, 0, n - 1, 0, r, combCount);
        delete[] data;
    }
    return output;
}

void RiverCrossing::combinacion(int**& output, int* arr, int* data, int start, int end, int index, int r, int& combIndex) {
    if (index == r) {
        for (int i = 0; i < r; i++) {
            output[combIndex][i] = data[i];
        }
        combIndex++;
        return;
    }
    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        combinacion(output, arr, data, i + 1, end, index + 1, r, combIndex);
    }
}