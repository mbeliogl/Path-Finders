//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <ostream>
using namespace std;

#include "readGraph.hpp"

// TEST_CASE("ReadGraph"){

//     SECTION("Declaration"){
//     }
// }


int main(int argc, char** argv){
    double** m;
    string* v;
    string** e;

    ifstream f("graph.txt");

    //MATRIX
    //readGraph(f, m, v, e);

    //int readGraph(ifstream& fin, int**& adj, double**& weights, int*& lengths, string*& vLabels, string**& eLabels)

    int** adj;
    //double** weights;
    int* lengths;

    int** edgeList;
    double* weights;
    int numEdges;
    string* eLabels;

    // ADJ LIST
    //readGraph(f,adj,weights,lengths,v,e);

    // EDGE LIST
    readGraph(f, edgeList, weights, numEdges,v, eLabels);

}