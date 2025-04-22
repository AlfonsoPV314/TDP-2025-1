all: testGraph testHeap testState testStack testRiverCrossing

ClaseEjemplo.o: ClaseEjemplo.h ClaseEjemplo.cpp
	g++ -c ClaseEjemplo.cpp

State.o: State.cpp State.h
	g++ -c State.cpp

Stack.o: Stack.cpp Stack.h 
	g++ -c Stack.cpp

RiverCrossing.o: RiverCrossing.h RiverCrossing.cpp
	g++ -c RiverCrossing.cpp

Heap.o: Heap.cpp Heap.h
	g++ -c Heap.cpp

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp

Boat.o: Boat.cpp Boat.h
	g++ -c Boat.cpp

testGraph: Graph.o testGraph.cpp
	g++ Graph.o testGraph.cpp -o testGraph

testRiverCrossing: Boat.o Graph.o State.o Stack.o Heap.o RiverCrossing.o testRiverCrossing.cpp
	g++ Boat.o Graph.o State.o Stack.o Heap.o RiverCrossing.o testRiverCrossing.cpp -o testRiverCrossing

testStack: Boat.o Graph.o State.o Stack.o testStack.cpp
	g++ Boat.o Graph.o State.o Stack.o testStack.cpp -o testStack

testState: Boat.o Graph.o State.o testState.cpp
	g++ Boat.o Graph.o State.o testState.cpp -o testState

testHeap: Boat.o Graph.o State.o Heap.o testHeap.cpp
	g++ Boat.o Graph.o State.o Heap.o testHeap.cpp -o testHeap

clean:
	rm -rf *.o testList testGraph testHeap testState testStack testRiverCrossing testGraph testList