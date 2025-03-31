# Compilation and linking logic

all: Node.o List.o Graph.o main

# Compile Node.cpp to Node.o
Node.o: Node.cpp Node.h	# Node.cpp depends on Node.h
	g++ -c Node.cpp

# Compile List.cpp to List.o
List.o: List.cpp List.h Node.h	# List.o depends on List.cpp, List.h and Node.h
	g++ -c List.cpp

Graph.o: Graph.cpp Graph.h List.h Node.h	# Graph.o depends on Graph.cpp, Graph.h, List.h and Node.h
	g++ -c Graph.cpp

# Link main.o and Node.o to create the executable 'main'
main: main.cpp Node.o List.o Graph.o	# main depends on main.cpp, Node.o and List.o (instructions)
	g++ Node.o List.o Graph.o main.cpp -o main

# Clean up the object files and executables
clean:
	rm -rf *.o main
	
# Run the program
run: all
	./main