#include "Heap.h"

int main() {
    Heap *h = new Heap(2);
    State *s = new State();
    s->setInitialState();
    h->push(s);
    State *s1 = s->cross(CABRA);
    h->push(s1);
    State *s2 = s1->crossVoid();
    h->push(s2);
    State *s3 = s2->cross(ZORRO);
    h->push(s3);
    State *s4 = s3->cross(CABRA);
    h->push(s4);

    h->printHeap();


    while((s=h->pop())!=nullptr) {
        cout << s->priority << endl;
    }
}