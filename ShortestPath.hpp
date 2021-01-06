#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <thread>


void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*& prev);

void dijkstra(const int* const * adj, const double* const * weights, const int* lengths, int numVertices, int source, double*& dist, int*& prev);

int getPath(int source, int dest, const int* prev, int*& path);

int bellmanFord(const int* const * edges, const double* weights, int numVertices, int numEdges, int source, double*& dist, int*& prev);

int getCycle(int vertex, const int* prev, int numVertices, int*& cycle);

void dijkstra(const double* const * graph, int numVertices, int source, double*& dist, int*& prev, int numThreads);



//HELPERS

void Initialize(const double* const * matrix, int numVertices, int start, int end, double* dist, int* prev, bool* inTree, int numThreads);

void getMinVertex(const double* const * matrix, int numVertices, int start, int end, double* dist, int* prev, bool* inTree, int numThreads, int* minVertex);

//int getMinVertex(const double* const * matrix, int numVertices, double*& dist, int*& prev, bool*& inTree);

void updateDistances(const double* const * matrix, int numVertices, int start, int end,double* dist, int* prev, bool* inTree, int numThreads, int vertex);

#endif