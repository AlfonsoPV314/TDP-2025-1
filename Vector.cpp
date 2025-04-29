#include "Vector.h"

Vector::Vector(int* arr, int size){
    capacity = size;  // set the initial capacity
    current = 0;   // set the current position to the size of the array
    data = new int[capacity];  // allocate memory for the vector
    for (int i = 0; i < capacity; ++i) {
        data[i] = arr[i];
        current++;
    }
}

Vector::Vector(){
    capacity = 1;  // initial capacity
    current = 0;   // current position
    data = new int[capacity];  // allocate memory for the vector
}

Vector::~Vector() {
    delete[] data;
}

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

void Vector::pop() {

    // if we are not at the start of the vector
    if (current > 0) {
        current--;  // no need to delete the elements after current, as they will be overwritten
    }
}

void Vector::print() {
    for (int i = 0; i < current; i++) {
        cout << "{" << data[i] << "} ";
    }
    cout << endl;
}

int Vector::getPos(int pos) {
    if (pos < 0 || pos >= current) {
        return -1; // out of bounds
    }
    return data[pos];   // simple as that, huh?
}

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

Vector Vector::clone() {
    Vector v;
    v.capacity = capacity;
    v.current = current;
    v.data = new int[capacity];
    for (int i = 0; i < current; i++) {
        v.data[i] = data[i];
    }
    return v;
}

Vector* Vector::clonePtr() {
    Vector* v = new Vector();
    v->capacity = capacity;
    v->current = current;
    v->data = new int[capacity];
    for (int i = 0; i < current; i++) {
        v->data[i] = data[i];
    }
    return v;
}

int Vector::isInVector(int i){
    if(i < 0){
        return -1;
    }
    for(int j = 0; j < current; j++){
        if(data[j] == i) return j;
    }
    return -1;
}