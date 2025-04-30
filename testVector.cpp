#include "Vector.h"

int main(){

    std::cout << "Creando vector v1 a traves de push..." << std::endl;
    Vector* v1 = new Vector();
    v1->push(1);
    v1->push(2);
    v1->printVector();

    std::cout<< endl << "Creando vector v2 a partir de un arreglo..." << std::endl;
    int* arr = new int[3];
    arr[0] = 3;
    arr[1] = 4;
    arr[2] = 5;
    Vector* v2 = new Vector(arr, 3);
    v2->printVector();

    cout << endl << "popeando vector v1..." << endl;
    cout << "nuevo vector v1: ";
    v1->printVector();
    
    std::cout << endl;
    if(v1 < v2){
        std::cout << "v1 es menor que v2" << std::endl;
    } else {
        std::cout << "v2 es mayor que v1" << std::endl;
    }

    if(v1 == v2){
        std::cout << "v1 es igual a v2" << std::endl;
    } else {
        std::cout << "v1 no es igual a v2" << std::endl;
    }

    cout << endl << "esta 3 en el vector v1?" << endl;
    if(v1->isInVector(3) == -1){
        cout << "nop" << endl;
    }else{
        cout << "si! y en la posicion " << v1->isInVector(3) << endl;
    }

    cout << endl << "esta 3 en el vector v2?" << endl;
    if(v2->isInVector(3) == -1){
        cout << "nop" << endl;
    }else{
        cout << "si! y en la posicion " << v2->isInVector(3) << endl;
    }

    return 0;
}