#include "Stack.h"

int main() {
    Stack *s = new Stack(10); 

    Boat* b = new Boat[1];
    b[0].setupBoat(0, 1, 100);

    cout << "Estado st: Creando estado inicial..." << endl;

    State *st = new State(3, b, 1, 0);
    st->setInitialState();
    st->printState();

    cout << endl;

    cout << "Creando grafo..." << endl;

    Graph *g = new Graph(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    g->printGraph();

    cout << endl;

    cout << "Estado st1: Intentando cruzar cabra..." << endl;

    int* arr = new int[1];
    arr[0] = 2;
    State *st1 = st->cross(arr, 1, g);
    st1->printState();

    cout << endl;

    cout << "Estado st2: Intentando cruzar vacío..." << endl;
    int arr2[2] = {-1, 0};
    State *st2 = st1->crossVoid(arr2, g);
    st2->printState();
    cout << endl;

    cout << "push estados st, st1, st2" << endl;
    s->push(st);
    s->push(st1);
    s->push(st2);

    cout << "busco st1 en la pila" << endl;
    if (s->find(st1)) {
        cout << "Estado encontrado en la pila" << endl;
        st1->printState();
    } else {
        cout << "Estado no encontrado en la pila" << endl;
    }
}