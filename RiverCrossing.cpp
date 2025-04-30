#include "RiverCrossing.h"

// Entradas: tamaño del stack (int), cantidad de pasajeros (int), cantidad de barcos (int), arreglo de barcos (Boat*), matriz de incompatibilidades (Graph*)
// Salidas: nuevo RiverCrossing (RiverCrossing)
// Descripcion: Constructor de un RiverCrossing. Inicializa el stack y el heap
RiverCrossing::RiverCrossing(int size, int psgs, int boatCant, Boat* boats, Graph* incompMtrx) {
    open = new Heap(size);
    all = new Stack(size);
    this->psgs = psgs;
    this->incompMtrx = incompMtrx;
    this->boatCant = boatCant; // cantidad de barcos
    this->capacidad = 0;
    for(int i = 0; i < boatCant; i++) {
        this->capacidad+=boats[i].capacidad;
    }
    compSets = nullptr;
}

// Entradas: nada
// Salidas: destruccion del RiverCrossing
// Descripcion: Destructor de un RiverCrossing. Libera la memoria del stack y el heap
RiverCrossing::~RiverCrossing(){
    delete open;
    delete all;
}

// Entradas: estado a añadir (State*), cantidad de pasajeros curzados (int)
// Salidas: estado solucion (State*)
// Descripcion: Resuelve el problema de cruce de rio. Retorna el estado solucion
State* RiverCrossing::solve(Boat* boats) {
    // paso 1: generar estado inicial e insertar en open
    State *init = new State(psgs, boats, boatCant, capacidad);
    init->setInitialState();
    open->push(init);
    all->push(init);
    int numSets = 0;

    // generar set que contiene vectores con pasajeros compatibles entre sí
    compSets = incompMtrx->separateNonAdjacent(numSets);

    std::cout << "Conjuntos no adyacentes:" << std::endl;

    for (int i = 0; i < numSets; ++i) {
        std::cout << "[";
        for (int j = 0; j < compSets[i]->capacity; ++j) {
            std::cout << compSets[i]->getPos(j);
            if (j < compSets[i]->capacity - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
    

    // paso 2: mientras open no este vacio
    while (open->top != 0) {
        State *s = open->pop();
        cout << "[RiverCrossing::solve] Camino actual: " << endl;
        s->printPath();
        cout << endl;

        cout << "[RiverCrossing::solve] Estado actual: " << endl;
        s->printState();
        cout << endl << endl;

        // paso 3: preguntamos si es la solucion
        if (s->isFinalState()) {
            delete[] compSets;
            cout << "[RiverCrossing::solve] Solución encontrada!" << endl;
            return s;
        }

        int combSize = 0;

        int* sidePsgs = s->getPassengers(psgs, combSize);

        State* ns = s->crossVoid(sidePsgs, incompMtrx); // Intentar cruzar vacío
        addState(ns, combSize); // Agregar el nuevo estado al heap y stack

        if(s->capacidadActual > 0){

            int* sidePsgsAux = new int[combSize];

            for(int i = 0; i < combSize; i++){
                sidePsgsAux[i] = sidePsgs[i];
            }

            for(int i = 0; i < numSets; i++){
                // cout << "[RiverCrossing::solve] Para el set " << i << "!" << endl;
                int* arrSetInSide = new int[compSets[i]->current];
                int indx = 0, cantSetInSide = 0, cantSideNotInSet = combSize;
                for(int j = 0; j < combSize; j++){
                    int aux = compSets[i]->isInVector(sidePsgsAux[j] - 1);
                    //cout << "[RiverCrossing::solve] sidepsgsaux[j] - 1 = " << sidePsgsAux[j] - 1 << endl;
                    if(sidePsgsAux[j] - 1 > -1 && aux > -1){
                        sidePsgsAux[j] = -1;
                        cantSetInSide++;
                        cantSideNotInSet--;
                        //cout << cantSideNotInSet << endl;
                        arrSetInSide[indx] = compSets[i]->data[aux] + 1;
                        indx++;
                        
                    }
                }

                // cout << "[RiverCrossing::solve] Pasajeros del set que estan en la orilla: ";
                // for(int j = 0; j < indx; j++){
                //     cout << arrSetInSide[j];
                // }
                // cout << endl << "[RiverCrossing::solve] Pasajeros que estan en la orilla y no en el set: " << cantSideNotInSet << endl;

                //cin.get();

                if(cantSideNotInSet <= 0 || (cantSetInSide <= s->capacidadActual && cantSetInSide > 0)){
                    if(!cantSideNotInSet <= 0){
                        // cout << "[RiverCrossing::solve] Hay mas de 1 set de compatibilidad en la orilla" << endl;
                        State* ns = s->cross(arrSetInSide, cantSetInSide, incompMtrx);
                        addState(ns, cantSetInSide);
                    }
                    else{
                        // cout << "[RiverCrossing::solve] Todos los pasajeros en esta orilla son compatibles entre si" << endl;
                        combinaciones(s, arrSetInSide, s->capacidadActual, combSize);
                        break;
                    }
                }
            }
        }

        // cout << "[RiverCrossing::solve] Heap: " << endl;
        //open->printHeap();
        //cout << endl;
    }

    delete[] compSets;
    cout << "[RiverCrossing::solve] No se encontró solución." << endl;
    return nullptr; // caso nuestra búsqueda no llegó a solución
}

// Entradas: estado a añadir (State*), arreglo de pasajeros (int*), tamaño de las combinaciones (int), cantidad de combinaciones (int&)
// Salidas: void
// Descripcion: Inicializa la funcion que genera todas las combinaciones de pasajeros a cruzar y los añade al stack y al heap
void RiverCrossing::combinaciones(State* s, int* arr, int size, int& combSize) {

    int* arrReal = new int[combSize];
    int idx = 0;
    // cout << "[RiverCrossing::combinaciones] arrReal[ ";
    for (int i = 0; i < combSize; i++) {
        if (arr[i] > 0) {
            arrReal[idx++] = arr[i];
            // cout << arrReal[idx - 1] << " ";
        }
    }
    // cout << "]" << endl;
    int n = combSize; // Actualizar `n` al tamaño real

    // Determinar la cantidad máxima de combinaciones posibles
    int maxCombinations = (1 << n) - 1; // 2^n - 1 combinaciones
    combSize = 0;
    int minSize = s->capacidadActual;

    // Generar combinaciones desde el tamaño más grande hacia el más pequeño
    for (int r = size; r >= minSize; r--) {
        int* data = new int[r]; // Espacio temporal para una combinación
        combinacion(s, arrReal, data, 0, n - 1, 0, r, combSize);
        delete[] data; // Liberar memoria del temporal
    }

    delete[] arrReal; // Liberar memoria de `arrReal`
}

// Entradas: estado a añadir (State*), arreglo de pasajeros (int*), arreglo de combinaciones (int*), inicio (int), fin (int), indice (int), tamaño de la combinacion (int), indice en la combinacion (int&)
// Salidas: void
// Descripcion: Genera todas las combinaciones de pasajeros a cruzar y los añade al stack y al heap
void RiverCrossing::combinacion(State* s, int* arr, int* data, int start, int end, int index, int r, int& combIndex) {
    // Caso base: combinación completa
    if (index == r) {
        // cout << "[RiverCrossing::combinacion] Verificando si cruzar con {";
        // for (int i = 0; i < r; i++) {
        //     cout << data[i] - 1 << " ";
        // }
        // cout << "}" << " capacidad: " << capacidad << endl;

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

// Entradas: estado a añadir (State*), cantidad de pasajeros curzados (int)
// Salidas: void
// Descripcion: Añade un nuevo estado al stack y al heap, verificando si es valido y si no se repite, y calcula su prioridad
void RiverCrossing::addState(State* ns, int combSize) {
    if (ns != nullptr) {
        priorityCalc(ns, combSize);
        capacidadCalc(ns, combSize);
        if (!all->find(ns)) {
            // cout << "[RiverCrossing::addState] Estado no estaba en stack. Actualizando heap y stack..." << endl;
            // ns->printState(boatCant);
            all->push(ns);
            open->push(ns);
        }else{
            // cout << "[RiverCrossing::addState] Estado ya estaba en stack. No se agrega." << endl;
        }
    }
}

// Entradas: estado a añadir (State*), cantidad de pasajeros curzados (int)
// Salidas: void
// Descripcion: Calcula la capacidad de los barcos para el estado a añadir
void RiverCrossing::capacidadCalc(State* s, int combSize) {
    // Se calcula la capacidad del barco como la cantidad de pasajeros en la orilla activa
    int count = 0;
    for (int i = 0; i < boatCant; i++) {
        if (!s->boats[i].isFuelEmpty()) {
            if(combSize > 0) {
                combSize -= s->boats[i].capacidad;
                s->boats[i].updateFuelAmt();
            }
            count += s->boats[i].capacidad;
        }
    }
    s->capacidadActual = count;
}

// Entradas: estado a añadir (State*), cantidad de pasajeros curzados (int)
// Salidas: void
// Descripcion: Calcula la prioridad del estado a añadir
void RiverCrossing::priorityCalc(State* s, int combSize) {
    // Se calcula la prioridad como la cantidad de elementos en la orilla
    // izquierda que no son incompatibles entre si
    s->priority = (s->depth + combSize) * 2;    // HEURISTICA = 2 * (cantidad de pasos realizados + cantidad de pasajeros llevados) + cantidad de pasajeros a la derecha
    for (int i = 0; i < psgs; i++) {
        if (!s->Izq[i]) {
            s->priority++;
        }
    }
    //cout << "[RiverCrossing::priorityCalc] Priority: " << s->priority << endl;
    //cout << "[RiverCrossing::priorityCalc] Depth: " << s->depth << endl;

}