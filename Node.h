#include <iostream>

class Node{
    public:
        int Val;
        Node* Next;
        Node();
        Node(int val);
        ~Node();
        Node(Node* next);
        Node(int val, Node* next);
        void linkNode(Node* nextNode);
};