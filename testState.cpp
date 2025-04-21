#include "State.h"

int main() {
    State *s = new State(); 
    s->printState();

    s->setInitialState();
    s->printState();
    State *s1 = s->cross(ZORRO);
    if (s1 != nullptr) {
        s1->printState();
    } else {
        cout << "No se puede cruzar el zorro" << endl;
    }
    State *s2 = s->cross(CABRA);
    if (s2 != nullptr) {
        s2->printState();
    } else {
        cout << "No se puede cruzar la cabra" << endl;
    }

}