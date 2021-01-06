#include "ShortestPath.hpp"
#include "BinaryHeap.hpp"
#include <vector>
#include <cstdlib>
#include <thread>
using namespace std;

void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*& prev){

    dist = new double[numVertices];
    prev = new int[numVertices];
    bool* inTree = new bool[numVertices];

    for(int i = 0; i < numVertices; i++){
        dist[i] = numeric_limits<double>::infinity();
        prev[i] = 0;
        inTree[i] = false;
    }

     dist[source] = 0;
     inTree[source] = true; 

     int n = source; 

     for(int i = 1; i < numVertices; i++){   //removed - 1
         for(int j = 0; j < numVertices; j++){ //removes -1
             if((inTree[j] == false) && dist[n] + matrix[n][j] < dist[j]){
                 dist[j] = dist[n] + matrix[n][j];
                 prev[j] = n;
             }
         }

         double min = numeric_limits<double>::infinity();
         for(int x = 0; x < numVertices; x++){ //removed -1
             if((inTree[x] == false) && dist[x] < min){
                 n = x;
                 min = dist[x];
             }
         }
         inTree[n] = true;
     }


    //testing (printing)
    // for(int i = 0; i < numVertices; i++){ //removed -1
    //     cout << source << "->" << i << " : " << dist[i] << " " << "prev : " << prev[i] << endl;
    // }
}

int getPath(int source, int dest, const int* prev, int*& path){

    int prevTemp = dest;
    int pathSize = 0;


    while(prevTemp != source){
        prevTemp = prev[prevTemp];
        pathSize++;
    }
    pathSize += 1;
    path = new int[pathSize];

    int prevTemp1 = dest;
    for(int i = pathSize-2; i >= 0; i--){
        prevTemp1 = prev[prevTemp1];
        path[i] = prevTemp1;
    }

    path[pathSize - 1] = dest;

    // int tempSource;

    // for(int i = pathSize-1; i > 0; i--){
    //     tempSource = path[i];
    // }

    return pathSize; 

}


void dijkstra(const int* const * adj, const double* const * weights, const int* lengths, int numVertices, int source, double*& dist, int*& prev){
    dist = new double[numVertices];
    prev = new int[numVertices];

    for(int i = 0; i < numVertices; i++){
        dist[i] = numeric_limits<double>::infinity();
        prev[i] = 0;
    }

    BinaryHeap heap(dist, numVertices);
    heap.decreasePriority(source,0);

    int n = heap.getMin();
    heap.popMin();

    //cout << "MIN " << n << endl; 

	dist[n]=0;
    prev[n]=n;
    for(int i = 0; i < numVertices-1; i++){
		for(int x = 0; x < lengths[n]; x++){

			if (heap.contains(adj[n][x]) && (dist[n] + weights[n][x]) < heap.getPriority(adj[n][x])){
				heap.decreasePriority(adj[n][x],(dist[n]+weights[n][x]));
				int tmp = n;
				prev[adj[n][x]] = tmp;
			}
		}

        n = heap.getMin();
        dist[n] = heap.getPriority(n);
        heap.popMin();
    }

}


int bellmanFord(const int* const * edges, const double* weights, int numVertices, int numEdges, int source, double*& dist, int*& prev){

    dist = new double[numVertices];
    prev = new int[numVertices];
    
    for(int i = 0; i < numVertices; i ++){
        dist[i] = numeric_limits<double>::infinity();
        prev[i] = 0;
    }
    dist[source] = 0;


    for(int i = 0; i < (numVertices+1); i++){  //changed i = 1
        for(int j = 0; j < numEdges; j++){
            int x = edges[j][0];
            int y = edges[j][1];
            
            if((dist[x] + weights[j]) < dist[y]){
                dist[y] = dist[x] + weights[j];
                prev[y] = x;

                //cout << i << endl;
                if(i == numVertices){
                    //cout << "NEG CYCLE DETECTED" << endl;
                    return edges[j][1];
                }
            }
        }
    }
    
    return -1;
}

int getCycle(int vertex, const int* prev, int numVertices, int*& cycle){
   int cycleSize = 1;
   bool* inPath = new bool[numVertices];
   
   for(int i = 0; i < numVertices; i ++){
       inPath[i] = false;
    }
    
    int current = prev[vertex];
    
    while(current != vertex){
        current = prev[current];
        cycleSize ++;
    }
    
    cycle = new int[cycleSize+1];
    cycle[0] = vertex;
    
    for(int i = 1; i < cycleSize+1; i ++){
        if(inPath[prev[vertex]] == false && prev[vertex] != vertex){
            cycle[i] = prev[vertex];
            inPath[prev[vertex]] = true;
            vertex = prev[vertex];
        }
    }
    int temp;
    for(int i = 0; i < (cycleSize+1)/2; i ++){
        temp = cycle[i];
        cycle[i] = cycle[(cycleSize)-i];
        cycle[cycleSize-i] = temp;
    }
    return cycleSize;
}
    



// PARALLEL DIJSKTRA BEGIN 

