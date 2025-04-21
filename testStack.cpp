#include "Stack.h"

int main() {
    Stack *s = new Stack(10); 
    State *st = new State();
    cout << "Estado inicial st" << endl;
    st->setInitialState();
    st->printState();
    cout << "**************" << endl;
    cout << "Estado st1" << endl;
    State *st1 = st->cross(CABRA);
    st1->printState();
    cout << "**************" << endl;
    cout << "Estado st2" << endl;
    State *st2 = st1->crossVoid();
    st2->printState();
    cout << "**************" << endl;
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