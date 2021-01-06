#ifndef READGRAPH_H
#define READGRAPH_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


int readGraph(ifstream& fin, double**& matrix, string*& vLabels, string**& eLabels);
int readGraph(ifstream& fin, int**& adj, double**& weights, int*& lengths, string*& vLabels, string**& eLabels);
int readGraph(ifstream& fin, int**& edgeList, double*& weights, int& numEdges, string*& vLabels, string*& eLabels);

#endif