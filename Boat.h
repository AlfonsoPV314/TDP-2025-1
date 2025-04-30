#include <iostream>

class Boat{
    public:
        int id; // el id del barco
        int capacidad;  // la capacidad de pasajeros del barco
        int fuelAmt;    // cuantas veces puede viajar el barco

        // Entradas: nada
        // Salidas: Bote nuevo (Boat)
        // Descripcion: Constructor de un barco.
        Boat();

        // Entradas: id del barco (int), capacidad del barco (int), combustible del barco (int)
        // Salidas: void
        // Descripcion: Inicializa un barco segun los parametros especificados
        void setupBoat(int id, int size, int fuel);

        // Entradas: id del barco (int), capacidad del barco (int)
        // Salidas: void
        // Descripcion: inicializa el id y la capacidad del barco
        void setIdSize(int id, int size);

        // Entradas: combustible del barco (int)
        // Salidas: void
        // Descripcion: inicializa el combustible del barco
        void setFuel(int fuel);

        // Entradas: nada
        // Salidas: void
        // Descripcion: Actualiza los viajes restantes de un barco luego de un viaje
        void updateFuelAmt();

        // Entradas: nada
        // Salidas: si el combustible es 0 o no (bool)
        // Descripcion: verifica si el combustible del barco es 0
        bool isFuelEmpty();

        // Entradas: nada
        // Salidas: void
        // Descripcion: muestra por pantalla un barco
        void printBoat();

        // Entradas: nada
        // Salidas: un puntero al barco clonado (Boat*)
        // Descripcion: hace una copia del barco
        Boat* cloneBoat();
};