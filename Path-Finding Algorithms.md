#### Path-Finding Algorithms 

----

This program utilizes various algorithms in order to derive the shortest paths from a given vertex to a given destination. It uses a specifically formatted input file that represents the graph in a readable way. There are 4 main implementations of the shortest path algorithms: **matrixDijkstra**, **listDijkstra**, **bellmanFord**, and **parallelDijkstra**. All of which use various data structures and varying algorithms to derive the shortest path. The efficiency of the algorithms varies from one to another as well as their functionality. For example, only the **bellmanFord** implementation is capable of detecting and dealing with negative cycles in a given graph. 

---

**---matrixDijkstra---**
To compile: make matrixDijkstra
To run: ./a.out <graph file in .txt format> <output file> <source as string> <destination as string>

Description: This program reads the input file and constructs an adjacency matrix. The matrix is then passed to a Dijkstra algorithm along with other appropriate arrays which are to be filled with values. The program then finds the shortest path using a special function and the information given by Dijkstra. Finally, the program writes the graph information as well as path information with weights and path names into the output file. It also outputs the total distance of the path found, the total CPU run time and the total Wall Clock time it took for the program to run. 

---

**---listDijkstra---**
To compile: make listDijkstra
To run: ./a.out <graph file in .txt format> <output file> <source as string> <destination as string>

Description: This program is extremely similar to matrixDijkstra in its functionality. They key difference is that listDijkstra utilizes an adjacency list instead of a matrix to derive the shortest paths. In order for that to be possible, the algorithm uses the functionality of a data structure knows as a binary heap. The output of the program is exactly the same as matrixDijstra. 

---

**---bellmanFord---**
To compile: make bellmanFord
To run: ./a.out <graph file in .txt format> <output file> <source as string> <destination as string>

Description: The primary reason to use bellmanFord over list or matrix Dijkstra implementations is its ability to detect and deal with negative cycles in a graph. The program reads the given graph into a structure called an edge list and then employs the bellmanFord algorithm to derive the shortest paths. If there is no negative cycle detected, the output of the program is vastly similar to that of matrixDijkstra. However, should a negative cycle be detected, instead of writing a path, the program will actually output the cycle it has detected. The cycle will be represented in the same format as a path but will end with the same vertex as it starts. The program will also output the Wall Clock and CPU times as well as the total weight of the cycle/path.

---

**---parallelDijsktra---**
To compile: make parallelDijkstra
To run: ./a.out <graph file in .txt format> <output file> <source as string> <destination as string> <number of threads>

Description: This program employs multithreading techniques in order to find the shortest paths in a more efficient and optimized way. It uses the same matrix structure as matrixDijkstra, however performs the algorithms in a much more time efficient way. The program also takes an extra parameter which represents the number of threads to be spawned. The output of the program is exactly the same as matrixDijstra. Important to note that the number of threads *MUST* be less or equal to the number of vertices in the graph. 

**NOTE:** Please read the provided _mapqueuefix.txt_ file as it explains how I overcame the "race condition" challenge that presents itself when spawning multiple threads. 

---

Sample input files: graph.txt, graph1.txt, and graph2.txt 
Sample output file: path.txt