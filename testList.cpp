#include <iostream>
#include "List.h"
using namespace std;

int main(){
    List* l = new List();
    l->addFirst(2);
    l->addLast(3);
    l->addFirst(1);
    l->printList();
}