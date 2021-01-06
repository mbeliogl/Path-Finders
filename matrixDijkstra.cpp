#include "catch.hpp"
#include <iostream>
#include <ostream>
using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

#include "ShortestPath.hpp"
#include "readGraph.hpp"

int main(int argc, char** argv){

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    double** m;
    string* v;
    string** e;
    int numVertices = readGraph(fin, m, v, e);
  
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

    int* prev;
    double* dist;
    int* path;

    auto t = std::chrono::system_clock::now();
    auto startCPU = clock();
    dijkstra(m,numVertices, source,dist, prev);

    auto t2 = std::chrono::system_clock::now();
    auto endCPU = clock();
    auto dur = t2-t;
    auto durns = std::chrono::duration_cast<std::chrono::microseconds>(dur);
    double elapsed = durns.count();
    int pathSize = getPath(source, dest, prev, path);

    fout << numVertices << " " << pathSize - 1 << endl;

  
    for(int i = 0; i < numVertices; i++){
        fout << v[i] << endl;
    }
    
    int tempSource; 
    double totalDist; 
    for(int i = 0; i < pathSize-1; i++){
        tempSource = path[i];
        fout << tempSource << " " << path[i+1] << " " << m[tempSource][path[i+1]] << " " << e[tempSource][path[i+1]] << endl;
        totalDist += m[tempSource][path[i+1]];
    }

    fout << '\n';
    fout << "Total Distance: " << totalDist << endl;

    fout << "CPU Time: " << (endCPU-startCPU)*(1000000/CLOCKS_PER_SEC) << " microseconds" << endl;
    fout << "Wall Clock Time: " << elapsed << " " << "microseconds" << endl;


    //fout << path[0] << " " << dest << " " << m[path[0]][dest] << " " << e[path[0]][dest] << endl;

    delete[] path;
    delete[] dist;
    delete[] prev;

    for(int i = 0; i < numVertices; i++){
        delete[] e[i];
        delete[] m[i];

    }

    delete[] m;
    delete[] e;
    delete[] v;
    return 0;
}