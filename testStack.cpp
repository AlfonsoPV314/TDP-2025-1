#include "Stack.h"

int main() {
    Stack *s = new Stack(10); 
    Boat* b = new Boat[1];
    b[0].setupBoat(0, 1, 100);
    State *st = new State(3, b, 0);
    Graph *g = new Graph(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    cout << "Estado inicial st" << endl;
    st->setInitialState();
    st->printState(1);
    cout << "**************" << endl;
    cout << "Estado st1" << endl;
    int* arr = new int[1];
    arr[0] = CABRA;
    State *st1 = st->cross(arr, 1, g);
    st1->printState(1);
    cout << "**************" << endl;
    cout << "Estado st2" << endl;
    int arr2[2] = {-1, 0};
    State *st2 = st1->crossVoid(arr2, g);
    st2->printState(1);
    cout << "**************" << endl;
    cout << "push estados st, st1, st2" << endl;
    s->push(st);
    s->push(st1);
    s->push(st2);

    cout << "busco st1 en la pila" << endl;
    if (s->find(st1)) {
        cout << "Estado encontrado en la pila" << endl;
        st1->printState(1);
    } else {
        cout << "Estado no encontrado en la pila" << endl;
    }
}