void dijkstra(const double* const * graph, int numVertices, int source, double*& dist, int*& prev, int numThreads){

    int start, end;
    
    start = 0;
    end = numVertices;

    dist = new double[numVertices];
    prev = new int[numVertices];
    bool* inTree = new bool[numVertices];

    Initialize(graph,numVertices,start, end, dist, prev, inTree, numThreads);


    dist[source] = 0;
    //inTree[source] = true;

    //int minVertex;
    double min = numeric_limits<double>::infinity();

    //int x;
    int minVertex;
    for(int i = 1; i < numVertices; i++){
        getMinVertex(graph, numVertices, start, end,dist, prev, inTree, numThreads, &minVertex);
        inTree[minVertex] = true;
        updateDistances(graph, numVertices,start, end, dist, prev, inTree, numThreads, minVertex);
    }
    
    //testing (printing)
    // for(int i = 0; i < numVertices; i++){ 
    //     cout << source << "->" << i << " : " << dist[i] << " " << "prev : " << prev[i] << endl;
    // }

    // for(int i = 0; i < numVertices; i++){
    //     cout << i << " " << "dist : " << dist[i] << " " << "prev : " << prev[i] << " " << "in tree : " << inTree[i] << endl;
    // }

    //cout << "MIN VERTEX : " << x << endl;
}

// PARALLEL DIJKSTRA END


//HELPTER FUNCTIONS START 

void Initialize(const double* const * matrix, int numVertices, int start, int end, double* dist, int* prev, bool* inTree, int numThreads){

    if(end == start + 1){ 
        dist[start] = numeric_limits<double>::infinity();
        prev[start] = 0;
        inTree[start] = false;
    }

    else{

        if(numThreads == 1){
            int mid = (start+end)/2;
            Initialize(matrix, numVertices, start, mid, dist, prev, inTree, 1);
            Initialize(matrix, numVertices, mid, end, dist, prev, inTree, 1);
        }
        
        else{
            int halfT = numThreads/2;
            int mid = start + halfT*((end - start)/numThreads);
            thread leftThread(Initialize, matrix, numVertices, start, mid, dist, prev, inTree, halfT);
            Initialize(matrix, numVertices, mid, end, dist, prev, inTree, numThreads-halfT);
            
            leftThread.join();
        }
    }

    //  for(int i = 0; i < numVertices; i++){
    //     dist[i] = numeric_limits<double>::infinity();
    //     prev[i] = 0;
    //     inTree[i] = false;
    // }
}

void getMinVertex(const double* const * matrix, int numVertices, int start, int end, double* dist, int* prev, bool* inTree, int numThreads, int* minVertex){

    if(end == start+1){
        if(inTree[start] == true){
            *minVertex = -1;
        }
        else{
        *minVertex = start;
        }
    }
    
    else{
        int left; 
        int right; 
        if(numThreads == 1){
            int mid = (start+end)/2;
            getMinVertex(matrix, numVertices, start, mid, dist, prev, inTree, 1, &left);
            getMinVertex(matrix, numVertices, mid, end, dist, prev, inTree, 1, &right);
        }

        else{
            int halfT = numThreads/2;
            int mid = start + halfT*((end - start)/numThreads);
            thread leftThread(getMinVertex, matrix, numVertices, start, end, dist, prev, inTree, halfT, &left);
            getMinVertex(matrix, numVertices, mid, end, dist, prev, inTree, numThreads-halfT, &right);
            
            leftThread.join();

        }
    

    if(left == - 1 && right == - 1){
        *minVertex = -1;
    }

    else if(left == -1){
        *minVertex = right;
    }

    else if(right == -1){
        *minVertex = left;
    }

    else{
        *minVertex = left;
        if(dist[right] <= dist[left]){
            *minVertex = right;
        }
    }
    
    }
}

//    int minVertex = 0;
//    double min = numeric_limits<double>::infinity();
//          for(int x = 0; x < numVertices-1; x++){ 
//              if((inTree[x] == false) && dist[x] < min){
//                  minVertex = x;
//                  min = dist[x];
//              }
//          }
//     return minVertex;


void updateDistances(const double* const * matrix, int numVertices, int start, int end, double* dist, int* prev, bool* inTree, int numThreads, int vertex){
 
    if(end == start+1){
        if((inTree[start] == false) && dist[vertex] + matrix[vertex][start] < dist[start]){
            dist[start] = dist[vertex] + matrix[vertex][start];
            prev[start] = vertex;
        }
    }

    else{
        if(numThreads == 1){
            int mid = (start+end)/2;
            updateDistances(matrix, numVertices, start, mid, dist, prev, inTree, 1, vertex);
            updateDistances(matrix, numVertices, mid, end, dist, prev, inTree, 1, vertex);

        }

        else{
            int halfT = numThreads/2;
            int mid = start + halfT*((end - start)/numThreads);
            thread leftThread(updateDistances, matrix, numVertices, start, mid, dist, prev, inTree, halfT, vertex);
            updateDistances(matrix, numVertices, mid, end, dist, prev, inTree, numThreads - halfT, vertex);
           
            
            leftThread.join();
    }
    }
}


    //  for(int i = 0; i < numVertices; i++){
    //          if((inTree[i] == false) && dist[vertex] + matrix[vertex][i] < dist[i]){
    //              dist[i] = dist[vertex] + matrix[vertex][i];
    //              prev[i] = vertex;

    //      }
    // }



//HELPER FUNCTIONS END