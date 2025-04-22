#include "Stack.h"

Stack::Stack(int size) {
    arr = new State*[size]; 
    this->size=size;
    top=0;
}

void Stack::push(State* s) {
    if (top==size) { // esta lleno
        cout << "[Stack::push] stack overflow!" << endl;
        return;
    } 
    arr[top]=s;
    top++;
    return;
}

State* Stack::pop() {
    if (top==0) { // esta vacio
        return nullptr;
    }
    top--;
    return(arr[top]);
}

bool Stack::find(State *s) {
    if (top==0 || nullptr == s) { // esta vacio
        return false;
    } 
    for(int k=0; k<top; k++) {
        cout << "Comparando " << k << endl;
        if (*s == *arr[k]) {
            return true;
        }
    }
    return false;
}