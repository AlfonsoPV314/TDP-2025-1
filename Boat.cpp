#include "Boat.h"
using namespace std;

Boat::Boat(){
    id = 0;
    capacidad = 0;
    fuelAmt = 0;
}

void Boat::setupBoat(int id, int size, int fuel) {
    this->id = id;
    capacidad = size;
    fuelAmt = fuel;
    cout << "[Boat::setupBoat] Barco " << id << " creado con capacidad " << size << " y combustible " << fuelAmt << endl;
}

void Boat::updateFuelAmt() {
    fuelAmt--;
    cout << "[Boat::updateFuelAmt] Barco " << id << " fuelAmt: " << fuelAmt << endl;
}

bool Boat::isFuelEmpty() {
    return fuelAmt <= 0;
}