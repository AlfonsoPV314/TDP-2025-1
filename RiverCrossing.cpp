#include "RiverCrossing.h"

RiverCrossing::RiverCrossing(int size) {
//    open = new Stack(size); // se cambio a heap
    psgs = 9;
    capacidad = 0; // capacidad del barco
    incompMtrx = new Graph(9);
    incompMtrx->addEdge(0, 2);
    incompMtrx->addEdge(1, 3);
    incompMtrx->addEdge(1, 5);
    incompMtrx->addEdge(1, 6);
    incompMtrx->addEdge(2, 4);
    incompMtrx->addEdge(2, 7);
    incompMtrx->addEdge(3, 4);
    incompMtrx->addEdge(4, 5);
    incompMtrx->addEdge(4, 6);
    incompMtrx->addEdge(5, 7);
    incompMtrx->addEdge(5, 8);
    incompMtrx->addEdge(6, 7);
    incompMtrx->addEdge(6, 8);
    open = new Heap(size);
    all = new Stack(size);
    boatCant = -1; // cantidad de barcos
}

// RiverCrossing::RiverCrossing(int size, int psgs, int boatCant, Boat* boats, Graph* incompMtrx) {
//     open = new Heap(size);
//     all = new Stack(size);
//     this->psgs = psgs;
//     this->incompMtrx = incompMtrx;
//     this->boatCant = boatCant; // cantidad de barcos
//     this->capacidad = 0;
//     for(int i = 0; i < boatCant; i++) {
//         this->capacidad+=boats[i].capacidad;
//     }
// }

RiverCrossing::~RiverCrossing(){
    delete open;
    delete all;
}

State* RiverCrossing::solve() {
    // paso 1: generar estado inicial e insertar en open
    boatCant = 3; // cantidad de barcos
    capacidad = 0;
    Boat* boats = new Boat[boatCant];
    boats[0].setupBoat(0, 1, 100);
    boats[1].setupBoat(1, 2, 98);
    boats[2].setupBoat(2, 1, 99);
    for(int i = 0; i < boatCant; i++) {
        this->capacidad+=boats[i].capacidad;
    }
    State *init = new State(psgs, boats, capacidad);
    init->setInitialState();
    init->printState(boatCant);
    open->push(init);
    all->push(init);

    // paso 2: mientras open no este vacio
    while (open->top != 0) { // recordar que top es el lugar vacío en el arreglo
        State *s = open->pop();
        cout << "[RiverCrossing::solve] NUEVA ITERACION! :D. Camino actual: " << endl;
        s->printPath();
        cout << endl;

        // paso 3: preguntamos si es la solucion
        if (s->isFinalState()) {
            cout << "[RiverCrossing::solve] Solución encontrada!" << endl;
            return s;
        }

        int combSize = 0;

        int* sidePsgs = s->getPassengers(psgs, combSize);

        
        State* ns = s->crossVoid(sidePsgs, incompMtrx); // Intentar cruzar vacío
        addState(ns, combSize); // Agregar el nuevo estado al heap y stack
        if(s->capacidadActual > 0){
            combinaciones(s, sidePsgs, s->capacidadActual, combSize); // Generar combinaciones
        }

            // cout << "[RiverCrossing::solve] Combinaciones generadas: " << combSize << endl;

            // for (int i = 0; i < combSize; i++) {
                // cout << "[RiverCrossing::solve] Verificando si cruzar con {";
                // for (int j = 0; j < capacidad ; j++) {
                //     cout << combs[i][j] - 1 << " ";
                // }
                // cout << "}" << endl;

                // State *ns = s->cross(combs[i], capacidad, incompMtrx); // Intentar cruzar con esta combinación
                // addState(ns, combSize); // Agregar el nuevo estado al heap y stack

            // }

        cout << "[RiverCrossing::solve] Heap: " << endl;
        open->printHeap();
        cout << endl;

        // Liberar memoria de las combinaciones (problemas en combs[2])
        // for (int i = 0; i < combSize; i++) {
        //     if (combs[i] == nullptr || sizeof(combs[i]) == 0) {
        //         cout << "Error: combs[" << i << "] es nullptr, no se libera." << endl;
        //     } else {
        //         cout << "Liberando combs[" << i << "]." << endl;
        //         // Imprimir la combinación antes de liberar
        //         cout << "Combinación: {";
        //         for (int j = 0; combs[i][j] != -1; j++) {
        //             cout << combs[i][j] << (combs[i][j + 1] != 0 ? ", " : "");
        //         }
        //         cout << "}" << endl;
        //         delete[] combs[i];
        //         combs[i] = nullptr; // Prevenir doble liberación
        //     }
        // }
        
        

    }

    cout << "[RiverCrossing::solve] No se encontró solución." << endl;
    return nullptr; // caso nuestra búsqueda no llegó a solución
}

