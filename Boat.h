#include <iostream>

class Boat{
    public:
        int id;
        int capacidad;
        int fuelAmt;
        Boat();
        void setupBoat(int id, int size, int fuel);
        void setIdSize(int id, int size);
        void setFuel(int fuel);
        void updateFuelAmt();
        bool isFuelEmpty();
};