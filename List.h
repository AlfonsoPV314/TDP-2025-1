#include <iostream>
#include "Node.h"
using namespace std;

class List{
    public:
        Node* Head;
        int Len;
        List();
        List(Node* head);
        List(int val);
        ~List();
        void addFirst(Node* head);
        void addFirst(int val);
        void addLast(Node* tail);
        void addLast(int val);
        // void addInPos(Node* node, int pos);
        // void addInPos(int val, int pos);
        bool isEmpty();
        void printList();
        int get(int pos);
        int set(int pos, int val);
        int remove(int pos);
        // int remove(Node* node);
        // int remove(int val);
};