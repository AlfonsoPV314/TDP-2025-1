#include "Stack.h"

Stack::Stack(int size) {
    arr = new State*[size]; 
    this->size=size;
    top=0;
    currentSize=0;
}

void Stack::push(State* s) {
    if (top==size) { // esta lleno
        cout << "[Stack::push] stack overflow!" << endl;
        return;
    } 
    arr[top]=s;
    top++;
    currentSize++;
    return;
}

State* Stack::pop() {
    if (top==0) { // esta vacio
        return nullptr;
    }
    top--;
    currentSize--;
    return(arr[top]);
}

bool Stack::find(State *s) {
    if (top==0 || nullptr == s) { // esta vacio
        return false;
    } 
    for(int k=0; k<top; k++) {
        if (*s == *arr[k]) {
            return true;
        }
    }
    return false;
}