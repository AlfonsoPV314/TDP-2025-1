#include "State.h"

// Entradas: numero de psajeros (int), arreglo de botes (Boat*), cantidad de botes (int), capacidad actual de los botes (int)
// Salidas: Estado nuevo (State)
// Descripcion: Constructor de un estado.
State::State(int psgs, Boat* boats, int cantBotes, int capacidad) {
    isIzq=false;
    priority=-1;
    parent=nullptr;
    this->cantBotes = cantBotes;
    this->boats = new Boat[cantBotes];
    for(int i = 0; i < cantBotes; i++){
        this->boats[i] = *boats[i].cloneBoat();
    }
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

// Entradas: nada
// Salidas: void
// Descripcion: Inicializa el estado y sus atributos asumiendo que es el estado inicial.
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

// Entradas: tamaño del arreglo inicial (int), tamaño del arreglo con la cantidad de pasajeros (int&)
// Salidas: retorna un arreglo con los pasajeros en la orilla activa (int*)
// Descripcion: obtiene los pasajeros presentes en la orilla en la cual se está actualmente
int* State::getPassengers(int size, int& count) {
    // cout << "[State::getPassengers] INPUT: size = " << size << " count = " << count << endl;
    // Crear un arreglo dinámico para almacenar los índices
    int* result = new int[size];
    count = 0;

    // Recorrer el arreglo para encontrar pasajeros en la orilla activa
    for (int i = 0; i < size; i++) {
        if ((isIzq && Izq[i]) || (!isIzq && !Izq[i])) {
            result[count++] = i + 1;
        }
    }
    // cout << "[State::getPassengers] count: " << count << endl;

    // Ajustar el tamaño del arreglo para que termine con un cero
    int* finalResult = new int[count + 1];
    // cout << "[State::getPassengers] OUTPUT: ";
    for (int i = 0; i < count; i++) {
        finalResult[i] = result[i];
        // cout << finalResult[i] << " ";
    }
    // cout << endl;
    finalResult[count] = 0; // Indicador de fin de lista
    delete[] result;

    return finalResult;
}

// Entradas: pasajeros a cruzar (int*), cantidad de pasajeros que cruzan (int), grafo de incompatibilidades
// Salidas: estado con los pasajeros a cruzar en la otra orilla (State*)
// Descripcion: Realiza un cruce de pasajeros en un estado, verificando su validez
State* State::cross(int* comb, int capacidad, Graph* incompMtrx) {
    State* n = clone();
    n->depth++;

    for(int i = 0; i < capacidad; i++) {
        comb[i]--;
    }

    // Validar si la combinación puede cruzar
    bool* currentSide = isIzq ? Izq : Der;
    // cout << "[State::cross] capacidad: " << capacidad << endl;
    if (!incompMtrx->isValid(comb, currentSide, capacidad)) {
        for(int i = 0; i < capacidad; i++) {
            comb[i]++;
        }
        // cout << "[State::cross] Combinación inválida" << endl;
        return nullptr; // Si no es válida, no se realiza el cruce
    }

    // Actualizar el estado para todos los pasajeros de la combinación
    for (int i = 0; i < capacidad; i++) {
        if(comb[i] > -1) {
            int psg = comb[i];
            if (isIzq && Izq[psg]) {
                // cout << "[State::cross] Cruzando: " << psg << " a orilla derecha " << endl;
                n->Izq[psg] = false;
                n->Der[psg] = true;
            } else if (!isIzq && Der[psg]) {
                // cout << "[State::cross] Cruzando: " << psg << " a orilla izquierda" << endl;
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
        comb[i]++; // Volver a la numeración original
    }
    n->operation += "}";
    n->parent = this;

    return n;
}

// Entradas: pasajeros a cruzar (int*) (auxiliar), grafico de incompatibilidades (Graph*)
// Salidas: estado con los botes en la otra orilla (State*)
// Descripcion: Realiza un cruce sin ningun pasajero en un estado, verificando su validez
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

// Entradas: nada
// Salidas: si es el estado final o no (bool)
// Descripcion: verifica si el estado es el estado final
bool State::isFinalState() {
    for(int i = 0; i < psgs; i++){
        if(Izq[i]){
            return false;
        }
    }
    return true;
}    

// Entradas: nada
// Salidas: estado clonado (State*)
// Descripcion: Clona el estado
State* State::clone() {
    State *n = new State(psgs, boats, cantBotes, capacidadActual);
    n->isIzq = isIzq;
    n->parent = parent;
    n->operation = operation;
    n->priority = priority;
    n->depth = depth;
    for (int i = 0; i < psgs; i++) {
        n->Izq[i] = Izq[i];
        n->Der[i] = Der[i];
    }
    return n;    
}

// Entradas: nada
// Salidas: void
// Descripcion: Imprime el estado por pantalla
void State::printState() {
    cout << "[State::printState] " << operation << endl;
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
    cout << "Prioridad: " << priority << endl;
    cout << "Barcos: " << endl;
    for (int i = 0; i < cantBotes; i++) {
        cout << "Barco " << boats[i].id << " (capacidad: " << boats[i].capacidad << ", combustible: " << boats[i].fuelAmt << ") " << endl;
    }
    cout << "=======================" << endl;
}

// Entradas: nada
// Salidas: void
// Descripcion: Imprime por pantalla el camino de los estados
void State::printPath() {
    if(parent==nullptr) { // caso base
        cout << "[State::printPath] " << operation << " -> "; // va a sobrar una flecha en el ultimo
        return;
    }
    if (parent!=nullptr) { // recorrido hacia la raiz
        parent->printPath();
    }
    cout << operation << " -> "; // va a sobrar una flecha en el ultimo
}

// Entradas: estado a verificar (State)
// Salidas: si son iguales o no (bool)
// Descripcion: Verifica si 2 estados son iguales
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

// Entradas: estado a verificar (State)
// Salidas: si el estado es menor a aquel que se compara o no (bool)
// Descripcion: Verifica si el estado es menor que un estado a comparar
bool State::operator<(State s) {
    return priority < s.priority;
}