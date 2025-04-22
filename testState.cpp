#include "State.h"

int main() {
    State *s = new State(); 
    s->printState();

    s->setInitialState();
    s->printState();
    State *s1 = s->cross(ZORRO, 1);
    if (s1 != nullptr) {
        s1->printState();
    } else {
        cout << "No se puede cruzar el zorro" << endl;
    }
    int* arr = new int[1];
    arr[0] = CABRA;
    State *s2 = s->cross(arr, 1);
    if (s2 != nullptr) {
        s2->printState();
    } else {
        cout << "No se puede cruzar la cabra" << endl;
    }

}