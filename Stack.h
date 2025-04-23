#include<iostream>
#include "State.h"


using namespace std;

class Stack {
    public:
    State **arr;
    int size;
    int top;
    Stack(int size);
    void push(State* s);
    State* pop();
    bool find(State* s);
};