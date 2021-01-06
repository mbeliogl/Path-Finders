#include "catch.hpp"
#include <iostream>
#include <ostream>
using namespace std;
#include <string>
#include <fstream>
#include <sstream>

#include "ShortestPath.hpp"
#include "readGraph.hpp"
#include "BinaryHeap.hpp"

int main(int argc, char** argv){

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int** adj;
    double** weights;
    int* lengths;
    string* v;
    string** e;
    
    int numVertices = readGraph(fin,adj, weights, lengths, v,e);

    string sourceV = argv[3];
    string destV = argv[4];

    int source, dest;
    for(int i = 0; i < numVertices; i ++){
        if(sourceV == v[i])
        {
            source = i;
        }
        if(destV == v[i])
        {
            dest = i; 
        }
    }


    // int source = 2;
    // int dest = 1;
    int* prev;
    double* dist;
    int* path;
    
    dijkstra(adj,weights,lengths, numVertices, source, dist, prev);

    int pathSize = getPath(source, dest, prev, path);

    // for(int i = 0; i < pathSize; i ++){
    //     cout << path[i] << endl;
    // }


    fout << numVertices << " " << pathSize - 1 << endl;

     for(int i = 0; i < numVertices; i++){
        fout << v[i] << endl;
    }

    int tempSource; 
    double totalDist; 
    int idx;
    for(int i = 0; i < pathSize-1; i++){
        tempSource = path[i];
        for(int j = 0; j < lengths[i+1]; j ++){
            if(adj[path[i]][j] == path[i+1]){
                idx = j;
            }
        }
        fout << tempSource << " " << path[i+1] << " " << weights[path[i]][idx] << " " << e[path[i]][idx] << endl;
        totalDist += weights[tempSource][path[i+1]];
    }

    fout << '\n';
    fout << "Total Distance: " << totalDist << endl;

}
