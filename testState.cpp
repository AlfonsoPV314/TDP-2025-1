#include "State.h"

int main() {
    Boat* b = new Boat[1];
    b[0].setupBoat(0, 1, 100);
    State *s = new State(3, b, 0); 
    Graph *g = new Graph(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    s->printState(1);

    cout << endl;

    cout << "Inicializando estado..." << endl;
    
    s->setInitialState();
    s->printState(1);

    cout << endl;

    cout << "Intentando cruzar zorro..." << endl;
    int* arrZ = new int[1];
    arrZ[0] = 1;
    State *s1 = s->cross(arrZ, 1, g);
    if (s1 != nullptr) {
        cout << "Exito cruzando zorro!" << endl;
        s1->printState(1);
    } else {
        cout << "No se puede cruzar el zorro" << endl;
    }

    cout << endl;

    cout << "Intentando cruzar cabra..." << endl;
    int* arrC = new int[1];
    arrC[0] = 2;
    State *s2 = s->cross(arrC, 1, g);
    if (s2 != nullptr) {
        cout << "Exito cruzando cabra!" << endl;
        s2->printState(1);
    } else {
        cout << "No se puede cruzar la cabra" << endl;
    }

    cout << endl;

    cout << "Intentando cruzar repollo..." << endl;
    int* arrR = new int[1];
    arrR[0] = 3;
    State *s3 = s->cross(arrR, 1, g);
    if (s3 != nullptr) {
        cout << "Exito cruzando repollo!" << endl;
        s3->printState(1);
    } else {
        cout << "No se puede cruzar el repollo" << endl;
    }
}