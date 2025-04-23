#include "Heap.h"

int main() {
    Heap *h = new Heap(2);
    Boat* b = new Boat[1];
    b[0].setupBoat(0, 1, 100);
    State *s = new State(3, b, 0);
    Graph *g = new Graph(3);
    g->addEdge(0, 1);
    g->addEdge(1, 2);
    s->setInitialState();
    h->push(s);
    cout << "flag1" << endl;
    int* arr1 = new int[1];
    arr1[0] = 1;
    State *s1 = s->cross(arr1, 1, g);
    cout << "flag2" << endl;
    h->push(s1);
    cout << "flag3" << endl;
    int arr4[2] = {-1, 0};
    State *s2 = s1->crossVoid(arr4, g);
    cout << "flag4" << endl;
    h->push(s2);
    cout << "flag5" << endl;
    int* arr2 = new int[1];
    arr2[0] = 0;
    cout << "flag6" << endl;
    State *s3 = s2->cross(arr2, 1, g);
    cout << "flag7" << endl;
    h->push(s3);
    cout << "flag8" << endl;
    int* arr3 = new int[1];
    arr3[0] = 1;
    cout << "flag9" << endl;
    State *s4 = s3->cross(arr3, 1, g);
    cout << "flag10" << endl;
    h->push(s4);

    h->printHeap();


    while((s=h->pop())!=nullptr) {
        cout << s->priority << endl;
    }
}