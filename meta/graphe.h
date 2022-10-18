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
    Graphe(string filepath);
    int** getEdge(){return edge;}
    int getNbEdge(){return m;}
    int getNbVertex(){return n;}
    vector<int> getVertexDegree();
};
