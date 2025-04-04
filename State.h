#include "Graph.h"
#include "Boat.h"

class State{
    int* Isle1;
    int* Isle2;
    Graph M;
    Boat* BoatArray;
    float Priority;
    State* Parent;
    // string Operation;
    bool operator==(State* s);
    bool operator<(State* s);
    State();
    void printState();
};