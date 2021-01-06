OPTS = -Wall -g -pthread --std=c++11 

readGraph.o: readGraph.cpp readGraph.hpp
	g++ ${OPTS} -c readGraph.cpp

shortestPath.o: shortestPath.cpp shortestPath.hpp BinaryHeap.hpp
	g++ ${OPTS} -c shortestPath.cpp 

BinaryHeap.o: BinaryHeap.cpp BinaryHeap.hpp
	g++ ${OPTS} -c BinaryHeap.cpp

bellmanFord: bellmanFord.cpp readGraph.o shortestPath.o BinaryHeap.o
	g++ ${OPTS} -o bellmanFord bellmanFord.cpp readGraph.o shortestPath.o BinaryHeap.o

currency: currency.cpp readGraph.o shortestPath.o BinaryHeap.o
	g++ ${OPTS} -o currency currency.cpp readGraph.o shortestPath.o BinaryHeap.o

matrixDijkstra: matrixDijkstra.cpp readGraph.o shortestPath.o BinaryHeap.o
	g++ ${OPTS} -o matrixDijkstra matrixDijkstra.cpp readGraph.o shortestPath.o BinaryHeap.o

parallelDijkstra: parallelDijkstra.cpp readGraph.o shortestPath.o BinaryHeap.o
	g++ ${OPTS} -o parallelDijkstra parallelDijkstra.cpp readGraph.o shortestPath.o BinaryHeap.o

listDijkstra: listDijkstra.cpp readGraph.o shortestPath.o  BinaryHeap.o
	g++ ${OPTS} -o listDijkstra listDijkstra.cpp readGraph.o shortestPath.o BinaryHeap.o

mapqueue: mapqueue.cpp
	g++ ${OPTS} -o mapqueue mapqueue.cpp
