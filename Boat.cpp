#include "Boat.h"
using namespace std;

// Entradas: nada
// Salidas: Bote nuevo (Boat)
// Descripcion: Constructor de un barco.
Boat::Boat(){
    id = 0;
    capacidad = 0;
    fuelAmt = 0;
}

// Entradas: id del barco (int), capacidad del barco (int), combustible del barco (int)
// Salidas: void
// Descripcion: Inicializa un barco segun los parametros especificados
void Boat::setupBoat(int id, int size, int fuel) {
    this->id = id;
    capacidad = size;
    fuelAmt = fuel;
    // cout << "[Boat::setupBoat] Barco " << id << " creado con capacidad " << size << " y combustible " << fuelAmt << endl;
}

// Entradas: id del barco (int), capacidad del barco (int)
// Salidas: void
// Descripcion: inicializa el id y la capacidad del barco
void Boat::setIdSize(int id, int size) {
    this->id = id;
    capacidad = size;
    // cout << "[Boat::setSize] Barco " << id << " capacidad: " << capacidad << endl;
}

// Entradas: combustible del barco (int)
// Salidas: void
// Descripcion: inicializa el combustible del barco
void Boat::setFuel(int fuel) {
    fuelAmt = fuel;
    // cout << "[Boat::setFuel] Barco " << id << " combustible: " << fuelAmt << endl;
}

// Entradas: nada
// Salidas: void
// Descripcion: Actualiza los viajes restantes de un barco luego de un viaje
void Boat::updateFuelAmt() {
    fuelAmt--;
    // cout << "[Boat::updateFuelAmt] Barco " << id << " fuelAmt: " << fuelAmt << endl;
}

// Entradas: nada
// Salidas: si el combustible es 0 o no (bool)
// Descripcion: verifica si el combustible del barco es 0
bool Boat::isFuelEmpty() {
    return fuelAmt <= 0;
}

// Entradas: nada
// Salidas: void
// Descripcion: muestra por pantalla un barco
void Boat::printBoat() {
    cout << "[Boat::printBoat] Barco " << id << ": (capacidad: " << capacidad << ", combustible: " << fuelAmt << ")" << endl;
}

// Entradas: nada
// Salidas: un puntero al barco clonado (Boat*)
// Descripcion: hace una copia del barco
Boat* Boat::cloneBoat(){
    Boat* newBoat = new Boat();
    newBoat->setupBoat(this->id, this->capacidad, this->fuelAmt);
    return newBoat;
}