void RiverCrossing::addState(State* ns, int combSize) {
    if (ns != nullptr) {
        priorityCalc(ns, combSize);
        capacidadCalc(ns, combSize);
        if (!all->find(ns)) {
            cout << "[RiverCrossing::addState] Estado no estaba en stack. Actualizando heap y stack..." << endl;
            ns->printState(boatCant);
            all->push(ns);
            open->push(ns);
        }else{
            cout << "[RiverCrossing::addState] Estado ya estaba en stack. No se agrega." << endl;
        }
    }
}

void RiverCrossing::capacidadCalc(State* s, int combSize) {
    // Se calcula la capacidad del barco como la cantidad de pasajeros en la orilla activa
    int count = 0;
    for (int i = 0; i < boatCant; i++) {
        if (!s->boats[i].isFuelEmpty()) {
            combSize -= s->boats[i].capacidad;
            if(combSize > 0) {
                s->boats[i].updateFuelAmt();
            }
            count += s->boats[i].capacidad;
        }
    }
    s->capacidadActual = count;
}


// NOTA: para capacidad = 3, esto hace 10 fokin combinaciones... o hago caso especial, o cambio heuristica. si usas pasos en vez de all->currentSize, el caso con capacidad 3 es 4 pasos, y el caso con capacidad 1 es 9 pasos en vez de 8. estudiar esta heuristica...
void RiverCrossing::priorityCalc(State* s, int combSize) {
    // Se calcula la prioridad como la cantidad de elementos en la orilla
    // izquierda que no son incompatibles entre si
    s->priority = (s->depth + combSize) * 2;
    for (int i = 0; i < psgs; i++) {
        if (!s->Izq[i]) {
            s->priority++;
        }
    }
}

void RiverCrossing::combinaciones(State* s, int* arr, int size, int& combSize) {
    cout << "[RiverCrossing::combinaciones] INPUT: " << endl;
    cout << "arr: ";
    for (int i = 0; i < combSize; i++) {
        cout << arr[i] << " ";
    }
    cout << "size: " << size << endl;
    cout << "combSize: " << combSize << endl;

    int* arrReal = new int[combSize];
    int idx = 0;
    cout << "[RiverCrossing::combinaciones] arrReal[ ";
    for (int i = 0; i < combSize; i++) {
        if (arr[i] > 0) {
            arrReal[idx++] = arr[i];
            cout << arrReal[idx - 1] << " ";
        }
    }
    cout << "]" << endl;
    int n = combSize; // Actualizar `n` al tamaño real

    // Determinar la cantidad máxima de combinaciones posibles
    int maxCombinations = (1 << n) - 1; // 2^n - 1 combinaciones
    combSize = 0;
    int minSize = 1;
    if(n >= 10) {
        Graph* subGraph = incompMtrx;
        if(s->parent != nullptr){
            subGraph = incompMtrx->arrSubgraph(arrReal, n);
        }
        minSize = subGraph->mvc2Approx(subGraph);
    }
    
    // cout << "[RiverCrossing::combinaciones] minSize: " << minSize << endl;

    // Generar combinaciones desde el tamaño más grande hacia el más pequeño
    for (int r = size; r >= minSize; r--) {
        int* data = new int[r]; // Espacio temporal para una combinación
        combinacion(s, arrReal, data, 0, n - 1, 0, r, combSize);
        delete[] data; // Liberar memoria del temporal
    }

    // Agregar combinación adicional: solo `-1` al principio, seguido de ceros
    // output[combSize] = new int[size](); // Inicializa en ceros
    // output[combSize][0] = -1;          // Establecer el primer elemento en -1
    // combSize++;

    delete[] arrReal; // Liberar memoria de `arrReal`
}

void RiverCrossing::combinacion(State* s, int* arr, int* data, int start, int end, int index, int r, int& combIndex) {
    // Caso base: combinación completa
    if (index == r) {
        cout << "[RiverCrossing::combinacion] Verificando si cruzar con {";
        for (int i = 0; i < r; i++) {
            cout << data[i] - 1 << " ";
        }
        cout << "}" << " capacidad: " << capacidad << endl;

        State *ns = s->cross(data, r, incompMtrx); // Intentar cruzar con esta combinación
        addState(ns, end + 1); // Agregar el nuevo estado al heap y stack
        combIndex++;
        return;
    }

    // Generar combinaciones recursivamente
    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        combinacion(s, arr, data, i + 1, end, index + 1, r, combIndex);
    }
}
