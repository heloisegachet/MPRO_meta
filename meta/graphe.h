#ifndef GRAPHE_H
#define GRAPHE_H

#endif // GRAPHE_H

#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#include<cstring>
#include<time.h>
#include<limits>
#include<assert.h>
#include <vector>
using namespace std;

class Graphe{
    int**   edge;            //These global variables simply define the graph:
    int     n;               //vtx no
    int     m;               //edge no
public:
    Graphe(string filepath); //build a graph from the .txt file
    Graphe(int n); //build an empty graph of size n
    int** getEdge(){return edge;}
    int getEdge(int v1, int v2){return edge[v1][v2];}
    int getNbEdge(){return m;}
    int getNbVertex(){return n;}
    void addEdge(int i, int j); //add the edge from i to j and from j to i
    void delEdge(int i, int j); //delete the edge from i to j and from j to i
    vector<int> getVertexDegree(); //return the vector of vertex degrees : on position i is the degree of vertex i (when indexed from 0)
    void printGraphe(); //prints the graph edges
};
