#include "Boat.h"

Boat::Boat(){
    id = 0;
    size = 0;
    fuelAmt = 0;
}

void Boat::setupBoat(int id, int size, int fuel) {
    this->id = id;
    this->size = size;
    fuelAmt = fuel;
}

void Boat::updateFuelAmt() {
    fuelAmt--;
}

bool Boat::isEmpty() {
    return fuelAmt > 0;
}