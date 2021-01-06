#include "readGraph.hpp"
#include "ShortestPath.hpp"
#include <limits>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

int main(int argc, char** argv){

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    double cost = atof(argv[5]);

    int** edgeL;
    double* weights;

    int numEdges;
    double totalDist;

    string* e; //eLabels
    string* v; //vLabels

    /* edgeList version of readGraph */
    int numVertices = readGraph(fin,edgeL,weights,numEdges,v, e);

    string sourceV = argv[3];
    string destV = argv[4];

    /* Checking input source and destination vertices and assigning their corresponding integer values */ 
    int source, dest;
    for(int i = 0; i < numVertices; i ++){
        if(sourceV == v[i]){
            source = i;
        }
        if(destV == v[i]){
            dest = i; 
        }
    }
    
    int* prev;
    double* dist;
    int* path;
    int* cycle;

    /*Prepping the weights for bellmanFord by taking setting w[i] = -log(temp*(1-cost)) */
    for(int i = 0; i < numEdges; i ++){
        double temp = weights[i];
        weights[i] = -1*log(temp*(1-cost));
        cout << weights[i] << endl;
    }
    
    /* Setting timers and invoking bellmanFord to catch arbitrage opportunity */
    auto t1 = std::chrono::system_clock::now();
    int x = bellmanFord(edgeL, weights, numVertices, numEdges, source, dist, prev);
    auto t2 = std::chrono::system_clock::now();
    auto dur = t2-t1;
    auto durns = std::chrono::duration_cast<std::chrono::microseconds>(dur);
    double elapsed = durns.count();
    
   
    /** If there is a negative loop, there is an arbitrage opportunity.
     *  A path is derived using the appropriate getCycle method. 
     *  The path is printed to fout and meta data printed to the terminal.
    */
    if(x != -1){
        int cycleSize = getCycle(x, prev, numVertices, cycle);
        fout << numVertices << " " << cycleSize << endl;
        
        for(int i = 0; i < numVertices; i ++){
            fout << v[i] << endl;
        }
        
        int idx = 0;
        for(int i = 0; i < cycleSize; i ++){
            for(int j = 0; j < numEdges; j ++){
                if(edgeL[j][0] == cycle[i] && edgeL[j][1] == cycle[i+1]){
                    totalDist += weights[j];
                    fout << cycle[i] << " " << cycle[i+1] << " " << exp(-1*weights[j]) << " " << e[j] << endl;
                    idx = j;
                }
            }
        }
        
        cout << "Arbitrage Opportunity Detected!" << endl;
        cout << "Effective Exchange Rate: " << exp(-1*totalDist) << endl;
        cout << "Runtime: " << elapsed << " Microseconds" << endl;

    delete[] cycle;
    for (int i=0; i<numEdges; i++){
		delete[] edgeL[i];
	}
    }

    /** If there is no negative cycle. 
     *  The path is simply printed to fout and meta data printed to terminal. 
     */
    else if(x == -1){

    int pathSize = getPath(source, dest, prev, path);
    fout << numVertices << " " << pathSize - 1 << endl;
    
    for(int i = 0; i < numVertices; i++){
        fout << v[i] << endl;
    }
    
    int temp;
    
    for(int i = 0; i < pathSize-1; i++){
        temp = path[i];
        for(int j = 0; j < numEdges; j ++){
            if(edgeL[j][0] == path[i] && edgeL[j][1] == path[i+1]){
                totalDist += weights[j];
                fout << temp << " " << path[i+1] << " " << exp(-1*weights[j]) << " " << e[j] << endl;
            }
        }
    }
    cout << "Effective Exchange Rate: " << exp(-1*totalDist) << endl;
    cout << "Runtime: " << elapsed << " " << "Microseconds" << endl;

    delete[] path;
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