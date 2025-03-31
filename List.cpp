#include "List.h"

List::List(){
    Head = nullptr;
    Len = 0;
}

List::List(Node* head){
    this->Head = head;
    Len = 1;
}

List::List(int val) : List(new Node(val)){} // delegates the constructor to the List constructor with a Node

List::~List(){
    Node* current = Head;
    Node* next = nullptr;
    while(current != nullptr){
        next = current->Next;
        delete current;
        current = next;
    }
    Head = nullptr;
    Len = 0;
}

void List::addFirst(Node* head){
    if(head == nullptr){
        head = new Node(Head);
    }
    head->Next = this->Head;
    this->Head = head;
    Len++;
}

void List::addFirst(int val){
    Node* newHead = new Node(val);
    addFirst(newHead);
}

void List::addLast(Node* tail){
    if(Head == nullptr){
        addFirst(tail);
        return;
    }
    Node* aux = Head;
    while(aux->Next != nullptr){
        aux = aux->Next;
    }
    aux->Next = tail;
    Len++;
}

void List::addLast(int val){
    if(Head == nullptr){
        addFirst(val);
        return;
    }
    Node* newTail = new Node(val);
    addLast(newTail);
}

bool List::isEmpty(){
    return Head == nullptr;
}

void List::printList(){
    cout << "[ ";
    Node* aux = Head;
    while(aux != nullptr){
        cout << aux->Val << " -> ";
        aux = aux->Next;
    }
    cout << " ]" << endl;
}

int List::get(int pos){
    if(pos < 0 || pos >= Len){
        return -1;
    }
    Node* aux = Head;
    for(int i = 0; i < pos; i++){
        aux = aux->Next;
    }
    return aux->Val;
}

int List::set(int pos, int val){
    if(pos < 0 || pos >= Len){
        return -1;
    }
    Node* aux = Head;
    for(int i = 0; i < pos; i++){
        aux = aux->Next;
    }
    int oldVal = aux->Val;
    aux->Val = val;
    return oldVal;
}

int List::remove(int pos){
    if(pos < 0 || pos >= Len){
        return -1;
    }
    Node* aux = Head;
    if(pos == 0){
        Head = aux->Next;
        int val = aux->Val;
        delete aux;
        Len--;
        return val;
    }
    for(int i = 0; i < pos - 1; i++){
        aux = aux->Next;
    }
    Node* toDelete = aux->Next;
    int val = toDelete->Val;
    aux->Next = toDelete->Next;
    delete toDelete;
    Len--;
    return val;
}