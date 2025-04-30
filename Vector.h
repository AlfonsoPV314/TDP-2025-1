#include <iostream>
using namespace std;

class Vector{
    public: 
        int* data;  // datos del vector
        int capacity;   // capacidad maxima
        int current;    // indice actual del ultimo dato

        // Entradas: arreglo sobre el cual crear los dtos (int*), tamaño del arreglo (int)
        // Salidas: Nuevo vector (Vector)
        // Descripcion: Constructor de un vector a partir de un arreglo
        Vector(int* arr, int size);

        // Entradas: nada
        // Salidas: Nuevo vector (Vector)
        // Descripcion: Constructor de un vector
        Vector();

        // Entradas: nada
        // Salidas: destruccion del vector
        // Descripcion: destructor de un vector
        ~Vector();

        // Entradas: valor a añadir al vector (int)
        // Salidas: void
        // Descripcion: Funcion que añade un dato a los datos del vector
        void push(int value);

        // Entradas: nada
        // Salidas: void
        // Descripcion: Funcion que elimina el valor del indice actual del vector
        void pop();

        // Entradas: posicion del elemento a recuperar (int)
        // Salidas: elemento de la posicion especificada (int)
        // Descripcion: Funcion que busca en los dtos del vector el elemento de una posicion dada
        int getPos(int pos);

        // Entradas: Vector a comparar (Vector)
        // Salidas: si los vectores son iguales o no (bool)
        // Descripcion: Verifica si 2 vectores son iguales
        bool operator==(Vector v);

        // Entradas: Vector a comparar (Vector)
        // Salidas: si el vector a la izquierda es menor al de la derech (bool)
        // Descripcion: Verifica si el vector es menor que un vector dado
        bool operator<(Vector v);

        // Entradas: elemento a verificar si está o no en el vector (int)
        // Salidas: posicion del elemento, si es que está (int)
        // Descripcion: Funcion que verifica si un dato está en los datos del vector
        int isInVector(int i);

        // Entradas: nada
        // Salidas: void
        // Descripcion: Imprime por pantalla un vector
        void printVector();
};