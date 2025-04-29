#include <iostream>
using namespace std;

class Vector{
    public: 
        int* data;
        int capacity;
        int current;
        Vector(int* arr, int size);
        Vector();
        ~Vector();
        void push(int value);
        void pop();
        void print();
        int getPos(int pos);
        bool operator==(Vector v);
        bool operator<(Vector v);
        Vector clone();
        Vector* clonePtr();
        int isInVector(int i);
};