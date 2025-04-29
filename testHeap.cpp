#include "Heap.h"

int main() {
    Heap *h = new Heap(2);

    cout << "Creando bote..." << endl;

    Boat* b = new Boat[1];
    b[0].setupBoat(0, 1, 100);
    b->printBoat();

    cout << endl << "Creando estado inicial..." << endl;

    State *s = new State(3, b, 0);
    s->setInitialState();
    s->printState(1);

    cout << endl << "Creando grafo..." << endl;

    Graph *g = new Graph(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    g->printGraph();

    cout << "Agregando estado inicial al heap..." << endl;
    h->push(s);
    h->printHeap();

    cout << endl << "Intentando cruzar cabra..." << endl;
    int* arr0 = new int[1];
    arr0[0] = 2;
    State *s1 = s->cross(arr0, 1, g);
    s1->printState(1);

    cout << endl << "Agregando estado cruzando cabra al heap..." << endl;
    h->push(s1);
    h->printHeap();

    cout << endl << "Intentando cruzar vacío..." << endl;
    int arr1[2] = {0, 0};
    State *s2 = s1->crossVoid(arr1, g);
    s2->printState(1);

    cout << endl << "Agregando estado cruzando vacío al heap..." << endl;
    h->push(s2);
    h->printHeap();

    cout << endl << "Intentando cruzar vacío de nuevo..." << endl;
    int* arr2 = new int[1];
    arr2[0] = 0;
    State *s3 = s2->cross(arr2, 1, g);
    if(s3 != nullptr){
        s3->printState(1);
    }
    else{
        cout << "No se puede cruzar vacío de nuevo" << endl;
    }

    cout << endl << "Agregando estado cruzando vacío de nuevo al heap..." << endl;
    h->push(s3);
    h->printHeap();

    cout << endl << "Intentando cruzar zorro..." << endl;
    int* arr3 = new int[1];
    arr3[0] = 1;
    State *s4 = s3->cross(arr3, 1, g);
    if(s4 != nullptr){
        s4->printState(1);
    }
    else{
        cout << "No se puede cruzar zorro" << endl;
    }

    cout << endl << "Agregando estado cruzando zorro al heap..." << endl;
    h->push(s4);

    h->printHeap();
    cout << "NOTA: La prioridad se calcula en la clase RiverCrossing" << endl;
}