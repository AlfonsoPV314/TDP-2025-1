#include "Node.h"

Node::Node(){
    Val = -1;
    Next = nullptr;
}

Node::Node(int val){
    this->Val = val;
    Next = nullptr;
}

Node::Node(Node* next){
    Val = -1;
    this->Next = next;
}

Node::Node(int val, Node* next){
    this->Val = val;
    this->Next = next;
}

Node::~Node(){}

void Node::linkNode(Node* nextNode){
    Next = nextNode;
}