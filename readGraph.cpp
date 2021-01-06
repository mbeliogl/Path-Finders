#include "readGraph.hpp"
#include <limits>


int readGraph(ifstream& fin, double**& matrix, string*& vLabels, string**& eLabels){
       
    int numVertices;
    int numEdges;
    
    string label;

    fin >> numVertices;
    fin >> numEdges;

    //MATRIX 

    matrix = new double*[numVertices];
    for(int i = 0; i < numVertices; i++){
        matrix[i] = new double[numVertices];

        for(int j = 0; j < numVertices; j++){
            if(i == j){
                matrix[i][j] = 0;
            }
            else{
                matrix[i][j] = numeric_limits<double>::infinity();
            }
        }
    }
    
    //Printing MATRIX
    // for(int i = 0; i < numVertices; i ++){
    //     for(int j = 0;  j < numVertices; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    //VLABELS
    vLabels = new string[numVertices];
    for(int i = 0; i < numVertices; i++){
        fin >> label;
        vLabels[i] = label;
    }

    //eLABELS

    eLabels = new string*[numEdges];

    int source; 
    int dest; 
    double weight; 
    string edge;

    for(int i = 0; i < numEdges; i++){
        fin >> source;
        fin >> dest;
        fin >> weight; 
        fin >> edge;

        matrix[source][dest] = weight;
        eLabels[i] = new string[numVertices];

        if(matrix[source][dest] == numeric_limits<double>::infinity()){
                eLabels[source][dest] = " ";
            }
            else{
                eLabels[source][dest] = edge;
            }
        }
    

    // for(int i = 0; i < numVertices; i ++){
    //     for(int j = 0;  j < numVertices; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    // for(int i = 0; i < numVertices; i ++){
    //     for(int j = 0;  j < numVertices; j++){
    //         cout << eLabels[i][j] << " ";

    //     }
    //     cout << endl;
    // }

    return numVertices;
}


// ADJ LIST 
int readGraph(ifstream& fin, int**& adj, double**& weights, int*& lengths, string*& vLabels, string**& eLabels){

    int numVertices;
    int numEdges;

    fin >> numVertices;
    fin >> numEdges;

    string label;

    vLabels = new string[numVertices];

    for(int i = 0; i < numVertices; i++){
        fin >> label;
        vLabels[i] = label;
        //cout << label << endl;
    }

    int source;
    int prev;
    int dest;
    double weight;
    string eLabel;

    adj = new int*[numVertices];
    weights = new double*[numVertices];
    lengths = new int[numVertices];
    eLabels = new string*[numVertices];

    vector<int> vec;
    vector<double> wvec;
    vector<string> lab;

    fin >> prev >> dest >> weight >> eLabel;

    vec.push_back(dest);
    wvec.push_back(weight);
    lab.push_back(eLabel);

    fin >> source >> dest >> weight >> eLabel;

    while(!fin.eof()){
        while(source == prev){
            vec.push_back(dest);
            wvec.push_back(weight);
            lab.push_back(eLabel);
            fin >> source >> dest >> weight >> eLabel;
        }
    
    adj[prev] = new int[vec.size()];
    weights[prev] = new double[wvec.size()];
    eLabels[prev] = new string[lab.size()];

    // LOOP FOR DEST
    for(int i = 0; i < vec.size(); i++){
        adj[prev][i] = vec[i];
        //cout << "Adj at " << prev << " = " << adj[prev][i] << endl;
    }

    lengths[prev] = vec.size();

    // LOOP FOR WEIGHT
    for(int i = 0; i < wvec.size(); i++){
        weights[prev][i] = wvec[i];
        //cout << "Weights at " << prev << " = " << weights[prev][i] << endl;
    }

    // LOOP FOR ELABALES
    for(int i = 0; i < lab.size(); i++){
        eLabels[prev][i] = lab[i];
        //cout << "ELABELES at " << prev << " = " << eLabels[prev][i] << endl;
    }


    vec.clear();
    wvec.clear();
    lab.clear();
    vec.push_back(dest);
    wvec.push_back(weight);
    lab.push_back(eLabel);
    prev = source;
    fin >> source >> dest >> weight >> eLabel;
    
    }

    adj[prev] = new int[vec.size()];
    for(int i = 0; i < vec.size(); i++){
        adj[prev][i] = vec[i];
        //cout << "Adj at " << prev << " = " << adj[prev][i] << endl;
    }

    lengths[prev] = vec.size();

    weights[prev] = new double[wvec.size()];
    for(int i = 0; i < wvec.size(); i++){
        weights[prev][i] = wvec[i];
        //cout << "Weights at " << prev << " = " << weights[prev][i] << endl;
    }

    cout << '\n';
    
    eLabels[prev] = new string[lab.size()];
    for(int i = 0; i < lab.size(); i++){
        eLabels[prev][i] = lab[i];
        //cout << "ELABELS at " << prev << " = " << eLabels[prev][i] << endl;
    }


    // for(int i = 0; i < numVertices; i++){
    //     cout << lengths[i] << endl;
    // }    

    return numVertices;
}


/**
 * edgeList variation of readGraph
 * invoked in currency.cpp
 * vLabels -> list of currenct labels (GBP, EUR...)
 * edgeList[i] -> array of size 2 with start and end vertex 
 * weights[i] -> weight associated with this exchange 
 * eLabels[i] -> label of this exchange (GBP->EUR)
 * numVertices -> number of currencies 
 * numEdges -> number of possible exchanges 
 */ 
int readGraph(ifstream& fin, int**& edgeList, double*& weights, int& numEdges, string*& vLabels, string*& eLabels){

    int numVertices;
    int edges;

    string label;

    fin >> numVertices;
    fin >> edges;

    numEdges = edges;

    edgeList = new int*[numEdges];
    
    vLabels = new string[numVertices];
    
    for(int i = 0; i < numVertices; i++){
        fin >> label;
        vLabels[i] = label;
    }

    int source;
    int dest;
    double weight;
    string elabel;

    eLabels = new string[numEdges];
    weights = new double[numEdges];

    /* Looping through every combination and populating arrays with info from .txt file */
    for(int i = 0; i < numEdges; i ++){
        edgeList[i] = new int[2];

        fin >> source;
        fin >> dest;

        edgeList[i][0] = source;
        edgeList[i][1] = dest;
        
        fin >> weight;
        weights[i] = weight;

        fin >> label;
        eLabels[i] = label;
    }
    
    return numVertices;
}




