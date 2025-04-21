#include "State.h"

State::State() {
    isIzq=false;
    priority=-1;
    parent=nullptr;
    operation="";
    for (int i = 0; i < 3; i++) {
        Izq[i] = false; // todos los elementos en la orilla izquierda
        Der[i] = false; // todos los elementos en la orilla derecha
    }
}

void State::setInitialState() {
    isIzq=true;
    parent=nullptr;
    priority=0;
    operation="Inicializacion";
    incompMtrx = new Graph(3);
    incompMtrx->addEdge(ZORRO, CABRA);
    incompMtrx->addEdge(CABRA, REPOLLO);
    Izq[ZORRO] = true;
    Izq[CABRA] = true;
    Izq[REPOLLO] = true;
    Der[ZORRO] = false;
    Der[CABRA] = false;
    Der[REPOLLO] = false;
    psgs = 3; // cantidad de pasajeros
}

State* State::clone() {
    State *n = new State();
    n->isIzq = isIzq;
    n->parent = parent;
    n->operation = operation;
    n->priority = priority;
    n->incompMtrx = incompMtrx->clonePtr(); // se clona la matriz de incompatibilidad
    n->psgs = psgs;
    for (int i = 0; i < 3; i++) {
        n->Izq[i] = Izq[i];
        n->Der[i] = Der[i];
    }
    return n;    
}

State* State::cross(int psg){
    State *n = clone();
    // detectar orilla
    if(psg == this->psgs){
        return crossVoid();
    }
    if (isIzq && Izq[psg]){
        if (incompMtrx->isValid(psg, Izq)){
            n->operation = "Cruza " + to_string(psg);
            n->Izq[psg] = false;
            n->Der[psg] = true;
            n->isIzq = false;
            n->parent=this;
            return n;
        }
    } 
    else if (!isIzq && Der[psg]){
        if (incompMtrx->isValid(psg, Der)){
            n->operation = "Cruza " + to_string(psg);
            n->Der[psg] = false;
            n->Izq[psg] = true;
            n->isIzq = true;
            n->parent=this; 
            return n;
        }
    }
    return nullptr; 
}

State* State::crossVoid() {
    State *n = clone();
    n->operation = "crossVoid";
    // detectar orilla
    if (isIzq) {
        if (incompMtrx->isValid(-1, Izq)){
            n->isIzq = false;
            n->parent = this; // OJO: faltaba esto
            return n;
        }
    } else {
        if (incompMtrx->isValid(-1, Der)){
            n->isIzq = true;
            n->parent = this;
            return n;
        }
    }
    return nullptr; 
}

bool State::isFinalState() {
    return(Der[ZORRO]&&Der[CABRA]&&Der[REPOLLO]);
}    

void State::printState() {
    cout << "[State::printState]" << operation << endl;
    cout << "=======================" << endl;
    cout << "Barco en la orilla: " << (isIzq ? "Izquierda" : "Derecha") << endl;
    cout << "Orilla Izquierda: ";
    if (Izq[ZORRO]) cout << "Zorro ";
    if (Izq[CABRA]) cout << "Cabra ";
    if (Izq[REPOLLO]) cout << "Repollo ";
    cout << endl;

    cout << "Orilla Derecha: ";
    if (Der[ZORRO]) cout << "Zorro ";
    if (Der[CABRA]) cout << "Cabra ";
    if (Der[REPOLLO]) cout << "Repollo ";
    cout << endl;
    cout << "=======================" << endl;
}

bool State::operator==(State s) {
    // No se va a controlar la variable parent y operation
    if (isIzq != s.isIzq) {
        return false;
    }
    for (int i = 0; i < 3; i++) {
        if (Izq[i] != s.Izq[i]) {
            return false;
        }
    }
    for (int i = 0; i < 3; i++) {
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
