#include "State.h"

int main() {
    Boat* b = new Boat[1];
    b[0].setupBoat(0, 1, 100);
    State *s = new State(); 
    Graph *g = new Graph(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    s->printState();

    s->setInitialState(3, b);
    s->printState();
    int* arr2 = new int[1];
    arr2[0] = ZORRO;
    State *s1 = s->cross(arr2, 1, g);
    if (s1 != nullptr) {
        s1->printState();
    } else {
        cout << "No se puede cruzar el zorro" << endl;
    }
    int* arr = new int[1];
    arr[0] = CABRA;
    State *s2 = s->cross(arr, 1, g);
    if (s2 != nullptr) {
        s2->printState();
    } else {
        cout << "No se puede cruzar la cabra" << endl;
    }

}