#include "catch.hpp"
#include <iostream>
#include <ostream>
using namespace std;
#include <string>
#include <fstream>
#include <sstream>

#include "ShortestPath.hpp"
#include "readGraph.hpp"



int main(int argc, char** argv){

    double** m;
    string* v;
    string** e;

    ifstream fin("graph.txt");

    int numVertices = readGraph(fin, m, v, e);

    int source = 2;
    int dest = 0;
    int* prev;
    double* dist;
    bool* inTree;

    // int start = 0;
    // int end = numVertices;

    //Initialize(m, numVertices, start, end, dist, prev, inTree);

    //getMinVertex(m, numVertices, dist, prev, inTree);

    // updateDistances(m, numVertices, dist, prev, inTree, source);

    //dijkstra(m, numVertices, source, dist, prev);

    cout << '\n';
    dijkstra(m, numVertices, source, dist, prev, 4);



    // int* path;
    // getPath(source, dest, prev, path);
}