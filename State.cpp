#include "State.h"

State::State(int psgs, Boat* boats, int capacidad) {
    isIzq=false;
    priority=-1;
    parent=nullptr;
    this->boats = boats;
    this->psgs = psgs;
    Izq = new bool[psgs];
    Der = new bool[psgs];
    capacidadActual = capacidad;
    operation="";
    for (int i = 0; i < psgs; i++) {
        Izq[i] = false; // todos los elementos en la orilla izquierda
        Der[i] = false; // todos los elementos en la orilla derecha
        //incompArr[i] = 0; // inicializa el contador de incompatibilidades
    }
    depth = 0;
}

void State::setInitialState() {
    isIzq=true;
    parent=nullptr;
    priority=0;
    operation="Inicializacion";
    for(int i = 0; i < psgs; i++) {
        Der[i] = false; // todos los elementos en la orilla derecha
        Izq[i] = true; // todos los elementos en la orilla izquierda
    }
    // for(int i = 0; i < psgs; i++) {
    //     for(int j = 0; j < psgs; j++) {
    //         if (incompMtrx->M[i][j] == 1) {
    //             incompArr[i]++;
    //         }
    //     }
    // }
}

State* State::clone() {
    State *n = new State(psgs, boats, capacidadActual);
    n->isIzq = isIzq;
    n->parent = parent;
    n->operation = operation;
    n->priority = priority;
    n->depth = depth;
    n->boats = boats;
    for (int i = 0; i < psgs; i++) {
        n->Izq[i] = Izq[i];
        n->Der[i] = Der[i];
    }
    return n;    
}

int* State::getPassengers(int size, int& count) {
    cout << "[State::getPassengers] INPUT: size = " << size << " count = " << count << endl;
    // Crear un arreglo dinámico para almacenar los índices
    int* result = new int[size];
    count = 0;

    // Recorrer el arreglo para encontrar pasajeros en la orilla activa
    for (int i = 0; i < size; i++) {
        if ((isIzq && Izq[i]) || (!isIzq && !Izq[i])) {
            result[count++] = i + 1;
        }
    }
    cout << "[State::getPassengers] count: " << count << endl;

    // Ajustar el tamaño del arreglo para que termine con un cero
    int* finalResult = new int[count + 1];
    cout << "[State::getPassengers] OUTPUT: ";
    for (int i = 0; i < count; i++) {
        finalResult[i] = result[i];
        cout << finalResult[i] << " ";
    }
    cout << endl;
    finalResult[count] = 0; // Indicador de fin de lista
    delete[] result;

    return finalResult;
}


State* State::cross(int* comb, int capacidad, Graph* incompMtrx) {
    State* n = clone();
    n->depth++;

    if(comb[0] == -1){
        return crossVoid(comb, incompMtrx); // Si la combinación es -1, cruzar vacío
    }

    for(int i = 0; i < capacidad; i++) {
        comb[i]--;
    }

    // Validar si la combinación puede cruzar
    bool* currentSide = isIzq ? Izq : Der;
    if (!incompMtrx->isValid(comb, currentSide, capacidad)) {
        return nullptr; // Si no es válida, no se realiza el cruce
    }

    // Actualizar el estado para todos los pasajeros de la combinación
    for (int i = 0; i < capacidad; i++) {
        if(comb[i] > -1) {
            int psg = comb[i];
            if (isIzq && Izq[psg]) {
                cout << "[State::cross] Cruzando: " << psg << " a orilla derecha " << endl;
                n->Izq[psg] = false;
                n->Der[psg] = true;
            } else if (!isIzq && Der[psg]) {
                cout << "[State::cross] Cruzando: " << psg << " a orilla izquierda" << endl;
                n->Der[psg] = false;
                n->Izq[psg] = true;
            }
        }
    }

    // Actualizar el estado general
    n->isIzq = !isIzq;
    n->operation = "Cruza {";
    for (int i = 0; i < capacidad; i++) {
        if (comb[i] > -1) {
            n->operation += to_string(comb[i]) + ", ";   
        }
    }
    n->operation += "}";
    n->parent = this;
    cout << endl;

    return n;
}


State* State::crossVoid(int* comb, Graph* incompMtrx) {
    State *n = clone();
    n->operation = "crossVoid";
    n->depth++;
    // detectar orilla
    if (isIzq) {
        if (incompMtrx->isValid(comb, Izq, 0)){
            n->isIzq = false;
            n->parent = this; // OJO: faltaba esto
            return n;
        }
    } else {
        if (incompMtrx->isValid(comb, Der, 0)){
            n->isIzq = true;
            n->parent = this;
            return n;
        }
    }
    return nullptr; 
}

bool State::isFinalState() {
    for(int i = 0; i < psgs; i++){
        if(Izq[i]){
            return false;
        }
    }
    return true;
}    

void State::printState(int boatCant) {
    cout << "[State::printState]" << operation << endl;
    cout << "=======================" << endl;
    cout << "Barco en la orilla: " << (isIzq ? "Izquierda" : "Derecha") << endl;
    cout << "Orilla Izquierda: ";
    for(int i=0; i < psgs; i++){
        if(Izq[i]){
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "Orilla Derecha: ";
    for(int i=0; i < psgs; i++){
        if(!Izq[i]){
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "Capacidad actual: " << capacidadActual << endl;
    cout << "Profundidad: " << depth << endl;
    cout << "Barcos: " << endl;
    for (int i = 0; i < boatCant; i++) {
        cout << "Barco " << boats[i].id << " (capacidad: " << boats[i].capacidad << ", combustible: " << boats[i].fuelAmt << ") " << endl;
    }
    cout << "=======================" << endl;
}

bool State::operator==(State s) {
    // No se va a controlar la variable parent y operation
    if (isIzq != s.isIzq) {
        return false;
    }
    for (int i = 0; i < psgs; i++) {
        if (Izq[i] != s.Izq[i]) {
            return false;
        }
    }
    for (int i = 0; i < psgs; i++) {
        if (Der[i] != s.Der[i]) {
            return false;
        }
    }
    return true;
}

bool State::operator<(State s) {
    return priority < s.priority;
}

void State::printPath() {
    if(parent==nullptr) { // caso base
        cout << "[State::printPath]" << operation << " -> "; // va a sobrar una flecha en el ultimo
        return;
    }
    if (parent!=nullptr) { // recorrido hacia la raiz
        parent->printPath();
    }
    cout << operation << " -> "; // va a sobrar una flecha en el ultimo
}
