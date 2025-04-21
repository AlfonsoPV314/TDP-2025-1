all: testList testGraph testHeap testState testStack testRiverCrossing testGraph testList

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

Graph.o: Node.o List.o Graph.cpp Graph.h
	g++ -c Graph.cpp

List.o: Node.o List.cpp List.h
	g++ -c List.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

testGraph: Node.o List.o Graph.o testGraph.cpp
	g++ Node.o List.o Graph.o testGraph.cpp -o testGraph

testList: Node.o List.o testList.cpp
	g++ Node.o List.o testList.cpp -o testList

testRiverCrossing: Node.o List.o Graph.o State.o Stack.o Heap.o RiverCrossing.o testRiverCrossing.cpp
	g++ Node.o List.o Graph.o State.o Stack.o Heap.o RiverCrossing.o testRiverCrossing.cpp -o testRiverCrossing

testStack: Node.o List.o Graph.o State.o Stack.o testStack.cpp
	g++ Node.o List.o Graph.o State.o Stack.o testStack.cpp -o testStack

testState: Node.o List.o Graph.o State.o testState.cpp
	g++ Node.o List.o Graph.o State.o testState.cpp -o testState

testHeap: Node.o List.o Graph.o State.o Heap.o testHeap.cpp
	g++ Node.o List.o Graph.o State.o Heap.o testHeap.cpp -o testHeap

clean:
	rm -rf *.o testList testGraph testHeap testState testStack testRiverCrossing testGraph testList