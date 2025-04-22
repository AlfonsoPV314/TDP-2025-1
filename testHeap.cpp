#include "Heap.h"

int main() {
    Heap *h = new Heap(2);
    State *s = new State();
    s->setInitialState();
    h->push(s);
    int* arr1 = new int[1];
    arr1[0] = CABRA;
    State *s1 = s->cross(arr1, 1);
    h->push(s1);
    int arr4[2] = {-1, 0};
    State *s2 = s1->crossVoid(arr4);
    h->push(s2);
    int* arr2 = new int[1];
    arr2[0] = ZORRO;
    State *s3 = s2->cross(arr2, 1);
    h->push(s3);
    int* arr3 = new int[1];
    arr3[0] = CABRA;
    State *s4 = s3->cross(arr3, 1);
    h->push(s4);

    h->printHeap();


    while((s=h->pop())!=nullptr) {
        cout << s->priority << endl;
    }
}