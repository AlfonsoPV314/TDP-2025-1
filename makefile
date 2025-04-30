all: main testGraph testHeap testRiverCrossing testState testStack testVector

ClaseEjemplo.o: ClaseEjemplo.h ClaseEjemplo.cpp
	g++ -g -c ClaseEjemplo.cpp

State.o: State.cpp State.h
	g++ -g -c State.cpp

Stack.o: Stack.cpp Stack.h 
	g++ -g -c Stack.cpp

RiverCrossing.o: RiverCrossing.h RiverCrossing.cpp
	g++ -g -c RiverCrossing.cpp

ReadFile.o: ReadFile.cpp ReadFile.h
	g++ -g -c ReadFile.cpp

Vector.o: Vector.cpp Vector.h
	g++ -g -c Vector.cpp

Heap.o: Heap.cpp Heap.h
	g++ -g -c Heap.cpp

Graph.o: Graph.cpp Graph.h
	g++ -g -c Graph.cpp

Boat.o: Boat.cpp Boat.h
	g++ -g -c Boat.cpp

main: main.cpp Graph.o Boat.o State.o Stack.o Heap.o RiverCrossing.o Vector.o ReadFile.o
	g++ -g Graph.o Boat.o State.o Stack.o Heap.o RiverCrossing.o Vector.o ReadFile.o main.cpp -o main

testGraph: Vector.o Graph.o testGraph.cpp
	g++ -g Vector.o Graph.o testGraph.cpp -o testGraph

testRiverCrossing: Vector.o Boat.o Graph.o State.o Stack.o Heap.o RiverCrossing.o testRiverCrossing.cpp
	g++ -g Vector.o Boat.o Graph.o State.o Stack.o Heap.o RiverCrossing.o testRiverCrossing.cpp -o testRiverCrossing

testStack: Vector.o Boat.o Graph.o State.o Stack.o testStack.cpp
	g++ -g Vector.o Boat.o Graph.o State.o Stack.o testStack.cpp -o testStack

testState: Vector.o Boat.o Graph.o State.o testState.cpp
	g++ -g Vector.o Boat.o Graph.o State.o testState.cpp -o testState

testHeap: Vector.o Boat.o Graph.o State.o Heap.o testHeap.cpp
	g++ -g Vector.o Boat.o Graph.o State.o Heap.o testHeap.cpp -o testHeap

testVector: Vector.o testVector.cpp
	g++ -g Vector.o testVector.cpp -o testVector

clean:
	rm -rf *.o main testGraph testHeap testState testStack testRiverCrossing testGraph testVector