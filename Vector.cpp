#include "Vector.h"

// Entradas: arreglo sobre el cual crear los dtos (int*), tamaño del arreglo (int)
// Salidas: Nuevo vector (Vector)
// Descripcion: Constructor de un vector a partir de un arreglo
Vector::Vector(int* arr, int size){
    capacity = size;  // set the initial capacity
    current = 0;   // set the current position to the size of the array
    data = new int[capacity];  // allocate memory for the vector
    for (int i = 0; i < capacity; ++i) {
        data[i] = arr[i];
        current++;
    }
}

// Entradas: nada
// Salidas: Nuevo vector (Vector)
// Descripcion: Constructor de un vector
Vector::Vector(){
    capacity = 1;  // initial capacity
    current = 0;   // current position
    data = new int[capacity];  // allocate memory for the vector
}

// Entradas: nada
// Salidas: destruccion del vector
// Descripcion: destructor de un vector
Vector::~Vector() {
    delete[] data;
}

// Entradas: valor a añadir al vector (int)
// Salidas: void
// Descripcion: Funcion que añade un dato a los datos del vector
void Vector::push(int value) {

    // if capacity is full, double the size and copy the data
    if (current == capacity) {
        int* newData = new int[2 * capacity];

        for (int i = 0; i < capacity; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        capacity *= 2;
        data = newData;
    }

    data[current] = value;  // insert the value at the current position of the vector
    current++;  // increment the current position
}

// Entradas: nada
// Salidas: void
// Descripcion: Funcion que elimina el valor del indice actual del vector
void Vector::pop() {

    // if we are not at the start of the vector
    if (current > 0) {
        current--;  // no need to delete the elements after current, as they will be overwritten
    }
}

// Entradas: posicion del elemento a recuperar (int)
// Salidas: elemento de la posicion especificada (int)
// Descripcion: Funcion que busca en los dtos del vector el elemento de una posicion dada
int Vector::getPos(int pos) {
    if (pos < 0 || pos >= current) {
        return -1; // out of bounds
    }
    return data[pos];   // simple as that, huh?
}

// Entradas: Vector a comparar (Vector)
// Salidas: si los vectores son iguales o no (bool)
// Descripcion: Verifica si 2 vectores son iguales
bool Vector::operator==(Vector v) {
    if (current != v.current) {
        return false;
    }
    for (int i = 0; i < current; i++) {
        if (data[i] != v.data[i]) {
            return false;
        }
    }
    return true;
}

// Entradas: Vector a comparar (Vector)
// Salidas: si el vector a la izquierda es menor al de la derech (bool)
// Descripcion: Verifica si el vector es menor que un vector dado
bool Vector::operator<(Vector v) {
    if (current < v.current) {
        return true;
    } else if (current > v.current) {
        return false;
    }
    for (int i = 0; i < current; i++) {
        if (data[i] < v.data[i]) {
            return true;
        } else if (data[i] > v.data[i]) {
            return false;
        }
    }
    return false;
}

// Entradas: elemento a verificar si está o no en el vector (int)
// Salidas: posicion del elemento, si es que está (int)
// Descripcion: Funcion que verifica si un dato está en los datos del vector
int Vector::isInVector(int i){
    if(i < 0){
        return -1;
    }
    for(int j = 0; j < current; j++){
        if(data[j] == i) return j;
    }
    return -1;
}

// Entradas: elemento a verificar si está o no en el vector (int)
// Salidas: posicion del elemento, si es que está (int)
// Descripcion: Funcion que verifica si un dato está en los datos del vector
void Vector::printVector() {
    cout << "[Vector::printVector] Vector: ";
    for (int i = 0; i < current; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}