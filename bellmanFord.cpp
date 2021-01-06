#include "catch.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;

#include "ShortestPath.hpp"
#include "readGraph.hpp"

int main(int argc, char** argv){

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int** edgeL;
    double* weights;

    int numEdges;

    string* e;
    string* v;

    int numVertices = readGraph(fin,edgeL,weights,numEdges,v, e);

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
    
    cout << '\n';
    
    int* prev;
    double* dist;
    int* path;

    auto t = std::chrono::system_clock::now();
    auto startCPU = clock();
    int x = bellmanFord(edgeL, weights, numVertices, numEdges, source, dist, prev);


    int weightTotal;
    int index;

    // IF THERE IS NO NEG CYCLE. E.G X = -1

    if(x == -1){
        cout << "NO NEGATIVE CYCLES" << endl;
        
        auto t2 = std::chrono::system_clock::now();
        auto endCPU = clock();
        auto dur = t2-t;
        auto durns = std::chrono::duration_cast<std::chrono::microseconds>(dur);
        double elapsed = durns.count();

        int pathSize = getPath(source, dest, prev, path);
        fout << numVertices << " " << pathSize - 1 << endl;
        
        for(int i = 0; i < numVertices; i ++){
            fout << v[i] << endl;
        }

    int tempSource; 
    double totalDist; 

    // cout << "PATH SIZE : " << pathSize-1 << endl;

    int idx;
    for(int i = 0; i < pathSize - 1; i++){
        tempSource = path[i];

        for(int j = 0; j < numEdges; j++){
            if(edgeL[j][0] == path[i] && edgeL[j][1] == path[i+1]){
                idx = j;
            }
        }

        fout << tempSource << " " << path[i+1] << " " << weights[idx] << " " << e[idx] << endl;
        totalDist += weights[idx];
    }

    fout << '\n';
    fout << "Total Distance: " << totalDist << endl;

    fout << "CPU Time: " << (endCPU-startCPU)*(1000000/CLOCKS_PER_SEC) << " microseconds" << endl;
    fout << "Wall Clock Time: " << elapsed << " " << "microseconds" << endl;

    delete[] path;
    for (int i=0; i<numEdges; i++){
		delete[] edgeL[i];
	}    
    }

    //IF THERE IS A NEG CYCLE E.G X != -1

    else if(x != -1){
    int* cycle;
    auto t2 = std::chrono::system_clock::now();
    auto endCPU = clock();
    auto dur = t2-t;
    auto durns = std::chrono::duration_cast<std::chrono::microseconds>(dur);
    double elapsed = durns.count();

	int cycleSize = getCycle(x, prev, numVertices, cycle);
    cout << "*** NEGATIVE CYCLE DETECTED *** " << endl;
    cout << "LENGTH : " << cycleSize << endl;

    fout << numVertices << " " << cycleSize << endl;
        
    for(int i = 0; i < numVertices; i ++){
        fout << v[i] << endl;
    }
    
    int tempSource; 
    double totalDist; 

    int idx;

    for(int i = 0; i < cycleSize; i++){
        tempSource = cycle[i];

        for(int j = 0; j < numEdges; j++){
            if(edgeL[j][0] == cycle[i] && edgeL[j][1] == cycle[i+1]){
                idx = j;
            }
        }

        fout << tempSource << " " << cycle[i+1] << " " << weights[idx] << " " << e[idx] << endl;
        totalDist += weights[idx];
    }

    fout << '\n';
    fout << "Total Distance: " << totalDist << endl;

    fout << "CPU Time: " << (endCPU-startCPU)*(1000000/CLOCKS_PER_SEC) << " microseconds" << endl;
    fout << "Wall Clock Time: " << elapsed << " " << "microseconds" << endl;
    delete[] cycle;
    for (int i=0; i<numEdges; i++){
		delete[] edgeL[i];
	}
    }

	delete[] dist;
	delete[] prev;
	delete[] e;
	delete[] v;
	delete[] weights;
    delete[] edgeL;

}

